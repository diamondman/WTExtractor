#include <stdio.h>

#include "dshfl.h"
#include "dataaccessors.h"

int main(int argc, char* argv[]){
  int ret = 0;
  if(argc == 1){
    fprintf(stderr,
            "Decodes WT encoded class files used for copy protection.\n"
            "Usage: %s ENCODED_FILE\n",
            "Missing file path.\n",
            argv[0]);
    ret = 1;
    goto FINISH;
  }

  DataAccessor* acc = openFileAccessor(argv[1]);
  if(acc == NULL) {
    fprintf(stderr, "Failed to create File Accessor.\n");
    ret = 2;
    goto FINISH;
  }

  DSHFL* dshfl = DSHFL_create(acc);
  if(dshfl == NULL) {
    fprintf(stderr, "Failed to create DeSHuFfLer\n");
    ret = 2;
    goto FINISH;
  }
  if(!dshfl->valid) {
    fprintf(stderr,
            "File too short! Header demands %d bytes, but only %d available!\n",
            dshfl->header.length, dshfl->acc->remaining(dshfl->acc));
    ret = 3;
    goto FINISH;
  }

  DSHFL_DecodedChunk out;
  size_t chunkLen;
  while(chunkLen = DSHFL_decodeNextChunk(dshfl, &out))
    fwrite(&out, chunkLen, 1, stdout);
  fprintf(stderr, "Decoded %d bytes.\n", dshfl->header.length);

 FINISH:
  if(dshfl) DSHFL_free(dshfl);
  if(acc) freeFileAccessor(acc);
  return ret;
}
