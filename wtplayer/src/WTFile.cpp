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
  WTObject(wt_), wld3(0), cacheType(WTCache_Type), endian(endian) {
  APILOG;

  full_fname = std::string(this->wt->getFilesPath()) + "/" + File_Name;
  std::cout << "opening file: \"" << full_fname << "\"" << std::endl;

  DataAccessor* acc = openFileAccessor(full_fname.c_str());
  if(!acc){
    printf("Failed to create accessor for WTFile!\n\n");
    return;
  }
  this->wld3 = wld3_extract(acc);

  if(this->wld3)
    wld3_print(this->wld3);
  else
    printf("ERROR! DONE!\n");

  printf("MADE THE ACC %p\n\n", acc);
  freeFileAccessor(acc);
}

WTFile::~WTFile(){
  APILOG;
  if(this->wld3)
    wld3_free(this->wld3);
}

bool WTFile::readAll(signed char** result, int* len) {
  APILOG;
  std::cout << "    file: " << full_fname << std::endl;
  if(!this->wld3 || result == NULL || len == NULL) return 0;
  *len = this->wld3->payload_len - this->wtbuff_offset;
  std::cout << "  Reading from: " << wtbuff_offset << "; len: " << *len << std::endl;

  if(*len < 0) return false;

  *result = new signed char[*len];
  std::memcpy(*result, &this->wld3->payload_data[wtbuff_offset], *len);
  wtbuff_offset += *len;
  return true;
}

unsigned char WTFile::readByte(){
  //APILOG;
  if(!this->wld3)
    return 0;
  if(this->wtbuff_offset >= this->wld3->payload_len) return 0;
  //std::cout << "  DATA = '" << this->wld3->payload_data[wtbuff_offset] << "'; " <<
  //  "OFFSET = " << this->wtbuff_offset << std::endl;
  return this->wld3->payload_data[wtbuff_offset++];
}

int WTFile::readInt(){
  APILOG;
  throw std::runtime_error("unimplemented");
}

float WTFile::readFloat(){
  APILOG;
  throw std::runtime_error("unimplemented");
}

short WTFile::readShort(){
  APILOG;
  throw std::runtime_error("unimplemented");
}

double WTFile::readDouble(){
  APILOG;
  throw std::runtime_error("unimplemented");
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
  std::cout << "LINE: '''" << readLine_strres << "'''" << std::endl;
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
  if(!this->wld3){
    //std::cout << "  EOF = TRUE (no wld3)" << std::endl;
    return true;
  }
  if(this->wtbuff_offset >= this->wld3->payload_len){
    //std::cout << "  EOF = TRUE" << std::endl;
    return true;
  }
  //std::cout << "  EOF = FALSE" << std::endl;
  return false;
     //return this->wtbuff_offset >= this->wld3->payload_len;
}

//[id(0x00002b04), hidden]
int WTFile::length(){
  APILOG;
  if(!this->wld3)
    return 0;
  return this->wld3->payload_len;
}

int WTFile::status(){
  APILOG;
  if(!this->wld3){
    return -6; //No such file.
    std::cout << "  STATUS = NO FILE" << std::endl;
  }
  if(this->eof()){
    return -9; //EOF.
    std::cout << "  STATUS = EOF" << std::endl;
  }
  //return -10; //Forbidden.
  //return -11; //Not Opened. (File is loading or something)
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
  length = (length > -1) ? length : this->length() - wtbuff_offset;
  readString_strres = "";
  while (!this->eof() && length--)
    readString_strres += this->readByte();
  //std::cout << "LINE: '''" << readString_strres << "'''" << std::endl;
  return readString_strres.c_str();
}
