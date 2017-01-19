#ifndef WLDS_EXTRACT
#define WLDS_EXTRACT

#include <uuid/uuid.h>


enum resource_class{
  model,
  media,
  data
};

#define MAX_EXT_LEN 3
#define EXT_BUFF_LEN (MAX_EXT_LEN+1)

typedef struct WLD3{
  uint8_t magic[4];
  uint8_t outext[EXT_BUFF_LEN];
  uint16_t formatver;
  time_t created_unimportant;
  char* comment;
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

  //Payload
  size_t payload_len;
  uint8_t* payload_data;
} WLD3;

WLD3* wld3_extract(uint8_t*, size_t);

#endif
