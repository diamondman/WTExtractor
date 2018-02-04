#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WLDS_EXTRACT
#define WLDS_EXTRACT

#include <uuid/uuid.h>
#include <stdbool.h>

#include "dataaccessors.h"

enum resource_class{
  model,
  media,
  data
};

#define MAX_EXT_LEN 3
#define EXT_BUFF_LEN (MAX_EXT_LEN+1)

typedef struct ExtraStringLL {
  uint8_t type;
  uint32_t len;
  uint32_t always300_0;
  uint32_t always300_1;
  char* buff;
  struct ExtraStringLL* next;
} ExtraStringLL;

typedef struct WLD3{
  //uint8_t magic[4];
  uint8_t outext[EXT_BUFF_LEN];
  uint16_t formatver;
  //time_t created_unimportant;
  char* comment;
  bool cabcompression;
  // Packed Headers
  char* copyright;
  time_t createddate;
  time_t startvaliedate;
  time_t expiredate;
  uuid_t wtversionUUID;
  uuid_t resourceUUID;
  char licensetype[5];
  uint16_t encodeversion;
  //URLS
  ExtraStringLL* urls;
  //Payload
  size_t payload_len;
  uint8_t* payload_data;
} WLD3;

WLD3* wld3_extract(DataAccessor*);

void wld3_print(WLD3* wt);

void wld3_free(WLD3* wt);
#endif

#ifdef __cplusplus
}
#endif
