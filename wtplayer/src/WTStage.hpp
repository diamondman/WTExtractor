#pragma once

#include "WTObject.hpp"

#include <vector>

class WTCamera;
class WTContainer;

class WTStage : public WTObject {

public:
  WTStage(WT* wt_);

  ~WTStage();

  int getObjectType(){
    APILOG;
    return this->WTObject::getObjectType() |
      WTSTAGE;
  }

  void addObject(WTContainer* Object_To_Add);

  void removeObject(WTContainer* Object_To_Remove);

  WTObject* getObjectByName(char* Name_Of_Object,
                            int Nth = 1);

  int getChildCount();

  WTObject* getChildByIndex(int Child_Number);

  WTCamera* createCamera();

  WTCamera* createBitmapCamera(int iWidth,
                               int iHeight);

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

private:
  std::vector<WTCamera*> cameras;
  std::vector<WTCamera*> bitmapCameras;

  std::vector<WTObject*> objects;

  bool fog_enabled = false;
  float fog_start_distance = 0;
  float fog_end_distance = 0;
  float fog_density = 0;
  uint32_t fog_color = 0;

  uint32_t bg_color = 0;
};
