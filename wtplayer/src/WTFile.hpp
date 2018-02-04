#pragma once

#include "basetypes.hpp"

#include "WTObject.hpp"

class WT;
typedef struct WLD3 WLD3;

class WTFile : public WTObject {

public:
  WTFile(WT* wt,
         const char* File_Name,
         int WTCache_Type,
         int endian);

  virtual ~WTFile();

  int getObjectType(){
    APILOG;
    return this->WTObject::getObjectType() |
      WTFILE;
  }

  VARIANT readAll();

  unsigned char readByte();

  int readInt();

  float readFloat();

  short readShort();

  double readDouble();

  const char* readLine();

  //[id(0x00002b00), hidden]
  void close();

  //[id(0x00002b01), hidden]
  void seek(int Pos);

  //[id(0x00002b02), hidden]
  int move(int by);

  bool eof();

  //[id(0x00002b04), hidden]
  int length();

  int status();

  int getEndian(){
    APILOG;
    return this->endian;
  }

  int setEndian(int endian);

  const char* readString(int length = -1);

private:
  WLD3* wld3;
  int cacheType;
  int endian;
  size_t wtbuff_offset = 0;
};
