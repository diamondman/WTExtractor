#pragma once

#include "WTObject.hpp"
#include "basetypes.hpp"
#include "wld3_extract.h"

class WT;

class WTFile : public WTObject {

public:
  WTFile(WT* wt,
         char* File_Name,
         int WTCache_Type,
         int endian);

  ~WTFile();

  VARIANT readAll();

  unsigned char readByte();

  int readInt();

  float readFloat();

  short readShort();

  double readDouble();

  char* readLine();

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

  int getEndian();

  int setEndian(int endian);

  char* readString(int length = -1);

private:
  WT* _wt;
  WLD3* wld3;
  int cacheType;
  int endian;
  size_t wtbuff_offset = 0;
};
