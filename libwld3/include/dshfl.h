/*
 * De-SHuFfLer used to decode WildTangent encoded class files used for
 * copy protection.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DSHFL_
#define _DSHFL_

#include <stdbool.h>

#include "dataaccessors.h"

// De-SHuFfLer data types.
typedef struct DSHFL_Header_s {
  unsigned int length;
} DSHFL_Header;

typedef struct DSHFL_EncodedChunk_s {
  unsigned int a;
  unsigned int b;
} DSHFL_EncodedChunk;

typedef struct DSHFL_DecodedChunk_s {
  unsigned char dat[8];
} DSHFL_DecodedChunk;

typedef struct DSHFL_s {
  DataAccessor* acc;
  DSHFL_Header header;
  bool valid;
} DSHFL;

void DSHFL_decodeChunk(const DSHFL_EncodedChunk *in, DSHFL_DecodedChunk *out);

DSHFL* DSHFL_create(DataAccessor* acc);
void DSHFL_free(DSHFL* dshfl);
size_t DSHFL_decodeNextChunk(DSHFL* dshfl, DSHFL_DecodedChunk *out);
size_t DSHFL_decodeAllChunks(DSHFL* dshfl, unsigned char* buffout);

#endif

#ifdef __cplusplus
}
#endif
