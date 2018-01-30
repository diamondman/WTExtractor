#pragma once

#include "basetypes.hpp"
#include "IUnknown.hpp"

#include "constants.hpp"

#include <string>

class InternalOnLoadCallbackWrapper;

class WT;

class WTObject : public IUnknown {

public:
  WTObject(WT* wt_);

  virtual int getObjectType(){
    APILOG;
    return WTOBJECT;
  }

  WT* getCreator(){
    APILOG;
    return this->wt;
  }

  virtual WTObject* getOwner();

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

protected:
  WT *wt;
  std::string name = "";

private:
  VARIANT userdata;
  InternalOnLoadCallbackWrapper *OnLoadCallback = 0;
};
