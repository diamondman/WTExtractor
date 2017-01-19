#include <endian.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define __USE_XOPEN
#include <time.h>

#include "wld3_extract.h"

//typedef struct reader_{
//  uint8_t* fbuff;
//  size_t fsize;
//  uint8_t* ptr;
//} Reader;
//
//Reader* readerCreate(uint8_t* fbuff, size_t fsize){
//  Reader* r = malloc(sizeof(Reader));
//  r->fbuff = fbuff;
//  r->fsize = fsize;
//  r->ptr = fbuff;
//  return r;
//}
//
//void readerDelete(Reader* r){
//  free(r);
//}

typedef struct{
  uint8_t len;
  uint8_t* buff;
  uint8_t last_crypt_byte;
  uint32_t index;
} EncryptTable;

typedef struct fileinfo{
  char headerval[EXT_BUFF_LEN];
  enum resource_class rc;
  char outext[EXT_BUFF_LEN];
} FileInfo;

const FileInfo file_type_info[] = {
  {"png", media, "png"},
  {"jpg", media, "jpg"},
  {"wav", media, "wav"},
  {"mid", media, "mid"},
  {"rmi", media, "rmi"},
  {"wt",  model, "pwt"},
  {"cfg", data,  "cfg"},
  {"dat", data,  "dat"},
  {"ini", data,  "ini"},
  {"txt", data,  "txt"},
  {"cab", media, "cab"},
  {"tmp", media, "tmp"},
};

const uint8_t WTFIELD_MIN_LEN [9] = {
  0, 4, 4, 4, 16, 16, 4, 5, 4
};


uint8_t calc_header_maxlen(uint8_t headerlens[], uint8_t headercount){
  uint8_t max = 0;
  for(int i = 0; i < headercount; i++)
    if(headerlens[i] > max)
      max = headerlens[i];
  return max;
}

uint8_t calc_hash_byte_TYPEMODEL
(uint8_t* rawheaders[], uint8_t headerlens[], uint8_t headercount){
  printf("CALC MODEL HASH BYTE\n");
  uint8_t maxlen = calc_header_maxlen(headerlens, headercount);
  uint8_t enc_byte = 0;
  for(int i=0; i<headercount; i++)
    if(maxlen>0)
      for(int j=0; j<maxlen; j++)
	if(headerlens[i] >= 1)
	  enc_byte ^= rawheaders[i][j % headerlens[i]];
  return enc_byte;

}
uint8_t calc_hash_byte_TYPEMEDIADATA
(uint8_t* rawheaders[], uint8_t headerlens[], uint8_t headercount){
  printf("CALC MEDIA HASH BYTE\n");
  uint8_t maxlen = calc_header_maxlen(headerlens, headercount);
  uint8_t enc_byte = 0;
  uint8_t c;
  for(int i=0; i<headercount; i++)
    if(maxlen>0)
      for(int j=0; j<maxlen; j++){
	if(headerlens[i] >= 1)
	  c = rawheaders[i][j % headerlens[i]];
	else
	  c = 0;
	enc_byte ^= i + j + c * (j + 1);
      }

  return enc_byte;
}

////////////////
EncryptTable* createEncryptTable(){
  EncryptTable* table = malloc(sizeof(EncryptTable));
  table->len = 0;
  table->buff = NULL;
  table->last_crypt_byte = 0;
  table->index = 0;
  return table;
}

EncryptTable* calc_enc_key_table_TYPEDATA
(uint8_t* rawheaders[], uint8_t headerlens[],
 uint8_t headercount, EncryptTable* table){

  if(table == NULL) table = createEncryptTable();

  if(table->len == 0){
    table->len = calc_header_maxlen(headerlens, headercount);
    table->buff = malloc(table->len);
  }

  uint8_t enc_byte = calc_hash_byte_TYPEMEDIADATA
    (rawheaders, headerlens, headercount);
  memset(table->buff, enc_byte, table->len);

  for(int i=0; i<table->len; i++){
    uint8_t chr_index = i + 7;
    for(int j=0; j<headercount; j++){
      if(headerlens[j] >= 1)
	table->buff[i] ^= rawheaders[j][chr_index % headerlens[j]];
      chr_index += 13;
    }
  }
  return table;
}

EncryptTable* calc_enc_key_table_TYPEMEDIA
(uint8_t* rawheaders[], uint8_t headerlens[],
 uint8_t headercount, EncryptTable* table){

  if(table == NULL) table = createEncryptTable();

  if(table->len == 0){
    table->len = calc_header_maxlen(headerlens, headercount);
    table->buff = malloc(table->len);
  }

  uint8_t enc_byte = calc_hash_byte_TYPEMEDIADATA
    (rawheaders, headerlens, headercount);
  memset(table->buff, enc_byte, table->len);

  for(int i=0; i<table->len; i++)
    for(int j=0; j<headercount; j++)
      if(headerlens[j] >= 1)
	table->buff[i] ^= rawheaders[j][(j + i) % headerlens[j]];
  return table;
}

EncryptTable* calc_enc_key_table_TYPEMODEL
(uint8_t* rawheaders[], uint8_t headerlens[],
 uint8_t headercount, EncryptTable* table){

  if(table == NULL) table = createEncryptTable();

  if(table->len == 0){
    table->len = calc_header_maxlen(headerlens, headercount);
    table->buff = malloc(table->len);
  }

  uint8_t enc_byte = calc_hash_byte_TYPEMODEL
    (rawheaders, headerlens, headercount);
  memset(table->buff, enc_byte, table->len);

  for(int i=0; i<table->len; i++)
    for(int j=0; j<headercount; j++)
      if(headerlens[j] >= 1)
	table->buff[i] ^= rawheaders[j][i % headerlens[j]];
  return table;
}


uint8_t decodeByte(EncryptTable* table, uint8_t inbyte){
  uint8_t res = inbyte ^ table->last_crypt_byte ^
      table->buff[table->index % table->len];
  table->index += 1;
  table->last_crypt_byte = inbyte;
  return res;
}

uint32_t readintcrypt(EncryptTable* table, uint8_t a,
			uint8_t b, uint8_t c, uint8_t d){
  a = decodeByte(table, a);
  b = decodeByte(table, b);
  c = decodeByte(table, c);
  d = decodeByte(table, d);
  return le32toh(d<<24 | c << 16 | b << 8 | a);
}

char* read_str_crypt(EncryptTable* table, uint8_t* ptr, uint32_t cnt){
  char* outbuff = malloc(cnt+1);
  memcpy(outbuff, ptr, cnt);
  for(int i = 0; i < cnt; i++)
    outbuff[i] = decodeByte(table, outbuff[i]);
  outbuff[cnt] = 0;
  return outbuff;
}

void wtloadUUID(uuid_t u, uint8_t* inbuff){
  u[0] = inbuff[3];
  u[1] = inbuff[2];
  u[2] = inbuff[1];
  u[3] = inbuff[0];
  u[4] = inbuff[5];
  u[5] = inbuff[4];
  u[6] = inbuff[7];
  u[7] = inbuff[6];
  for(int i = 8; i < 16; i++){
    u[i] = inbuff[i];
  }
}

#define WT_HEADER_STR "WildTangent 3D 300 Compressed and Patented\r\nConverted by XtoWT: "

WLD3* wld3_extract(uint8_t* fbuff, size_t fsize){
  //Reader *f = readerCreate(fbuff, fsize);
  uint8_t *ptr = fbuff;
  uint8_t headerlens[9];
  uint8_t* rawheaders[9];
  struct tm tm;
  EncryptTable table;
  WLD3* wt;


  wt = malloc(sizeof(WLD3));
  memset(wt, 0, sizeof(WLD3));

  if(memcmp(ptr, "WLD3", 4)){
    printf("Bad Magic\n");
    printf("%.*s\n", 4, ptr);
    goto FAIL;
  }
  memcpy(wt->magic, ptr, 4);
  ptr += 4;

  if(*ptr++ != '.'){
    printf("Invalid Format: Expected a dot after WLD3 magic.\n");
    goto FAIL;
  }

  uint8_t* firstspace = strchr(ptr, ' ');
  size_t typelen = (int)(firstspace-ptr);
  if(firstspace == NULL){
    printf("Invalid format: No end to typeext detected.\n");
    goto FAIL;
  }
  if(typelen > MAX_EXT_LEN){
    printf("Invalid format: Typeext too large (%zu).\n", typelen);
    goto FAIL;
  }
  memcpy(wt->outext, ptr, typelen);
  ptr += typelen+1;

  if(strncmp(ptr, WT_HEADER_STR, sizeof(WT_HEADER_STR)-1) != 0){
    printf("Invalid format: Incorrect Magic line. Unknown format.\n");
    //printf("%.*s\n", sizeof(WT_HEADER_STR)-1, WT_HEADER_STR);
    //printf("%.*s\n", sizeof(WT_HEADER_STR)-1, ptr);
  }
  wt->formatver = 300;
  ptr += sizeof(WT_HEADER_STR)-1;

  //Text Header Create Time
  ptr = strptime(ptr, "%a %b %d %H:%M:%S %Y", &tm);
  if(ptr == NULL){
    printf("Failed to parse creatime date from text header.\n");
    goto FAIL;
  }
  //printf("Y: %d; M: %d; D: %d; H: %d; MIN: %d; S: %d\n",
  //  tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
  //  tm.tm_hour, tm.tm_min, tm.tm_sec);
  tm.tm_isdst = -1;/* tells mktime() to determine DST*/
  wt->created_unimportant = mktime(&tm);
  if(wt->created_unimportant == -1){
    printf("Failed to extract EPOCH time from text header.\n");
    goto FAIL;
  }

  if(strncmp(ptr, "\n\r\n", 3) != 0){
    printf("Format Incorrect: Expected newline after date string \n");
    goto FAIL;
  }
  ptr += 3;

  uint8_t* commentend_ptr = strstr(ptr, ".START\n");
  if((int)(commentend_ptr-ptr)-2){
    wt->comment = malloc((int)(commentend_ptr-ptr)-2);
    memcpy(wt->comment, ptr, (int)(commentend_ptr-ptr)-2);
  }else
    wt->comment = 0;
  ptr = commentend_ptr + 7;

  uint8_t headercount = (*ptr++) - 0xC5;
  if(headercount != 9){
    printf("Only know how to use files with 9 headers, not %d. Exiting.",
	   headercount);
    goto FAIL;
  }

  uint8_t decrypt_byte = 0x39;
  for(int i = 0; i<headercount; i++){
    headerlens[i] = (*ptr++) - decrypt_byte;
    if(headerlens[i] > 80){
      printf("Invalid Format: Header %d has a length over 80.\n", i);
      goto FAIL;
    }
    if(headerlens[i] < WTFIELD_MIN_LEN[i]){
      printf("Invalid Format: Header %d is too short.\n", i);
      goto FAIL;
    }
    decrypt_byte += 13;
    //printf("%d ", headerlens[i]);
  }

  for(int i = 0; i<headercount; i++){
    rawheaders[i] = malloc(headerlens[i]);
    memcpy(rawheaders[i], ptr, headerlens[i]);
    ptr += headerlens[i];
    //for(int j = 0; j<headerlens[i]; j++)
    //  printf(" %02x '%c'", *(rawheaders[i]+j), *(rawheaders[i]+j));
    //printf("\n");
  }

  // COPYRIGHT
  wt->copyright = calloc(headerlens[0]+1, 1);
  memcpy(wt->copyright, rawheaders[0], headerlens[0]);
  printf("%s\n", wt->copyright);

  //CreatedDate
  wt->createddate = (time_t)le32toh(*((uint32_t*)rawheaders[1]));
  printf("CREATED %u\n", (unsigned int)wt->createddate);

  //StartValieDate
  wt->startvaliedate = (time_t)le32toh(*((uint32_t*)rawheaders[2]));
  printf("VALIDD  %u\n", (unsigned int)wt->startvaliedate);

  //ExpireDate
  wt->expiredate = (time_t)le32toh(*((uint32_t*)rawheaders[3]));
  printf("Expire  %u\n", (unsigned int)wt->expiredate);

  //WTVerUUID
  wtloadUUID(wt->wtversionUUID, rawheaders[4]);
  char uuid_str[37];
  uuid_unparse(wt->wtversionUUID, uuid_str);
  printf("UUID: %s\n", uuid_str);

  //ResourceUUID
  wtloadUUID(wt->resourceUUID, rawheaders[5]);
  uuid_unparse(wt->resourceUUID, uuid_str);
  printf("UUID: %s\n", uuid_str);

  //LicenseType
  memcpy(wt->licensetype, rawheaders[6], 4);
  printf("LicenseType: %s\n", wt->licensetype);

  //Check Body Marker
  if(memcmp(rawheaders[7]+(headerlens[7]-5), ".BODY", 5) != 0){
    printf("Invalid Format: Wrong '.BODY' location");
    goto FAIL;
  }

  //Encodeversion
  wt->encodeversion = le32toh(*((uint32_t*)rawheaders[8]));
  if(wt->encodeversion != 200 && wt->encodeversion != 300){
    printf("Invalid Format: Unknown Encode Type %d\n", wt->encodeversion);
    goto FAIL;
  }
  printf("EncodeVersion: %u\n", wt->encodeversion);

  //ExtraURLs
  if(wt->encodeversion >= 300){
    calc_enc_key_table_TYPEMEDIA
      (rawheaders, headerlens, headercount, &table);
    //self.urls = {};
    printf("\n\nURLS:\n");
    while(1){
      uint8_t urltype = decodeByte(&table, *ptr++);
      uint32_t url_len = readintcrypt(&table, *ptr, *(ptr+1),
				      *(ptr+2), *(ptr+3));
      ptr += 4;
      uint32_t always300_0 = readintcrypt(&table, *ptr, *(ptr+1),
					  *(ptr+2), *(ptr+3));
      ptr += 4;
      uint32_t always300_1 = readintcrypt(&table, *ptr, *(ptr+1),
					  *(ptr+2), *(ptr+3));
      ptr += 4;
      printf("0x%02x %d %d %d\n", urltype, url_len, always300_0,
	     always300_1);
      if(url_len == 0 && urltype == 0) break;

      char* urlbody = read_str_crypt(&table, ptr, url_len);
      printf("URL: %s\n", urlbody);
      free(urlbody);
      ptr += url_len;
      //self.urls.setdefault(urltype, []).append(urlbody);
    }
    printf("\n\n");
  }

  //EncodeType
  int typeindex = -1;
  enum resource_class encodetype;
  size_t outext_len = strlen(wt->outext);
  for(int i = 0; i < sizeof(file_type_info)/sizeof(FileInfo); i++){
    if(memcmp(file_type_info[i].headerval, wt->outext, outext_len) == 0){
      memcpy(wt->outext, file_type_info[i].outext, typelen);
      encodetype = file_type_info[i].rc;
      typeindex = i;
      //printf("Found Index %d\n\n\n", i);
      break;
    }
  }
  if(typeindex == -1){
    printf("No known way to extract type '%s'", wt->outext);
    goto FAIL;
  }

  //EncodeTableCalculation
  printf("TYPE %d\n", encodetype);
  printf("MODEL TYPE %d\n", model);
  if(encodetype == model){
    printf("CALCING FOR MODEL\n");
    calc_enc_key_table_TYPEMODEL
      (rawheaders, headerlens, headercount, &table);
  }else if(encodetype == media){
    calc_enc_key_table_TYPEMEDIA
      (rawheaders, headerlens, headercount, &table);
  }else if(encodetype == data){
    calc_enc_key_table_TYPEDATA
      (rawheaders, headerlens, headercount, &table);
  }else{
    printf("Error: Unknown resource class selected.");
    goto FAIL;
  }

  for(int i = 0; i < table.len; i++){
    printf(" %02x", table.buff[i]);
  }
  printf("\n");

  wt->payload_len = fsize-(int)(ptr-fbuff);
  wt->payload_data = malloc(wt->payload_len);

  //memcpy(wt->payload_data, ptr, wt->payload_len);
  for(int i = 0; i < wt->payload_len; i++){
    wt->payload_data[i] = decodeByte(&table, *ptr++);
    printf(" %02x", wt->payload_data[i]);
  }
  printf("\n");


 CLEANUP:
  for(int i = 0; i<headercount; i++)
    if(rawheaders[i]){free(rawheaders[i]);rawheaders[i]=0;}
  if(table.buff){free(table.buff); table.buff=0;}
  return wt;

 FAIL:
  if(wt){
    if(wt->comment){free(wt->comment); wt->comment=0;}
    if(wt->payload_data){free(wt->payload_data);wt->payload_data=0;}
    free(wt); wt = NULL;
  }
  goto CLEANUP;
}


  //printf("Payload Size: %zu\n", wt->payload_len);

  //printf("ENC BYTE: 0x%02x\n", encodebyte);

  //for(int i = 0; i < 8; i++){
  //  printf(" %02x", *(ptr+i));
  //}
  //printf("\n");
  //for(int i = 0; i < 8; i++){
  //  if(*(ptr+i) == '\n')
  //    printf(" \\n");
  //  else if (*(ptr+i) == '\r')
  //    printf(" \\r");
  //  else
  //    printf("  %c", *(ptr+i));
  //}
  //printf("\n");
