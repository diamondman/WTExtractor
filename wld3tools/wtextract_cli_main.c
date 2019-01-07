#include <stdio.h>

#include "wld3_extract.h"
#include "dataaccessors.h"

int main(int args, char** argv){
  if(args == 1){
    fprintf(stderr, "Missing file path.\n");
    return 1;
  }

  DataAccessor* acc = openFileAccessor(argv[1]);
  WLD3* wt = wld3_extract(acc);

  if(wt>0){
    wld3_print(wt);
    wld3_free(wt);
  }else
    fprintf(stderr, "ERROR! DONE!\n");

  if(acc) freeFileAccessor(acc);

  return 0;
}
