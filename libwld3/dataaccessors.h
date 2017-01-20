#ifndef _WLD3_DATAACCESSORS
#define _WLD3_DATAACCESSORS

#include <stdint.h>

typedef struct {
  uint8_t type;
  size_t length;
  size_t offset;
  union {
    uint8_t* buff;
    FILE* file;
  } dat;
} DataAccessor;

DataAccessor* openBufferAccessor(uint8_t* buffer, size_t len);

size_t da_remaining(DataAccessor* da);

size_t da_read(DataAccessor* da, void *buffer, size_t bytes);

//Just returns 0 if =, 1 if not for now
int da_memcmp(DataAccessor* da, uint8_t* buff, size_t bytes);

int da_strchrpos(DataAccessor* da, uint8_t chr);

int da_strstrpos(DataAccessor* da, uint8_t* str);


#endif
