#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _WLD3_DATAACCESSORS
#define _WLD3_DATAACCESSORS

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// Seek origin is one of {SEEK_SET, SEEK_CUR, SEEK_END}.

typedef struct DataAccessor {
  size_t (*length)(struct DataAccessor*);
  size_t (*remaining)(struct DataAccessor*);
  size_t (*read)(struct DataAccessor*, void *buffer, size_t bytes);
  int (*seek)(struct DataAccessor*, off_t offset, int origin);
  int (*tell)(struct DataAccessor*);
  int (*memcmp)(struct DataAccessor*, const uint8_t* buff, size_t bytes);
  int (*strchrpos)(struct DataAccessor*, uint8_t chr);
  int (*strstrpos)(struct DataAccessor*, uint8_t* str);
  void (*free)(struct DataAccessor*);
} DataAccessor;

DataAccessor* openBufferAccessor(const uint8_t* buffer, size_t len);
DataAccessor* openFileAccessor(const char *filename);

#endif

#ifdef __cplusplus
}
#endif
