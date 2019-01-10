//#include <iostream>
//#include <iomanip>
#include <stdio.h>

#include <string>
#include <cstring>
#include <dataaccessors.h>
#include <wld3_extract.h>

#include "WTFile.hpp"
#include "WT.hpp"

WTFile::WTFile(WT* wt_,
               const char* File_Name,
               int WTCache_Type,
               int endian) :
  WTObject(wt_), acc(0), _wld3(0), cacheType(WTCache_Type), endian(endian) {
  APILOG;

  full_fname = std::string(this->wt->getFilesPath()) + "/" + File_Name;
  std::cout << "opening file: \"" << full_fname << "\"" << std::endl;

  this->acc = openFileAccessor(full_fname.c_str());
  if(this->acc == 0){
    printf("Failed to create accessor for WTFile!\n\n");
    this->status_ = WTFILE_STATUS_NOSUCHFILE;
    return;
  }
  int curr_offset = acc->tell(acc);
  bool is_wld3_compressed = wld3_check_magic(acc);
  acc->seek(acc, curr_offset, SEEK_SET); // Rewind the file
  if(is_wld3_compressed) {
    printf("  File is WT compressed, decompressing.\n");
    this->_wld3 = wld3_extract(this->acc);
    if(this->_wld3 > 0) {
      wld3_print(this->_wld3);
      this->acc->free(this->acc);
      this->acc = 0;
      this->acc = openBufferAccessor(this->_wld3->payload_data,
                                     this->_wld3->payload_len);
      if(!this->acc){
        printf("Failed to create accessor for decoded WTFile!\n\n");
        this->status_ = WTFILE_STATUS_NOTOPENED;
        return;
      }
    } else {
      printf("WTFile::WTFile NOT VALID! NOT HANDLED!\n");
      this->status_ = WTFILE_STATUS_NOTOPENED;
      return;
    }
  } else {
    printf("  File is not compressed in WT format. Rewound to %d\n", acc->tell(acc));
  }

  this->status_ = WTFILE_STATUS_OK;
}

WTFile::~WTFile(){
  APILOG;
  if(this->acc)
    this->acc->free(this->acc);
  if(this->_wld3)
    wld3_free(this->_wld3);
}

size_t WTFile::remaining() {
  if(!this->acc) throw std::runtime_error("acc is null!");
  return this->acc->remaining(this->acc);
}

size_t WTFile::__read(void *buffer, size_t bytes) {
  if(!this->acc) throw std::runtime_error("acc is null!");
  return this->acc->read(this->acc, buffer, bytes);
}

int WTFile::length(){
  //APILOG;
  if(!this->acc) throw std::runtime_error("acc is null!");
  return this->acc->length(this->acc);
}

bool WTFile::readAll(signed char** result, int* len) {
  APILOG;
  std::cout << "    file: " << full_fname << std::endl;
  if(result == NULL || len == NULL) return 0;
  *len = this->remaining();
  std::cout << "  Reading from: " << this->acc->tell(this->acc) << "; len: "
            << *len << std::endl;

  if(*len < 0) return false;

  *result = new signed char[*len];
  this->__read(*result, *len);
  return true;
}

unsigned char WTFile::readByte(){
  //APILOG;
  unsigned char res;
  this->__read(&res, 1);
  //std::cout << "  BYTE: " << res << std::endl;
  return res;
}

int WTFile::readInt(){
  APILOG;
  int res;
  this->__read(&res, sizeof(int));

  switch(this->endian) {
  case WTBYTECONVENTION_BIG:
    return be32toh(res);
  case WTBYTECONVENTION_LITTLE:
    return le32toh(res);
  default: //WTBYTECONVENTION_HOST:
    return res;
  }
}

float WTFile::readFloat(){
  APILOG;
  float res;
  this->__read(&res, sizeof(float));

  switch(this->endian) {
  case WTBYTECONVENTION_BIG:
    return be32toh(res);
  case WTBYTECONVENTION_LITTLE:
    return le32toh(res);
  default: //WTBYTECONVENTION_HOST:
    return res;
  }
}

short WTFile::readShort(){
  APILOG;
  short res;
  this->__read(&res, sizeof(short));

  switch(this->endian) {
  case WTBYTECONVENTION_BIG:
    return be32toh(res);
  case WTBYTECONVENTION_LITTLE:
    return le32toh(res);
  default: //WTBYTECONVENTION_HOST:
    return res;
  }
}

double WTFile::readDouble(){
  APILOG;
  double res;
  this->__read(&res, sizeof(double));

  switch(this->endian) {
  case WTBYTECONVENTION_BIG:
    return be32toh(res);
  case WTBYTECONVENTION_LITTLE:
    return le32toh(res);
  default: //WTBYTECONVENTION_HOST:
    return res;
  }
}

std::string readLine_strres;
const char* WTFile::readLine(){
  //APILOG;
  readLine_strres = "";
  unsigned char c;
  while(!this->eof()) {
    c = this->readByte();
    if (c == '\r') continue;
    readLine_strres += c;
    if (c == '\n') break;
  }
  //std::cout << "LINE: '''" << readLine_strres << "'''" << std::endl;
  return readLine_strres.c_str();
}

//[id(0x00002b00), hidden]
void WTFile::close(){
  APILOG;
}

//[id(0x00002b01), hidden]
void WTFile::seek(int Pos){
  APILOG;
  throw std::runtime_error("unimplemented");
}

//[id(0x00002b02), hidden]
int WTFile::move(int by){
  APILOG;
  throw std::runtime_error("unimplemented");
}

bool WTFile::eof(){
  //APILOG;
  return this->remaining() <= 0;
}

int WTFile::status(){
  APILOG;
  if(this->status_ != WTFILE_STATUS_OK) {
    std::cout << "  STATUS = " << this->status_ << std::endl;
    return this->status_;
  }
  if(this->eof()){
    return WTFILE_STATUS_EOF;
    std::cout << "  STATUS = EOF" << std::endl;
  }
  std::cout << "  STATUS = ALL OK!" << std::endl;
  return 0; //No Errors
}

int WTFile::setEndian(int endian){
  APILOG;
  int prev = this->endian;
  this->endian = endian;
  return prev;
}

//TODO make this more efficient, also check the results.
std::string readString_strres;
const char* WTFile::readString(int length){
  APILOG;
  length = (length > -1) ? length : this->remaining();
  readString_strres = "";
  while (!this->eof() && length--)
    readString_strres += this->readByte();
  //std::cout << "LINE: '''" << readString_strres << "'''" << std::endl;
  return readString_strres.c_str();
}
