#ifndef _WLD3_DATAACCESSORS
#define _WLD3_DATAACCESSORS

#include <stdint.h>

typedef struct DataAccessor {
  size_t (*remaining)(struct DataAccessor*);
  size_t (*read)(struct DataAccessor*, void *buffer, size_t bytes);
  int (*memcmp)(struct DataAccessor*, uint8_t* buff, size_t bytes);
  int (*strchrpos)(struct DataAccessor*, uint8_t chr);
  int (*strstrpos)(struct DataAccessor*, uint8_t* str);

  uint8_t type;
  size_t length;
  size_t offset;
  union {
    uint8_t* buff;
    FILE* file;
  } dat;
} DataAccessor;

DataAccessor* openBufferAccessor(uint8_t* buffer, size_t len);

DataAccessor* openFileAccessor(FILE* f);

#endif
