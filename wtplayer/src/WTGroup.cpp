#include "basetypes.hpp"
#include "WTGroup.hpp"

#include <string.h>

WTGroup::WTGroup(WT* wt_) :
  WTContainer(wt_) {
}

WTGroup::WTGroup(WT* wt_,
                 const char* File_Name,
                 int WTCache_Type,
                 int Load_Order_Offset) :
  WTContainer(wt_) {
}

WTGroup::~WTGroup() {
  for(auto o : this->objects)
    o->Release();
}

int WTGroup::addObject(WTContainer* o){
  APILOG;
  o->AddRef();
  this->objects.push_back(o);
  return 0;
}

void WTGroup::removeObject(WTContainer* o){
  APILOG;
  for(int i = 0; i < this->objects.size(); i++) {
    if(this->objects[i] == o){
      o->Release();
      this->objects.erase(this->objects.begin() + i);
      return;
    }
  }
  std::cout << "ERROR! Tried to remove an object that was not here! Prob our fault!\n";
}

WTObject* WTGroup::getObjectByName(char* Name_Of_Object,
                                   int Nth){
  APILOG;
  if(Nth > 0)
    Nth--; //1 indexed, turning to 0 index. Ignoring issues of passing 0 for now. TODO?

  for(int i = 0; i < this->objects.size(); i++) {
    if(strcmp(this->objects[i]->getName(), Name_Of_Object) == 0){
      if(Nth == 0)
        return this->objects[i];
      Nth--;
    }
  }

  std::cout << "Error? getObjectByName returning null" << std::endl;
  return NULL;
}

WTObject* WTGroup::getChildByIndex(int Child_Number) {
  APILOG;
  if(Child_Number >= this->objects.size())
    return NULL;
  return this->objects[Child_Number];
}

bool WTGroup::getLightingStatus() {
  APILOG;
  return true;
}
