#include <stdio.h>

#include "pwt_decode.h"
#include "dataaccessors.h"

int main(int args, char** argv){
  if(args == 1){
    fprintf(stderr, "Missing file path.\n");
    return 1;
  }

  DataAccessor* acc = openFileAccessor(argv[1]);
  PWT* pwt = pwt_extract(acc);

  if(pwt>0){
    pwt_print(pwt);
    pwt_free(pwt);
  }else
    fprintf(stderr, "ERROR! DONE!\n");

  if(acc){
    fprintf(stderr, "OFFSET: %zu; Len %zu\n", ftell(acc->dat.file), acc->length);
    acc->free(acc);
  }

  return 0;
}
