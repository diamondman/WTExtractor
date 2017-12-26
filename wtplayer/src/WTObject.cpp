#include "WTObject.hpp"
#include <iostream>

int WTObject::getObjectType(){
  return 0;
}

////[id(0x000003ea), hidden]
//WTObject* WTObject::duplicate(){
//  return 0;
//}
//
//WT* WTObject::getCreator(){
//  return 0;
//}
//
//WTObject* WTObject::getOwner(){
//  return 0;
//}
//
//char* WTObject::getName(){
//  std::cout << "Hello from cout in native." << std::endl;
//  return (char*)"TEST";
//}
//
//void WTObject::setName(char* Name_Of_Object){}
//
//bool WTObject::getIsValid(){
//  return true;
//}
//
//bool WTObject::getIsLoaded(){
//  return true;
//}
//
//int WTObject::getErrorNumber(){
//  return -1;
//}
//
//void WTObject::setErrorNumber(int Error_Number){}
//
//VARIANT WTObject::getUserData(){
//  return this->userdata;
//}
//
//void WTObject::setUserData(VARIANT User_Data){
//  this->userdata = User_Data;
//}
//
//void WTObject::setOnLoad(WTOnLoadEvent* callback){}
//
//bool WTObject::isValid(){
//  return true;
//}
//
//bool WTObject::isLoaded(){
//  return true;
//}
//
//bool WTObject::isLoadedWithChildren(){
//  return true;
//}
//
//void WTObject::setOption(int Option_Number,
//                         VARIANT New_Value){}
//
//VARIANT WTObject::getOption(int Option_Number){}
//
//void WTObject::setOnLoadedWithChildren(WTOnLoadEvent* callback){}
