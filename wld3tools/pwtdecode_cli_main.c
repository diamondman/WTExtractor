#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "pwt_decode.h"
#include "dataaccessors.h"

int main(int args, char** argv){
  if(args == 1){
    printf("Missing file path.\n");
    return 1;
  }

  DataAccessor* acc = openFileAccessor(argv[1]);
  PWT* pwt = pwt_extract(acc);

  if(pwt){
    pwt_print(pwt);
    pwt_free(pwt);
  }else
    printf("ERROR! DONE!\n");

  if(acc){
    printf("OFFSET: %zu; Len %zu\n", ftell(acc->dat.file), acc->length);
    freeFileAccessor(acc);
  }

  return 0;
}
