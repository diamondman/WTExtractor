#include <endian.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "pwt_decode.h"

#define MAX(a,b) (((a)>(b))?(a):(b))

typedef union {
  char c[4];
  float f;
  uint32_t ui;
  int32_t i;
} FloatIntConv;

float tofloat(uint32_t in){
  FloatIntConv out;
  out.ui = in;
  return out.f;
}

uint32_t read_uint(DataAccessor* acc){
  FloatIntConv buff;
  acc->read(acc, buff.c, 4);
  buff.ui = be32toh(buff.ui);
  return buff.ui;
}

float read_float(DataAccessor* acc){
  FloatIntConv buff;
  acc->read(acc, buff.c, 4);
  buff.ui = be32toh(buff.ui);
  return buff.f;
}

typedef struct {
  DataAccessor* acc;
  uint8_t bit;
  uint8_t currbyte;
} BitfieldReader;

BitfieldReader* initializeBitarray(BitfieldReader* ba, DataAccessor* acc){
  if(ba == NULL) ba = malloc(sizeof(BitfieldReader));
  ba->acc = acc;
  ba->bit = 0;
  ba->currbyte = 0;
  return ba;
}

uint8_t bfr_consumebytebits(BitfieldReader* ba, uint8_t count){
  if(ba->bit == 0){
    ba->acc->read(ba->acc, &ba->currbyte, 1);
    ba->bit = 0;
  }
  if(count+ba->bit > 8){
    printf("Only works for bits in current byte.\n");
    exit(1);
  }
  uint8_t res = (ba->currbyte >> ba->bit) & ((1<<count)-1);
  ba->bit = (ba->bit + count)%8;
  return res;
}

uint8_t bfr_readbyte(BitfieldReader* ba){
  if (ba->bit == 0) return bfr_consumebytebits(ba, 8);
  uint8_t bitsneedednext = ba->bit;
  return bfr_consumebytebits(ba, 8 - ba->bit)
    | (bfr_consumebytebits(ba, bitsneedednext) << (8-bitsneedednext));
}

uint8_t bfr_readsubbyte(BitfieldReader* ba, uint8_t bitcount){
  if(bitcount > 8){
    printf("Only works for bits in current byte.\n");
    exit(1);
  }
  uint8_t left_in_byte = 8 - ba->bit;
  if(left_in_byte < bitcount){
    uint8_t bitsneedednext = bitcount - left_in_byte;
    return bfr_consumebytebits(ba, left_in_byte) |
      (bfr_consumebytebits(ba, bitsneedednext) << left_in_byte);
  }else
    return bfr_consumebytebits(ba, bitcount);
}

uint32_t bfr_readbits(BitfieldReader* ba, uint8_t bitcount){
  if(bitcount > 32){
    printf("Only works for up to 32 bits, not %d.\n", bitcount);
    exit(1);
  }
  uint32_t res = 0;
  uint8_t whichbyte = 0;

  for(int i = 0; i < bitcount/8; i++)
    res |= bfr_readbyte(ba) << (whichbyte++ * 8);

  if(bitcount % 8)
    res |= bfr_readsubbyte(ba, bitcount % 8) << (whichbyte++ * 8);

  return res;
}

PWT_Visuals* pwt_readvisuals(PWT* pwt, DataAccessor* acc){
  BitfieldReader ba;
  PWT_Visuals* visuals = malloc(sizeof(PWT_Visuals));
  memset(visuals, 0, sizeof(PWT_Visuals));

  visuals->vcount = read_uint(acc);
  visuals->ncount = read_uint(acc);
  visuals->fcount = read_uint(acc);
  acc->read(acc, &visuals->texture_count, 1);

  ///// VERTICES
  initializeBitarray(&ba, acc);
  visuals->vertex_count = bfr_readbits(&ba, 32);
  visuals->vertexcomp_count = bfr_readbits(&ba, 32);

  if(visuals->vertex_count != visuals->vertexcomp_count){
    printf("Don't know how to handle compressed vectors\n");
    exit(1);
  }

  visuals->bboxmin.X = tofloat(bfr_readbits(&ba, 32));
  visuals->bboxmin.Y = tofloat(bfr_readbits(&ba, 32));
  visuals->bboxmin.Z = tofloat(bfr_readbits(&ba, 32));

  visuals->unused_vbits_x = bfr_readbits(&ba, 6);
  visuals->unused_vbits_y = bfr_readbits(&ba, 6);
  visuals->unused_vbits_z = bfr_readbits(&ba, 6);

  float maxbbox_dimen =
    MAX(pwt->global_max.X - pwt->global_min.X,
	MAX(pwt->global_max.Y - pwt->global_min.Y,
            pwt->global_max.Z - pwt->global_min.Z));

  uint32_t vmax = (1 << pwt->vertex_bit_accuracy) - 1;

  visuals->vertices = malloc(visuals->vertex_count*sizeof(PWT_XYZ));

  for(int i=0; i <visuals->vertex_count; i++){
    PWT_XYZ* currxyz = &visuals->vertices[i];
    currxyz->X = (float)bfr_readbits
      (&ba, pwt->vertex_bit_accuracy - visuals->unused_vbits_x);
    currxyz->Y = (float)bfr_readbits
      (&ba, pwt->vertex_bit_accuracy - visuals->unused_vbits_y);
    currxyz->Z = (float)bfr_readbits
      (&ba, pwt->vertex_bit_accuracy - visuals->unused_vbits_z);

    currxyz->X = (currxyz->X*maxbbox_dimen/vmax) + visuals->bboxmin.X;
    currxyz->Y = (currxyz->Y*maxbbox_dimen/vmax) + visuals->bboxmin.Y;
    currxyz->Z = (currxyz->Z*maxbbox_dimen/vmax) + visuals->bboxmin.Z;
  }

  ///// NORMALS
  initializeBitarray(&ba, acc);

  visuals->normal_count = bfr_readbits(&ba, 32);
  visuals->normalcomp_count = bfr_readbits(&ba, 32);

  if(visuals->normal_count != visuals->normalcomp_count){
    printf("Don't know how to handle compressed vectors\n");
    exit(1);
  }

  visuals->norm_bboxmin.X = tofloat(bfr_readbits(&ba, 32));
  visuals->norm_bboxmin.Y = tofloat(bfr_readbits(&ba, 32));
  visuals->norm_bboxmin.Z = tofloat(bfr_readbits(&ba, 32));

  visuals->norm_bboxmax.X = tofloat(bfr_readbits(&ba, 32));
  visuals->norm_bboxmax.Y = tofloat(bfr_readbits(&ba, 32));
  visuals->norm_bboxmax.Z = tofloat(bfr_readbits(&ba, 32));

  visuals->unused_nbits_x = bfr_readbits(&ba, 6);
  visuals->unused_nbits_y = bfr_readbits(&ba, 6);
  visuals->unused_nbits_z = bfr_readbits(&ba, 6);

  float maxbbox_dimen_n =
    MAX(visuals->norm_bboxmax.X - visuals->norm_bboxmin.X,
	MAX(visuals->norm_bboxmax.Y - visuals->norm_bboxmin.Y,
            visuals->norm_bboxmax.Z - visuals->norm_bboxmin.Z));

  uint32_t maxnum = (1 << pwt->normal_bit_accuracy) - 1;

  visuals->normals = malloc(visuals->normal_count*sizeof(PWT_XYZ));

  for(int i=0; i < visuals->normal_count; i++){
    PWT_XYZ* curr = &visuals->normals[i];
    curr->X = (float)bfr_readbits
      (&ba, pwt->normal_bit_accuracy - visuals->unused_nbits_x);
    curr->Y = (float)bfr_readbits
      (&ba, pwt->normal_bit_accuracy - visuals->unused_nbits_y);
    curr->Z = (float)bfr_readbits
      (&ba, pwt->normal_bit_accuracy - visuals->unused_nbits_z);

    curr->X = (curr->X*maxbbox_dimen_n/maxnum) + visuals->norm_bboxmin.X;
    curr->Y = (curr->Y*maxbbox_dimen_n/maxnum) + visuals->norm_bboxmin.Y;
    curr->Z = (curr->Z*maxbbox_dimen_n/maxnum) + visuals->norm_bboxmin.Z;
  }

  ///// FACES
  initializeBitarray(&ba, acc);

  unsigned int face_vbit_length = ceil(log2(visuals->vcount));
  unsigned int face_nbit_length = ceil(log2(visuals->ncount));

  visuals->faces = malloc(sizeof(PWT_Face)*visuals->fcount);
  visuals->face_normals = malloc(sizeof(PWT_Face)*visuals->fcount);
  for(int i = 0; i < visuals->fcount; i++)
    for(int j = 0; j < 3; j++){
      visuals->face_normals[i][j] = bfr_readbits(&ba, face_nbit_length);
      visuals->faces[i][j] = bfr_readbits(&ba, face_vbit_length);
    }

  ///// TEXMAP
  visuals->texmapU = malloc(sizeof(float)*visuals->vcount);
  for(int i = 0; i < visuals->vcount; i++)
    visuals->texmapU[i] = read_float(acc);

  visuals->texmapV = malloc(sizeof(float)*visuals->vcount);
  for(int i = 0; i < visuals->vcount; i++)
    visuals->texmapV[i] = read_float(acc);

  ///// FACE DETAILS
  visuals->face_details = malloc(sizeof(FaceDetails)*visuals->fcount);
  for(int i = 0; i < visuals->fcount; i++){
    acc->read(acc, &visuals->face_details[i].texture_name, 1);

    visuals->face_details[i].texture_color = read_uint(acc);
    visuals->face_details[i].texture_power = read_float(acc);

    visuals->face_details[i].emmisivity.X = read_float(acc);
    visuals->face_details[i].emmisivity.Y = read_float(acc);
    visuals->face_details[i].emmisivity.Z = read_float(acc);

    visuals->face_details[i].specularity.X = read_float(acc);
    visuals->face_details[i].specularity.Y = read_float(acc);
    visuals->face_details[i].specularity.Z = read_float(acc);
  }

  ///// TEXTURES
  if(visuals->texture_count){
    uint8_t datlen;
    visuals->texture_paths = malloc(sizeof(char*)*visuals->texture_count);
    for(int i = 0; i < visuals->texture_count; i++){
      acc->read(acc, &datlen, 1);
      visuals->texture_paths[i] = malloc((sizeof(char)* datlen)+1);
      acc->read(acc, visuals->texture_paths[i], datlen);
      visuals->texture_paths[i][datlen] = 0;
    }
  }

  return visuals;
}

PWT_Frame* pwt_readframe(PWT* pwt, DataAccessor* acc){
  PWT_Frame* frame = malloc(sizeof(PWT_Frame));
  memset(frame, 0, sizeof(PWT_Frame));

  frame->subframe_count = read_uint(acc);

  uint8_t namelen;
  acc->read(acc, &namelen, 1);
  if(namelen > 0){
    frame->name = calloc(namelen+1, 1);
    acc->read(acc, frame->name, namelen);
  }

  for(int i = 0; i < 16; i++)
    frame->transform_matrix[i] = read_float(acc);

  acc->read(acc, &frame->has_animation, 1);
  acc->read(acc, &frame->has_visuals, 1);

  if(frame->has_animation){
    frame->animation_count = read_uint(acc);
    frame->animation_d3d_options = read_uint(acc);
    frame->animation = malloc(sizeof(PWT_Animation)*
			      frame->animation_count);
    for(int i = 0; i<frame->animation_count; i++){
      frame->animation[i].dv_time = read_float(acc);
      frame->animation[i].key_type = read_uint(acc);
      frame->animation[i].aniA = read_float(acc);
      frame->animation[i].aniB = read_float(acc);
      frame->animation[i].aniC = read_float(acc);
      frame->animation[i].aniD = read_float(acc);
    }
  }else{
    frame->animation_count = 0;
    frame->animation_d3d_options = 0;
  }

  if(frame->has_visuals){
    frame->visuals = pwt_readvisuals(pwt, acc);
  }

  if(frame->subframe_count){
    frame->subframes = calloc(frame->subframe_count, sizeof(PWT_Frame*));
    for(int i = 0; i < frame->subframe_count; i++)
      frame->subframes[i] = pwt_readframe(pwt, acc);
  }

  return frame;
}

PWT* pwt_extract(DataAccessor* acc){
  PWT* pwt = malloc(sizeof(PWT));
  memset(pwt, 0, sizeof(PWT));

  if(acc->memcmp(acc, "\x00\x00\x00\x13", 4)){
    printf("Bad Magic\n");
    goto FAIL;
  }

  //printf("OFFSET: %zu\n", ftell(acc->dat.file));
  //float* abc = &(pwt->global_min.X);
  //*abc = -7;
  //printf("ABC PTR  %p\n", abc);

  pwt->global_min.X = read_float(acc);
  pwt->global_min.Y = read_float(acc);
  pwt->global_min.Z = read_float(acc);

  pwt->global_max.X = read_float(acc);
  pwt->global_max.Y = read_float(acc);
  pwt->global_max.Z = read_float(acc);

  pwt->veryclose = read_uint(acc);
  pwt->prettyclose = read_uint(acc);

  pwt->dowrite_vertices = read_uint(acc);
  pwt->dowrite_normals = read_uint(acc);
  pwt->vertex_bit_accuracy = read_uint(acc);
  pwt->vertex_bit_accuracy_1 = read_uint(acc);
  pwt->normal_bit_accuracy = read_uint(acc);
  pwt->unk_f44 = read_uint(acc);
  pwt->unk_f48 = read_uint(acc);

  pwt->vertex_count = read_uint(acc);
  pwt->normal_count = read_uint(acc);
  pwt->face_count = read_uint(acc);
  pwt->unk_f40 = read_uint(acc);

  pwt->frames = pwt_readframe(pwt, acc);

 CLEANUP:
  return pwt;

 FAIL:
  if(pwt) free(pwt);
  pwt = NULL;
  goto CLEANUP;
}

void pwt_visuals_print(PWT_Visuals* visuals){
  printf("############ FRAME VISUALS ############\n");

  printf("VisualsVCOUNT:   %d\n", visuals->vcount);
  printf("VisualsNCOUNT:   %d\n", visuals->ncount);
  printf("VisualsFCOUNT:   %d\n", visuals->fcount);

  printf("VertexCount:     %d\n", visuals->vertex_count);
  printf("VertexCompCount: %d\n", visuals->vertexcomp_count);

  printf("bboxMIN   : {%f, %f, %f}\n",
	 visuals->bboxmin.X, visuals->bboxmin.Y, visuals->bboxmin.Z);

  printf("unusedbits: {%u, %u, %u}\n", visuals->unused_vbits_x,
	 visuals->unused_vbits_y, visuals->unused_vbits_z);

  /*for(int i=0; i <visuals->vertex_count; i++){
    PWT_XYZ* currxyz = &visuals->vertices[i];
    printf("  (%f, %f, %f)\n", currxyz->X,currxyz->Y,currxyz->Z);
    }*/

  printf("NormalCount:     %d\n", visuals->normal_count);
  printf("NormalCompCount: %d\n", visuals->normalcomp_count);

  printf("NormbboxMIN: {%f, %f, %f}\n", visuals->norm_bboxmin.X,
	 visuals->norm_bboxmin.Y, visuals->norm_bboxmin.Z);
  printf("NormbboxMAX: {%f, %f, %f}\n", visuals->norm_bboxmax.X,
	 visuals->norm_bboxmax.Y, visuals->norm_bboxmax.Z);

  printf("Normunusedbits: {%u, %u, %u}\n", visuals->unused_nbits_x,
	 visuals->unused_nbits_y, visuals->unused_nbits_z);

  /*for(int i=0; i < visuals->normal_count; i++){
    PWT_XYZ* curr = &visuals->normals[i];
    printf("  (%f, %f, %f)\n", curr->X,curr->Y,curr->Z);
  }

  for(int i = 0; i < visuals->fcount; i++)
    printf("FACE    : {%u %u %u}\n", visuals->faces[i][0],
	   visuals->faces[i][1], visuals->faces[i][2]);
  for(int i = 0; i < visuals->fcount; i++)
    printf("FACENORM: {%u %u %u}\n", visuals->face_normals[i][0],
	   visuals->face_normals[i][1], visuals->face_normals[i][2]);

  for(int i = 0; i < visuals->vcount; i++)
    printf("TEXMAPU: %f\n", visuals->texmapU[i]);
  for(int i = 0; i < visuals->vcount; i++)
    printf("TEXMAPV: %f\n", visuals->texmapV[i]);

  for(int i = 0; i < visuals->fcount; i++){
    printf("TexName: %u; TexColor: %08x; TexPower: %f; "
	   "Emmis: {%f %f %f}; Spec: {%f %f %f}\n",
	   visuals->face_details[i].texture_name,

	   visuals->face_details[i].texture_color,
	   visuals->face_details[i].texture_power,

	   visuals->face_details[i].emmisivity.X,
	   visuals->face_details[i].emmisivity.Y,
	   visuals->face_details[i].emmisivity.Z,

	   visuals->face_details[i].specularity.X,
	   visuals->face_details[i].specularity.Y,
	   visuals->face_details[i].specularity.Z);
           }*/


  for(int i = 0; i < visuals->texture_count; i++)
    printf("TEX PATH: %s\n", visuals->texture_paths[i]);

  printf("############ END FRAME VISUALS ############\n");
}

void pwt_frame_print(PWT_Frame* frame){
  printf("############ FRAME ############\n");
  printf("Name: %s\n", frame->name);
  printf("{%f %f %f %f\n %f %f %f %f\n %f %f %f %f\n %f %f %f %f}\n",
	 frame->transform_matrix[0], frame->transform_matrix[1],
	 frame->transform_matrix[2], frame->transform_matrix[3],
	 frame->transform_matrix[4], frame->transform_matrix[5],
	 frame->transform_matrix[6], frame->transform_matrix[7],
	 frame->transform_matrix[8], frame->transform_matrix[9],
	 frame->transform_matrix[10], frame->transform_matrix[11],
	 frame->transform_matrix[12], frame->transform_matrix[13],
	 frame->transform_matrix[14], frame->transform_matrix[15]);
  printf("HasAnimation: %d\n", frame->has_animation);
  printf("HasVisuals  : %d\n", frame->has_visuals);

  printf("SubFrameCount %d\n", frame->subframe_count);

  if(frame->has_animation){
    printf("############ ANIMATION ############\n");
    printf("AnimationCount: %u\n", frame->animation_count);
    printf("AnimationD3DOptions: %08x\n", frame->animation_d3d_options);
    for(int i = 0; i<frame->animation_count; i++)
      printf("AniFrame(DT: %f; Type: %u; {%f %f %f %f})\n",
	     frame->animation[i].dv_time, frame->animation[i].key_type,
	     frame->animation[i].aniA, frame->animation[i].aniB,
	     frame->animation[i].aniC, frame->animation[i].aniD);
    printf("############ END ANIMATION ############\n");
  }

  if(frame->has_visuals)
    pwt_visuals_print(frame->visuals);

  for(int i = 0; i < frame->subframe_count; i++){
    pwt_frame_print(frame->subframes[i]);
  }

  printf("############ END FRAME %s ############\n", frame->name);
}

void pwt_print(PWT* pwt){
  printf("MIN          : {%f, %f, %f}\n",
	 pwt->global_min.X, pwt->global_min.Y, pwt->global_min.Z);
  printf("MAX          : {%f, %f, %f}\n",
	 pwt->global_max.X, pwt->global_max.Y, pwt->global_max.Z);

  printf("VeryClose:   : %d\n", pwt->veryclose);
  printf("PrettyClose  : %d\n", pwt->prettyclose);

  printf("IncVertices  : %d\n", pwt->dowrite_vertices);
  printf("IncNormals   : %d\n", pwt->dowrite_normals);
  printf("VtexAccuracy : %d\n", pwt->vertex_bit_accuracy);
  printf("VtexAccuracy1: %d\n", pwt->vertex_bit_accuracy_1);
  printf("NormAccuracy : %d\n", pwt->normal_bit_accuracy);
  printf("unk_f44      : %d\n", pwt->unk_f44);
  printf("unk_f48      : %d\n", pwt->unk_f48);
  printf("VertexCount  : %d\n", pwt->vertex_count);
  printf("NormalCount  : %d\n", pwt->normal_count);
  printf("FaceCount    : %d\n", pwt->face_count);
  printf("unk_v40      : %d\n", pwt->unk_f40);

  printf("PWT_FRAME:\n");
  pwt_frame_print(pwt->frames);
}

void pwt_visuals_free(PWT_Visuals* visuals){
  free(visuals->vertices);
  free(visuals->normals);
  free(visuals->faces);
  free(visuals->face_normals);
  free(visuals->texmapU);
  free(visuals->texmapV);
  free(visuals->face_details);
  for(int i = 0; i < visuals->texture_count; i++)
    free(visuals->texture_paths[i]);
  free(visuals->texture_paths);
  free(visuals);
}

void pwt_frame_free(PWT_Frame* frame){
  if(frame->name) free(frame->name);
  if(frame->has_animation) free(frame->animation);
  if(frame->has_visuals) pwt_visuals_free(frame->visuals);
  for(int i = 0; i < frame->subframe_count; i ++)
    pwt_frame_free(frame->subframes[i]);
  if(frame->subframes) free(frame->subframes);
  free(frame);
}

void pwt_free(PWT* wt){
  pwt_frame_free(wt->frames);
  free(wt);
}
