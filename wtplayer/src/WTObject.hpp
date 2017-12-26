#pragma once

#include "basetypes.hpp"

class WTOnLoadEvent;
class WT;

class WTObject {

public:
  virtual int getObjectType();

  //[id(0x000003ea), hidden]
  WTObject* duplicate();

  WT* getCreator();

  WTObject* getOwner();

  char* getName();

  void setName(char* Name_Of_Object);

  bool getIsValid();

  bool getIsLoaded();

  int getErrorNumber();

  void setErrorNumber(int Error_Number);

  VARIANT getUserData();

  void setUserData(VARIANT User_Data);

  void setOnLoad(WTOnLoadEvent* callback);

  bool isValid();

  bool isLoaded();

  bool isLoadedWithChildren();

  void setOption(int Option_Number,
                 VARIANT New_Value);

  VARIANT getOption(int Option_Number);

  void setOnLoadedWithChildren(WTOnLoadEvent* callback);

private:
  VARIANT userdata;
};
