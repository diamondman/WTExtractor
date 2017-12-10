#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "wld3_extract.h"
#include "dataaccessors.h"

int main(int args, char** argv){
  if(args == 1){
    printf("Missing file path.\n");
    return 1;
  }

  DataAccessor* acc = openFileAccessor(argv[1]);
  WLD3* wt = wld3_extract(acc);

  if(wt){
    wld3_print(wt);
    wld3_free(wt);
  }else
    printf("ERROR! DONE!\n");

  if(acc) freeFileAccessor(acc);

  return 0;
}
