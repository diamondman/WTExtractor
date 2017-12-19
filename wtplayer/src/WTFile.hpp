#pragma once

#include "WTObject.hpp"
#include "basetypes.hpp"

class WTFile : public WTObject {

public:
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
};
