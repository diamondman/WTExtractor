#pragma once

#include <vector>

#include "WTContainer.hpp"

class WTObject;

class WTGroup : public WTContainer {

public:
  WTGroup(WT* wt_);

  WTGroup(WT* wt_,
          const char* File_Name,
          int WTCache_Type,
          int Load_Order_Offset);

  virtual ~WTGroup();

  virtual int getObjectType(){
    APILOG;
    return this->WTContainer::getObjectType() |
      WT_3D |
      WTGROUP;
  }

  int addObject(WTContainer* Object_To_Add);

  void removeObject(WTContainer* Object_To_Remove);

  WTObject* getObjectByName(char* Name_Of_Object,
                            int Nth = 1);

  int getChildCount() {
    APILOG;
    return this->objects.size();
  }

  WTObject* getChildByIndex(int Child_Number);

  bool getLightingStatus();

private:
  std::vector<WTObject*> objects;
};
