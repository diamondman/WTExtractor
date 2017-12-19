#include "WTFile.hpp"

VARIANT WTFile::readAll(){
  return 0;
}

unsigned char WTFile::readByte(){
  return 0;
}

int WTFile::readInt(){
  return 0;
}

float WTFile::readFloat(){
  return 0;
}

short WTFile::readShort(){
  return 0;
}

double WTFile::readDouble(){
  return 0;
}

char* WTFile::readLine(){
  return 0;
}

//[id(0x00002b00), hidden]
void WTFile::close(){}

//[id(0x00002b01), hidden]
void WTFile::seek(int Pos){}

//[id(0x00002b02), hidden]
int WTFile::move(int by){
  return 0;
}

bool WTFile::eof(){
  return false;
}

//[id(0x00002b04), hidden]
int WTFile::length(){
  return 0;
}

int WTFile::status(){
  return 0;
}

int WTFile::getEndian(){
  return 0;
}

int WTFile::setEndian(int endian){
  return 0;
}

char* WTFile::readString(int length){
  return (char*)"";
}
