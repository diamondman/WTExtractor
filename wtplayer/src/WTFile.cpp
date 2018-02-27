#include <string>
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

  std::string full_fname = std::string(this->wt->getFilesPath()) + "/" + File_Name;
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

VARIANT WTFile::readAll(){
  APILOG;
  throw std::runtime_error("unimplemented");
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

const char* WTFile::readLine(){
  APILOG;
  std::string res = "";
  unsigned char c;
  while(!this->eof()) {
    c = this->readByte();
    if (c == '\r') continue;
    res += c;
    if (c == '\n') break;
  }
  //std::cout << "LINE: '''" << res << "'''" << std::endl;
  return res.c_str();
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
const char* WTFile::readString(int length){
  APILOG;
  length = (length > -1) ? length : this->length() - wtbuff_offset;
  std::string res = "";
  while (!this->eof() && length--)
    res += this->readByte();
  //std::cout << "LINE: '''" << res << "'''" << std::endl;
  return res.c_str();
}
