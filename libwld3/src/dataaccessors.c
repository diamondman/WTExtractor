#include <endian.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataaccessors.h"

#define MIN(a,b) (((a)<(b))?(a):(b))

//////////////////// BUFF ACCESSOR
typedef struct DataAccessor_BUFFINT {
  DataAccessor func;

  size_t length;
  const uint8_t* buff;
  size_t offset;
} DataAccessor_BUFFINT;

static size_t da_buff_length(DataAccessor* da_ext){
  DataAccessor_BUFFINT* da = (DataAccessor_BUFFINT*)da_ext;
  return da->length;
};

static size_t da_buff_remaining(DataAccessor* da_ext){
  DataAccessor_BUFFINT* da = (DataAccessor_BUFFINT*)da_ext;
  return da->length - da->offset;
};

static size_t da_buff_read(DataAccessor* da_ext, void *buffer, size_t bytes){
  DataAccessor_BUFFINT* da = (DataAccessor_BUFFINT*)da_ext;
  bytes = MIN(bytes, da->length - da->offset);
  if(buffer)
    memcpy(buffer, da->buff + da->offset, bytes);
  da->offset += bytes;
  return bytes;
}

static int da_buff_seek(DataAccessor* da_ext, off_t offset, int origin){
  DataAccessor_BUFFINT* da = (DataAccessor_BUFFINT*)da_ext;
  off_t final = offset;
  switch(origin) {
  case SEEK_SET:
    break;
  case SEEK_CUR:
    final += da->offset;
    break;
  case SEEK_END:
  default:
    final += da->length;
  }
  if(final > (off_t)(da->length) | final < 0) return -1;
  da->offset = final;
  return 0;
}

static int da_buff_tell(DataAccessor* da_ext){
  DataAccessor_BUFFINT* da = (DataAccessor_BUFFINT*)da_ext;
  return da->offset;
}

static int da_buff_memcmp(DataAccessor* da_ext, const uint8_t* buff, size_t bytes){
  DataAccessor_BUFFINT* da = (DataAccessor_BUFFINT*)da_ext;
  if(bytes > da->length - da->offset) return 1;
  int res = memcmp(&da->buff[da->offset], buff, bytes);
  da->offset += bytes;
  return res;
}

static int da_buff_strchrpos(DataAccessor* da_ext, uint8_t chr){
  DataAccessor_BUFFINT* da = (DataAccessor_BUFFINT*)da_ext;
  uint8_t* firstchar = strchr(da->buff + da->offset, chr);
  if(firstchar == NULL) return -1;
  return firstchar - da->buff - da->offset;
}

static int da_buff_strstrpos(DataAccessor* da_ext, uint8_t* str){
  DataAccessor_BUFFINT* da = (DataAccessor_BUFFINT*)da_ext;
  uint8_t* firstchar = strstr(&da->buff[da->offset], str);
  if(firstchar == NULL) return -1;
  return firstchar - da->buff - da->offset;
}

static void da_buff_free(DataAccessor* da_ext){
  DataAccessor_BUFFINT* da = (DataAccessor_BUFFINT*)da_ext;
  free(da);
}

DataAccessor* openBufferAccessor(const uint8_t* buffer, size_t len){
  DataAccessor_BUFFINT* acc = malloc(sizeof(DataAccessor_BUFFINT));
  acc->func.length = da_buff_length;
  acc->func.remaining = da_buff_remaining;
  acc->func.read = da_buff_read;
  acc->func.seek = da_buff_seek;
  acc->func.tell = da_buff_tell;
  acc->func.memcmp = da_buff_memcmp;
  acc->func.strchrpos = da_buff_strchrpos;
  acc->func.strstrpos = da_buff_strstrpos;
  acc->func.free = da_buff_free;

  acc->buff = buffer;
  acc->length = len;
  acc->offset = 0;

  return &acc->func;
}


//////////////////// FILE ACCESSOR
typedef struct DataAccessor_FILEINT {
  DataAccessor func;
  size_t length;
  FILE* file;
} DataAccessor_FILEINT;

static size_t da_file_length(DataAccessor* da_ext){
  DataAccessor_FILEINT* da = (DataAccessor_FILEINT*)da_ext;
  return da->length;
};

static size_t da_file_remaining(DataAccessor* da_ext){
  DataAccessor_FILEINT* da = (DataAccessor_FILEINT*) da_ext;
  return da->length - da->func.tell(da_ext);
};

static size_t da_file_read(DataAccessor* da_ext, void *buffer, size_t bytes){
  DataAccessor_FILEINT* da = (DataAccessor_FILEINT*) da_ext;
  return fread(buffer, 1, bytes, da->file);
}

static int da_file_seek(DataAccessor* da_ext, off_t offset, int origin){
  DataAccessor_FILEINT* da = (DataAccessor_FILEINT*) da_ext;
  printf("SEEK FROM %d\n", ftell(da->file));
  int res = fseek(da->file, offset, origin);
  printf("SEEK TO %d\n", ftell(da->file));
  return res;
}

static int da_file_tell(DataAccessor* da_ext){
  DataAccessor_FILEINT* da = (DataAccessor_FILEINT*) da_ext;
  return ftell(da->file);
}

//Just returns 0 if =, 1 if not for now
static int da_file_memcmp(DataAccessor* da_ext, const uint8_t* buff, size_t bytes){
  DataAccessor_FILEINT* da = (DataAccessor_FILEINT*) da_ext;
  if(bytes > da->length - da->func.tell(da_ext)) return 1;
  uint8_t byte;
  for(int i = 0; i < bytes; i++){
    if(fread(&byte, 1, 1, da->file) != 1) return 1;
    if(byte != buff[i]) return 1;
  }
  return 0;
}

static int da_file_strchrpos(DataAccessor* da_ext, uint8_t chr){
  DataAccessor_FILEINT* da = (DataAccessor_FILEINT*) da_ext;
  size_t oldpos = ftell(da->file);
  uint8_t byte;
  while(fread(&byte, 1, 1, da->file) == 1){
    if(byte == chr){
      size_t newpos = ftell(da->file);
      fseek(da->file, oldpos, SEEK_SET);
      return newpos-oldpos-1;
    }
  }
  return -1;
}

static int da_file_strstrpos(DataAccessor* da_ext, uint8_t* str){
  DataAccessor_FILEINT* da = (DataAccessor_FILEINT*) da_ext;
  size_t oldpos = ftell(da->file);
  uint8_t byte;
  size_t stroffset = 0;
  size_t instr_len = strlen(str);
  int file_pos_start = -1;

  while(fread(&byte, 1, 1, da->file) == 1){
    if(byte == str[stroffset]){
      if(file_pos_start == -1) file_pos_start = ftell(da->file);
      stroffset += 1;
      if(stroffset, instr_len){
	fseek(da->file, oldpos, SEEK_SET);
	return file_pos_start-oldpos-1;
      }
    }else{
      file_pos_start = -1;
      stroffset = 0;
    }
  }

  return -1;
}

static void da_file_free(DataAccessor* da_ext){
  DataAccessor_FILEINT* da = (DataAccessor_FILEINT*) da_ext;
  if(da == NULL) return;
  printf("ABOUT TO CLOSE FILE!\n");
  if(da->file) fclose(da->file);
  printf("FILE CLOSED!\n");
  free(da);
}

DataAccessor* openFileAccessor(const char *filename){
  FILE *f = fopen(filename, "rb");
  if(f == NULL) return NULL;

  DataAccessor_FILEINT* acc = malloc(sizeof(DataAccessor_FILEINT));
  acc->func.length = da_file_length;
  acc->func.remaining = da_file_remaining;
  acc->func.read = da_file_read;
  acc->func.seek = da_file_seek;
  acc->func.tell = da_file_tell;
  acc->func.memcmp = da_file_memcmp;
  acc->func.strchrpos = da_file_strchrpos;
  acc->func.strstrpos = da_file_strstrpos;
  acc->func.free = da_file_free;

  acc->file = f;

  fseek(f, 0L, SEEK_END);
  acc->length = ftell(f);
  rewind(f);

  return &acc->func;
}
