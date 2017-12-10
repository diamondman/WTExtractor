#ifdef __cplusplus
extern "C" {
#endif

#ifndef _WLD3_DATAACCESSORS
#define _WLD3_DATAACCESSORS

#include <stdint.h>

typedef struct DataAccessor {
  size_t (*remaining)(struct DataAccessor*);
  size_t (*read)(struct DataAccessor*, void *buffer, size_t bytes);
  int (*seek)(struct DataAccessor*, off_t offset);
  int (*memcmp)(struct DataAccessor*, const uint8_t* buff, size_t bytes);
  int (*strchrpos)(struct DataAccessor*, uint8_t chr);
  int (*strstrpos)(struct DataAccessor*, uint8_t* str);

  uint8_t type;
  size_t length;
  size_t offset;
  union {
    const uint8_t* buff;
    FILE* file;
  } dat;
} DataAccessor;

DataAccessor* openBufferAccessor(const uint8_t* buffer, size_t len);
void freeBufferAccessor(DataAccessor* da);

DataAccessor* openFileAccessor(const char *filename);
void freeFileAccessor(DataAccessor* da);

#endif

#ifdef __cplusplus
}
#endif
