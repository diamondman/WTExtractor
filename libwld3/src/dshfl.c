#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "dshfl.h"

#define min(a,b) (((a)<(b))?(a):(b))

const uint32_t key[4] = {0x75BCC20, 0x2CFBC8D8, 0xDF9825C, 0x387BB876};

//TODO: may break on big endian.
void DSHFL_decodeChunk(const DSHFL_EncodedChunk *in, DSHFL_DecodedChunk *out){
  uint32_t int_a = in->a;
  uint32_t int_b = in->b;
  uint32_t shuffler_key = 0xC6EF3720;

  for(int i = 0; i < 32; i++){
    int_b -= (shuffler_key + int_a) ^
             (key[3] + (int_a >> 5)) ^
             (key[2] + 16 * int_a);
    int_a -= (shuffler_key + int_b) ^
             (key[1] + (int_b >> 5)) ^
             (key[0] + 16 * int_b);
    shuffler_key += 0x61C88647;
  }

  //unsigned char data[8];
  out->dat[0] = (int_a >>  0) & 0xff;
  out->dat[1] = (int_a >>  8) & 0xFF;
  out->dat[2] = (int_a >> 16) & 0xFF;
  out->dat[3] = (int_a >> 24) & 0xFF;
  out->dat[4] = (int_b >>  0) & 0xFF;
  out->dat[5] = (int_b >>  8) & 0xFF;
  out->dat[6] = (int_b >> 16) & 0xFF;
  out->dat[7] = (int_b >> 24) & 0xFF;
}

DSHFL* DSHFL_create(DataAccessor* acc) {
  int err = 0;
  DSHFL* dshfl = malloc(sizeof(DSHFL));
  if(dshfl == NULL) return 0;
  memset(dshfl, 0, sizeof(DSHFL));
  dshfl->acc = acc;

  dshfl->acc->read(dshfl->acc, &dshfl->header, sizeof(DSHFL_Header));
  dshfl->valid = dshfl->header.length <= dshfl->acc->remaining(dshfl->acc);
  return dshfl;
}

void DSHFL_free(DSHFL* dshfl) {
  if(dshfl == NULL) return;
  free(dshfl);
}

static size_t DSHFL_offset(DSHFL* dshfl) {
  return dshfl->acc->tell(dshfl->acc) - 4;
}

size_t DSHFL_decodeNextChunk(DSHFL* dshfl, DSHFL_DecodedChunk* out) {
  if(DSHFL_offset(dshfl) < dshfl->header.length){
    size_t ret = min(8, dshfl->header.length - DSHFL_offset(dshfl));
    DSHFL_EncodedChunk in;
    dshfl->acc->read(dshfl->acc, &in, sizeof(DSHFL_EncodedChunk));
    DSHFL_decodeChunk(&in, out);
    return ret;
  }
  return 0;
}

size_t DSHFL_decodeAllChunks(DSHFL* dshfl, unsigned char* buffout) {
  size_t total = 0;
  size_t chunkLen;
  while(chunkLen = DSHFL_decodeNextChunk(dshfl, (DSHFL_DecodedChunk*)buffout)) {
    buffout += sizeof(DSHFL_EncodedChunk);
    total += chunkLen;
  }
  return total;
}
