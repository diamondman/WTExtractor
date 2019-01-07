#include <endian.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataaccessors.h"

#define MIN(a,b) (((a)<(b))?(a):(b))

//////////////////// BUFF ACCESSOR
static size_t da_buff_remaining(DataAccessor* da){
  return da->length - da->offset;
};

static size_t da_buff_read(DataAccessor* da, void *buffer, size_t bytes){
  bytes = MIN(bytes, da->length-da->offset);
  if(buffer)
    memcpy(buffer, da->dat.buff+da->offset, bytes);
  da->offset += bytes;
  return bytes;
}

static int da_buff_seek(DataAccessor* da, off_t offset){
  if(offset > (off_t)(da->length-da->offset))
  if(offset > da->length-da->offset) return -1;
  da->offset += offset;
  return 0;
}

//Just returns 0 if =, 1 if not for now
static int da_buff_memcmp(DataAccessor* da, const uint8_t* buff, size_t bytes){
  if(bytes > da->length - da->offset) return 1;
  int res = memcmp(&da->dat.buff[da->offset], buff, bytes);
  da->offset += bytes;
  return res;
}

static int da_buff_strchrpos(DataAccessor* da, uint8_t chr){
  uint8_t* firstchar = strchr(da->dat.buff+da->offset, chr);
  if(firstchar == NULL) return -1;
  return firstchar-da->dat.buff-da->offset;
}

static int da_buff_strstrpos(DataAccessor* da, uint8_t* str){
  uint8_t* firstchar = strstr(&da->dat.buff[da->offset], str);
  if(firstchar == NULL) return -1;
  return firstchar-da->dat.buff-da->offset;
}

static void da_buff_free(DataAccessor* da){
  free(da);
}

DataAccessor* openBufferAccessor(const uint8_t* buffer, size_t len){
  DataAccessor* acc = malloc(sizeof(DataAccessor));
  acc->type = 0;
  acc->length = len;
  acc->offset = 0;
  acc->dat.buff = buffer;

  acc->remaining = da_buff_remaining;
  acc->read = da_buff_read;
  acc->seek = da_buff_seek;
  acc->memcmp = da_buff_memcmp;
  acc->strchrpos = da_buff_strchrpos;
  acc->strstrpos = da_buff_strstrpos;
  acc->free = da_buff_free;

  return acc;
}


//////////////////// FILE ACCESSOR
static size_t da_file_remaining(DataAccessor* da){
  return da->length - da->offset;
};

static size_t da_file_read(DataAccessor* da, void *buffer, size_t bytes){
  bytes = fread(buffer, 1, bytes, da->dat.file);
  //uint8_t* b = buffer;
  //printf(" %02x %02x %02x %02x\n", *b, *(b+1), *(b+2), *(b+3));
  //float f2 = le32toh(*(int*)buffer);
  //printf("F2 = %f\n", f2);
  //
  //float a = -1;
  //uint8_t* b2 = &a;
  //printf("BYTEBYBYTE %02x %02x %02x %02x\n", *b2, *(b2+1), *(b2+2), *(b2+3));
  //printf("CORRECT    %08x\n", *((int*)b2));

  da->offset += bytes;
  return bytes;
}

static int da_file_seek(DataAccessor* da, off_t offset){
  if(offset > (off_t)(da->length-da->offset)) return -1;
  int res = fseek(da->dat.file, offset, SEEK_CUR);
  if(res == 0){
    da->offset += offset;
    return 0;
  }
  return -1;
}

//Just returns 0 if =, 1 if not for now
static int da_file_memcmp(DataAccessor* da, const uint8_t* buff, size_t bytes){
  if(bytes > da->length - da->offset) return 1;
  uint8_t byte;
  for(int i = 0; i < bytes; i++){
    if(fread(&byte, 1, 1, da->dat.file) != 1) return 1;
    if(byte != buff[i]) return 1;
  }
  da->offset += bytes;
  return 0;
}

static int da_file_strchrpos(DataAccessor* da, uint8_t chr){
  size_t oldpos = ftell(da->dat.file);
  uint8_t byte;
  while(fread(&byte, 1, 1, da->dat.file) == 1){
    if(byte == chr){
      size_t newpos = ftell(da->dat.file);
      fseek(da->dat.file, oldpos, SEEK_SET);
      return newpos-oldpos-1;
    }
  }
  return -1;
}

static int da_file_strstrpos(DataAccessor* da, uint8_t* str){
  size_t oldpos = ftell(da->dat.file);
  uint8_t byte;
  size_t stroffset = 0;
  size_t instr_len = strlen(str);
  int file_pos_start = -1;

  while(fread(&byte, 1, 1, da->dat.file) == 1){
    if(byte == str[stroffset]){
      if(file_pos_start == -1) file_pos_start = ftell(da->dat.file);
      stroffset += 1;
      if(stroffset, instr_len){
	fseek(da->dat.file, oldpos, SEEK_SET);
	return file_pos_start-oldpos-1;
      }
    }else{
      file_pos_start = -1;
      stroffset = 0;
    }
  }

  return -1;
}

static void da_file_free(DataAccessor* da){
  if(da == NULL) return;
  printf("ABOUT TO CLOSE FILE!\n");
  if(da->dat.file) fclose(da->dat.file);
  printf("FILE CLOSED!\n");
  free(da);
}

DataAccessor* openFileAccessor(const char *filename){
  FILE *f = fopen(filename, "rb");
  if(f == NULL) return NULL;

  DataAccessor* acc = malloc(sizeof(DataAccessor));
  fseek(f, 0L, SEEK_END);
  acc->length = ftell(f);
  rewind(f);

  acc->type = 1;
  acc->offset = 0;
  acc->dat.file = f;

  acc->remaining = da_file_remaining;
  acc->read = da_file_read;
  acc->seek = da_file_seek;
  acc->memcmp = da_file_memcmp;
  acc->strchrpos = da_file_strchrpos;
  acc->strstrpos = da_file_strstrpos;
  acc->free = da_file_free;

  return acc;
}
