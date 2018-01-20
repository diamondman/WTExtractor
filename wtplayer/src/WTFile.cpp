#include "basetypes.hpp"
#include "WTFile.hpp"
#include "WT.hpp"

#include "dataaccessors.h"
#include <string>

WTFile::WTFile(WT* wt,
               char* File_Name,
               int WTCache_Type,
               int endian) :
  cacheType(WTCache_Type), endian(endian), wld3(0), _wt(wt) {
  APILOG;

  std::string full_fname = std::string(this->_wt->getFilesPath()) + "/" + File_Name;
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
  return 0;
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
  return 0;
}

float WTFile::readFloat(){
  APILOG;
  return 0;
}

short WTFile::readShort(){
  APILOG;
  return 0;
}

double WTFile::readDouble(){
  APILOG;
  return 0;
}

char* WTFile::readLine(){
  APILOG;
  return 0;
}

//[id(0x00002b00), hidden]
void WTFile::close(){
  APILOG;
}

//[id(0x00002b01), hidden]
void WTFile::seek(int Pos){
  APILOG;
}

//[id(0x00002b02), hidden]
int WTFile::move(int by){
  APILOG;
  return 0;
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

int WTFile::getEndian(){
  APILOG;
  return this->endian;
}

int WTFile::setEndian(int endian){
  APILOG;
  int prev = this->endian;
  this->endian = endian;
  return prev;
}

char* WTFile::readString(int length){
  APILOG;
  return (char*)"";
}
