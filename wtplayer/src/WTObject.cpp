#include "basetypes.hpp"
#include "WTObject.hpp"
#include <iostream>

int WTObject::getObjectType(){
  APILOG;
  return 14;
}

//[id(0x000003ea), hidden]
WTObject* WTObject::duplicate(){
  APILOG;
  return 0;
}

WT* WTObject::getCreator(){
  APILOG;
  return 0;
}

WTObject* WTObject::getOwner(){
  APILOG;
  return 0;
}

char* WTObject::getName(){
  APILOG;
  std::cout << "Hello from cout in native." << std::endl;
  return (char*)"TEST";
}

void WTObject::setName(char* Name_Of_Object){
  APILOG;
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
  this->userdata = User_Data;
}

void WTObject::setOnLoad(WTOnLoadEvent* callback){
  APILOG;
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
}

void WTObject::setOnLoadedWithChildren(WTOnLoadEvent* callback){
  APILOG;
}
