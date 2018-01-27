#include "basetypes.hpp"
#include "WTGroup.hpp"

WTGroup::WTGroup() :
  WTContainer() {
}

WTGroup::WTGroup(char* File_Name,
                 int WTCache_Type,
                 int Load_Order_Offset) :
  WTContainer() {
}

int WTGroup::addObject(WTContainer* Object_To_Add){
  APILOG;
  return 0;
}

void WTGroup::removeObject(WTContainer* Object_To_Remove){
  APILOG;
}

WTObject* WTGroup::getObjectByName(char* Name_Of_Object,
                                   int Nth){
  APILOG;
  return 0;
}

int WTGroup::getChildCount() {
  APILOG;
  return 0;
}

WTObject* WTGroup::getChildByIndex(int Child_Number) {
  APILOG;
  return 0;
}

bool WTGroup::getLightingStatus() {
  APILOG;
  return true;
}
