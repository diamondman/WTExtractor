#include <endian.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <mspack.h>

#define __USE_XOPEN
#include <time.h>

#include "wld3_extract.h"
#include "multifh.h"

#define WT_HEADER_STR "WildTangent 3D 300 Compressed and Patented\r\nConverted by XtoWT: "

typedef struct {
  uint8_t len;
  uint8_t* buff;
  uint8_t last_crypt_byte;
  uint32_t index;
} EncryptTable;

typedef struct {
  char headerval[EXT_BUFF_LEN];
  enum resource_class rc;
  char outext[EXT_BUFF_LEN];
} FileInfo;

static const FileInfo file_type_info[] = {
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

static const uint8_t WTFIELD_MIN_LEN [9] = {
  0, 4, 4, 4, 16, 16, 4, 5, 4
};

static uint8_t calc_header_maxlen(uint8_t headerlens[], uint8_t headercount){
  uint8_t max = 0;
  for(int i = 0; i < headercount; i++)
    if(headerlens[i] > max)
      max = headerlens[i];
  return max;
}

/////////////// HASH BYTE CALCULATION
static uint8_t calc_hash_byte_MODEL
(uint8_t* rawheaders[], uint8_t headerlens[], uint8_t headercount){
  uint8_t maxlen = calc_header_maxlen(headerlens, headercount);
  uint8_t enc_byte = 0;
  for(int i=0; i<headercount; i++)
    if(maxlen>0)
      for(int j=0; j<maxlen; j++)
	if(headerlens[i] >= 1)
	  enc_byte ^= rawheaders[i][j % headerlens[i]];
  return enc_byte;
}

static uint8_t calc_hash_byte_MEDIADATA
(uint8_t* rawheaders[], uint8_t headerlens[], uint8_t headercount){
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

/////////////// HASH TABLE CALCULATION
static EncryptTable* createEncryptTable(){
  EncryptTable* table = malloc(sizeof(EncryptTable));
  table->len = 0;
  table->buff = NULL;
  table->last_crypt_byte = 0;
  table->index = 0;
  return table;
}

void EncryptTable_free(EncryptTable* table){
  if(table){
    if(table->buff){free(table->buff); table->buff=0;}
    free(table);
  }
}

static EncryptTable* get_DATA_hashtable(uint8_t* rawheaders[],
					uint8_t headerlens[],
					uint8_t headercount,
					EncryptTable* table){
  if(table == NULL) table = createEncryptTable();

  if(table->len == 0){
    table->len = calc_header_maxlen(headerlens, headercount);
    table->buff = malloc(table->len);
  }

  uint8_t enc_byte = calc_hash_byte_MEDIADATA
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

static EncryptTable* get_MEDIA_hashtable(uint8_t* rawheaders[],
					 uint8_t headerlens[],
					 uint8_t headercount,
					 EncryptTable* table){
  if(table == NULL) table = createEncryptTable();

  if(table->len == 0){
    table->len = calc_header_maxlen(headerlens, headercount);
    table->buff = malloc(table->len);
  }

  uint8_t enc_byte = calc_hash_byte_MEDIADATA
    (rawheaders, headerlens, headercount);
  memset(table->buff, enc_byte, table->len);

  for(int i=0; i<table->len; i++)
    for(int j=0; j<headercount; j++)
      if(headerlens[j] >= 1)
	table->buff[i] ^= rawheaders[j][(j + i) % headerlens[j]];
  return table;
}

static EncryptTable* get_MODEL_hashtable(uint8_t* rawheaders[],
					 uint8_t headerlens[],
					 uint8_t headercount,
					 EncryptTable* table){
  if(table == NULL) table = createEncryptTable();

  if(table->len == 0){
    table->len = calc_header_maxlen(headerlens, headercount);
    table->buff = malloc(table->len);
  }

  uint8_t enc_byte = calc_hash_byte_MODEL
    (rawheaders, headerlens, headercount);
  memset(table->buff, enc_byte, table->len);

  for(int i=0; i<table->len; i++)
    for(int j=0; j<headercount; j++)
      if(headerlens[j] >= 1)
	table->buff[i] ^= rawheaders[j][i % headerlens[j]];
  return table;
}


static uint8_t decodeByte(EncryptTable* table, uint8_t inbyte){
  uint8_t res = inbyte ^ table->last_crypt_byte ^
      table->buff[table->index % table->len];
  table->index += 1;
  table->last_crypt_byte = inbyte;
  return res;
}

static uint32_t readintcrypt(EncryptTable* table, uint8_t a,
			     uint8_t b, uint8_t c, uint8_t d){
  a = decodeByte(table, a);
  b = decodeByte(table, b);
  c = decodeByte(table, c);
  d = decodeByte(table, d);
  return le32toh(d<<24 | c << 16 | b << 8 | a);
}

static char* read_str_crypt(EncryptTable* table, uint8_t* ptr,
			    uint32_t cnt){
  char* outbuff = malloc(cnt+1);
  memcpy(outbuff, ptr, cnt);
  for(int i = 0; i < cnt; i++)
    outbuff[i] = decodeByte(table, outbuff[i]);
  outbuff[cnt] = 0;
  return outbuff;
}

static void wtloadUUID(uuid_t u, uint8_t* inbuff){
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

ExtraStringLL* ExtraStringLL_create(EncryptTable* table, uint8_t* ptr){
  ExtraStringLL* url = malloc(sizeof(ExtraStringLL));

  url->type = decodeByte(table, *ptr++);
  url->len = readintcrypt(table, *ptr, *(ptr+1),
			  *(ptr+2), *(ptr+3));
  ptr += 4;
  url->always300_0 = readintcrypt(table, *ptr, *(ptr+1),
				  *(ptr+2), *(ptr+3));
  ptr += 4;
  url->always300_1 = readintcrypt(table, *ptr, *(ptr+1),
				  *(ptr+2), *(ptr+3));
  ptr += 4;
  if(url->len == 0 && url->type == 0){
    free(url);
    return NULL;
  }
  url->buff = read_str_crypt(table, ptr, url->len);
  ptr += url->len;

  url->next = NULL;

  return url;
}

void ExtraStringLL_free(ExtraStringLL* this){
  if(this->len && this->buff){free(this->buff); this->buff=0;}
  if(this->next){ExtraStringLL_free(this->next);this->next=0;}
  free(this);
}

static void wt_cab_extract(WLD3* wt){
  uint8_t* inbuff = wt->payload_data;
  uint32_t inbuff_len = wt->payload_len;
  const char *mem_cab_in, *mem_cab_out;
  struct mscab_decompressor *cabd;
  struct mscabd_cabinet *cab;
  struct mscabd_file *file;
  int err;

  mem_cab_in = create_filename_from_memory(inbuff, inbuff_len);
  if (!mem_cab_in) exit(1);

  MSPACK_SYS_SELFTEST(err);
  if (err) exit(1);

  if (cabd = mspack_create_cab_decompressor(&multi_system)) {
    if (cab = cabd->open(cabd, mem_cab_in)) {
      int filecount = 0;
      file = cab->files;
      while(file != NULL){
	filecount += 1;
	file = file->next;
      }
      if(filecount > 1){
	printf("More than one file in cab. Aborting extract.\n");
	cabd->close(cabd, cab);
      }else{
	file = cab->files;
	wt->payload_len = file->length;
	wt->payload_data = malloc(wt->payload_len);
	wt->cabcompression = true;
	//printf("Filename: %s\n", file->filename);

	mem_cab_out = create_filename_from_memory
	  (wt->payload_data, wt->payload_len);
	if (!mem_cab_out) exit(1);

	if (cabd->extract(cabd, file, mem_cab_out)) {
	  printf("Failed to write out to mem buff");
	  exit(1);
	}
	free_filename(mem_cab_out);
	free(inbuff);
	cabd->close(cabd, cab);
      }
    } else {
      fprintf(stderr, "can't open cabinet (%d)\n",
	      cabd->last_error(cabd));
    }
    mspack_destroy_cab_decompressor(cabd);
  } else {
    fprintf(stderr, "can't make decompressor\n");
  }

  free_filename(mem_cab_in);
}

WLD3* wld3_extract(uint8_t* fbuff, size_t fsize){
  //Reader *f = readerCreate(fbuff, fsize);
  uint8_t *ptr = fbuff;
  uint8_t headerlens[9];
  uint8_t* rawheaders[9];
  struct tm tm;
  WLD3* wt;
  EncryptTable* table;

  wt = malloc(sizeof(WLD3));
  memset(wt, 0, sizeof(WLD3));

  table = createEncryptTable();

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
  //printf("%s\n", wt->copyright);

  //CreatedDate
  wt->createddate = (time_t)le32toh(*((uint32_t*)rawheaders[1]));
  //printf("CREATED %u\n", (unsigned int)wt->createddate);

  //StartValieDate
  wt->startvaliedate = (time_t)le32toh(*((uint32_t*)rawheaders[2]));
  //printf("VALIDD  %u\n", (unsigned int)wt->startvaliedate);

  //ExpireDate
  wt->expiredate = (time_t)le32toh(*((uint32_t*)rawheaders[3]));
  //printf("Expire  %u\n", (unsigned int)wt->expiredate);

  //WTVerUUID
  //char uuid_str[37];
  wtloadUUID(wt->wtversionUUID, rawheaders[4]);
  //uuid_unparse(wt->wtversionUUID, uuid_str);
  //printf("UUID: %s\n", uuid_str);

  //ResourceUUID
  wtloadUUID(wt->resourceUUID, rawheaders[5]);
  //uuid_unparse(wt->resourceUUID, uuid_str);
  //printf("UUID: %s\n", uuid_str);

  //LicenseType
  memcpy(wt->licensetype, rawheaders[6], 4);
  //printf("LicenseType: %s\n", wt->licensetype);

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
  //printf("EncodeVersion: %u\n", wt->encodeversion);

  //ExtraURLs
  if(wt->encodeversion >= 300){
    get_MEDIA_hashtable(rawheaders, headerlens, headercount, table);
    ExtraStringLL** tail = &wt->urls;
    while(1){
      ExtraStringLL* url = ExtraStringLL_create(table, ptr);
      if(url == NULL){
	ptr += 13;
	//ExtraStringLL_free(url);
	break;
      }

      ptr += 13+url->len;
      *tail = url;
      tail = &url->next;
    }
  }

  //EncodeType
  int typeindex = -1;
  enum resource_class encodetype;
  size_t outext_len = strlen(wt->outext);
  for(int i = 0; i < sizeof(file_type_info)/sizeof(FileInfo); i++){
    if(memcmp(file_type_info[i].headerval, wt->outext, outext_len) == 0){
      outext_len = strlen(file_type_info[i].outext);
      memcpy(wt->outext, file_type_info[i].outext, outext_len);
      encodetype = file_type_info[i].rc;
      typeindex = i;
      break;
    }
  }
  if(typeindex == -1){
    printf("No known way to extract type '%s'", wt->outext);
    goto FAIL;
  }

  //EncodeTableCalculation
  if(encodetype == model){
    get_MODEL_hashtable(rawheaders, headerlens, headercount, table);
  }else if(encodetype == media){
    get_MEDIA_hashtable(rawheaders, headerlens, headercount, table);
  }else if(encodetype == data){
    get_DATA_hashtable(rawheaders, headerlens, headercount, table);
  }else{
    printf("Error: Unknown resource class selected.");
    goto FAIL;
  }

  wt->payload_len = fsize-(int)(ptr-fbuff);
  wt->payload_data = malloc(wt->payload_len);
  for(int i = 0; i < wt->payload_len; i++)
    wt->payload_data[i] = decodeByte(table, *ptr++);

  wt_cab_extract(wt);


 CLEANUP:
  for(int i = 0; i<headercount; i++)
    if(rawheaders[i]){free(rawheaders[i]);rawheaders[i]=0;}
  EncryptTable_free(table);
  return wt;

 FAIL:
  wld3_free(wt);
  goto CLEANUP;
}

void wlkd_print(WLD3* wt){
  char uuid_str[37];
  struct tm* timeinfo;

  printf("Copyright:     %s\n", wt->copyright);

  timeinfo = localtime(&wt->createddate);
  printf("CREATED:       %s", asctime(timeinfo));
  if(wt->startvaliedate == 0)
    printf("VALIDD:        NONE\n");
  else{
    timeinfo = localtime(&wt->startvaliedate);
    printf("VALIDD:        %s", asctime(timeinfo));
  }
  timeinfo = localtime(&wt->expiredate);
  printf("EXPIRED:       %s", asctime(timeinfo));

  uuid_unparse(wt->wtversionUUID, uuid_str);
  printf("UUID:          %s\n", uuid_str);
  uuid_unparse(wt->resourceUUID, uuid_str);
  printf("UUID:          %s\n", uuid_str);
  printf("LicenseType:   %s\n", wt->licensetype);
  printf("EncodeVersion: %u\n", wt->encodeversion);
  printf("OutExt:        %s\n", wt->outext);
  printf("CabCompressed: %s\n", wt->cabcompression? "true":"false");
  printf("PayloadLen:    %zu\n", wt->payload_len);

  if(wt->urls){
    printf("URLS:\n");
    ExtraStringLL* url = wt->urls;
    while(url){
      printf("  Type: 0x%02x; Val: \"%s\"; (%d, %d)\n", url->type,
	     url->buff, url->always300_0, url->always300_1);
      url = url->next;
    }
  }
}

void wld3_free(WLD3* wt){
  if(wt){
    if(wt->comment){free(wt->comment); wt->comment=0;}
    if(wt->payload_data){free(wt->payload_data);wt->payload_data=0;}
    if(wt->copyright){free(wt->copyright); wt->copyright=0;}
    if(wt->urls){ExtraStringLL_free(wt->urls); wt->urls=0;}
    free(wt); wt = NULL;
  }
}
