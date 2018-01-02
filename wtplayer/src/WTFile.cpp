#include "basetypes.hpp"
#include "WTFile.hpp"

VARIANT WTFile::readAll(){
  APILOG;
  return 0;
}

unsigned char WTFile::readByte(){
  APILOG;
  return 0;
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
  APILOG;
  return false;
}

//[id(0x00002b04), hidden]
int WTFile::length(){
  APILOG;
  return 0;
}

int WTFile::status(){
  APILOG;
  return 0;
}

int WTFile::getEndian(){
  APILOG;
  return 0;
}

int WTFile::setEndian(int endian){
  APILOG;
  return 0;
}

char* WTFile::readString(int length){
  APILOG;
  return (char*)"";
}
