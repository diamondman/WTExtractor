#pragma once

#include "basetypes.hpp"
#include "IUnknown.hpp"

#include "constants.hpp"

#include <string>

class InternalOnLoadCallbackWrapper;

class WT;

class WTObject : public IUnknown {

public:
  WTObject();

  virtual int getObjectType(){
    APILOG;
    return WTOBJECT;
  }

  //[id(0x000003ea), hidden]
  WTObject* duplicate();

  WT* getCreator();

  WTObject* getOwner();

  const char* getName(){
    APILOG;
    return this->name.c_str();
  }

  void setName(const char* Name_Of_Object){
    APILOG;
    std::cout << "  (Name_Of_Object = \"" << Name_Of_Object << "\")" << std::endl;
    this->name = std::string(Name_Of_Object);
  }

  bool getIsValid();

  bool getIsLoaded();

  int getErrorNumber();

  void setErrorNumber(int Error_Number);

  VARIANT getUserData();

  void setUserData(VARIANT User_Data);

  void setOnLoad(InternalOnLoadCallbackWrapper* callback){
    APILOG;
    this->OnLoadCallback = callback;
  };

  void setOnLoadedWithChildren(InternalOnLoadCallbackWrapper* callback){
    APILOG;
    this->OnLoadCallback = callback;
  };

  bool isValid();

  bool isLoaded();

  bool isLoadedWithChildren();

  void setOption(int Option_Number,
                 VARIANT New_Value);

  VARIANT getOption(int Option_Number);

private:
  VARIANT userdata;
  InternalOnLoadCallbackWrapper *OnLoadCallback = 0;
  std::string name = "";
};
