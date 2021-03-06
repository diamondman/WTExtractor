#include "basetypes.hpp"
#include "InternalOnLoadCallbackWrapper.hpp"

#include "WTObject.hpp"

WTObject::WTObject(WT* wt_) :
  IUnknown(),
  wt(wt_){
}

WTObject* WTObject::getOwner(){
  APILOG;
  return 0;
}

bool WTObject::getIsValid(){
  APILOG;
  return true;
}

bool WTObject::getIsLoaded(){
  APILOG;
  return true;
}

int WTObject::getErrorNumber(){
  APILOG;
  return -1;
}

void WTObject::setErrorNumber(int Error_Number){
  APILOG;
}

VARIANT WTObject::getUserData(){
  APILOG;
  return this->userdata;
}

void WTObject::setUserData(VARIANT User_Data){
  APILOG;
  //this->userdata = User_Data;
}

bool WTObject::isValid(){
  APILOG;
  return true;
}

bool WTObject::isLoaded(){
  APILOG;
  return true;
}

bool WTObject::isLoadedWithChildren(){
  APILOG;
  return true;
}

void WTObject::setOption(int Option_Number,
                         VARIANT New_Value){
  APILOG;
}

VARIANT WTObject::getOption(int Option_Number){
  APILOG;
  return 0;
}
