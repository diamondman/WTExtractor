#pragma once

#include "WTObject.hpp"

class WTCamera;
class WTContainer;

class WTStage : public WTObject {

public:
  void addObject(WTContainer* Object_To_Add);

  void removeObject(WTContainer* Object_To_Remove);

  WTCamera* createCamera();

  bool getFogEnabled();

  void setFogEnabled(bool Turn_On_Fog);

  float getFogStartDistance();

  void setFogStartDistance(float Distance);

  float getFogEndDistance();

  void setFogEndDistance(float Distance);

  float getFogDensity();

  void setFogDensity(float Density);

  void setFogColor(unsigned char Red,
                   unsigned char Green,
                   unsigned char Blue);

  void setBGColor(unsigned char Red,
                  unsigned char Green,
                  unsigned char Blue);

  WTObject* getObjectByName(char* Name_Of_Object,
                            int Nth = 1);

  int getChildCount();

  WTObject* getChildByIndex(int Child_Number);

  WTCamera* createBitmapCamera(int iWidth,
                               int iHeight);
};
