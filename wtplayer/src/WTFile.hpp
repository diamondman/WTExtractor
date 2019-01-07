#pragma once

#include <string>

#include "basetypes.hpp"

#include "WTObject.hpp"

class WT;
typedef struct DataAccessor DataAccessor;
typedef struct WLD3 WLD3;

#define WTFILE_STATUS_OK         (  0)
#define WTFILE_STATUS_NOSUCHFILE ( -6)
#define WTFILE_STATUS_EOF        ( -9)
#define WTFILE_STATUS_FORBIDDEN  (-10)
#define WTFILE_STATUS_NOTOPENED  (-11)

#define WTBYTECONVENTION_BIG    2
#define WTBYTECONVENTION_HOST   0
#define WTBYTECONVENTION_LITTLE 1

class WTFile : public WTObject {

public:
  WTFile(WT* wt,
         const char* File_Name,
         int WTCache_Type,
         int endian=WTBYTECONVENTION_BIG);

  virtual ~WTFile();

  int getObjectType(){
    APILOG;
    return this->WTObject::getObjectType() |
      WTFILE;
  }

  bool readAll(signed char ** arrReadAllOut, int * lReadAllOut);
  //VARIANT readAll();

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
  std::string full_fname;
};
