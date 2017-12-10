#ifdef __cplusplus
extern "C" {
#endif

#ifndef WLDS_DECODE
#define WLDS_DECODE

#include <uuid/uuid.h>
#include <stdbool.h>

#include "dataaccessors.h"

typedef struct {
  float X, Y, Z;
} PWT_XYZ;

typedef unsigned int PWT_Face[3];

typedef float MAT44[4*4];

typedef struct {
  float dv_time;
  unsigned int key_type;
  float aniA, aniB, aniC, aniD;
} PWT_Animation;

typedef struct {
  uint8_t texture_name;
  uint32_t texture_color;
  float texture_power;
  PWT_XYZ emmisivity;
  PWT_XYZ specularity;
} FaceDetails;

typedef struct {
  uint32_t vcount, ncount, fcount;
  uint8_t texture_count;
  uint32_t vertex_count, vertexcomp_count;
  PWT_XYZ bboxmin;
  uint8_t unused_vbits_x;
  uint8_t unused_vbits_y;
  uint8_t unused_vbits_z;
  PWT_XYZ* vertices;
  uint32_t normal_count, normalcomp_count;
  PWT_XYZ norm_bboxmin;
  PWT_XYZ norm_bboxmax;
  uint8_t unused_nbits_x;
  uint8_t unused_nbits_y;
  uint8_t unused_nbits_z;
  PWT_XYZ* normals;
  PWT_Face* faces;
  PWT_Face* face_normals;
  float* texmapU;
  float* texmapV;
  FaceDetails* face_details;
  char** texture_paths;
} PWT_Visuals;

typedef struct PWT_Frame {
  uint32_t subframe_count;
  char* name;
  MAT44 transform_matrix;
  bool has_animation, has_visuals;
  uint32_t animation_count;
  uint32_t animation_d3d_options;
  PWT_Animation* animation;
  PWT_Visuals* visuals;
  struct PWT_Frame** subframes;
} PWT_Frame;

typedef struct {
  PWT_XYZ global_min;
  PWT_XYZ global_max;
  uint32_t veryclose, prettyclose;
  bool dowrite_vertices, dowrite_normals;
  uint32_t vertex_bit_accuracy, vertex_bit_accuracy_1;
  uint32_t normal_bit_accuracy;
  uint32_t unk_f44, unk_f48;
  uint32_t vertex_count, normal_count, face_count;
  uint32_t unk_f40;
  PWT_Frame* frames;
} PWT;

PWT* pwt_extract(DataAccessor*);

void pwt_print(PWT* wt);

void pwt_free(PWT* wt);

#endif

#ifdef __cplusplus
}
#endif
