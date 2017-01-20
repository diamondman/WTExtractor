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

//Just returns 0 if =, 1 if not for now
static int da_buff_memcmp(DataAccessor* da, uint8_t* buff, size_t bytes){
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

DataAccessor* openBufferAccessor(uint8_t* buffer, size_t len){
  DataAccessor* acc = malloc(sizeof(DataAccessor));
  acc->type = 0;
  acc->length = len;
  acc->offset = 0;
  acc->dat.buff = buffer;

  acc->remaining = da_buff_remaining;
  acc->read = da_buff_read;
  acc->memcmp = da_buff_memcmp;
  acc->strchrpos = da_buff_strchrpos;
  acc->strstrpos = da_buff_strstrpos;

  return acc;
}
