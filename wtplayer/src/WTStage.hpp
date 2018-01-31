#pragma once

#include "WTObject.hpp"

#include <vector>
#include <cairo.h>

class WTCamera;
class WTContainer;

class WTStage : public WTObject {

public:
  WTStage(WT* wt_);

  virtual ~WTStage();

  int getObjectType(){
    APILOG;
    return this->WTObject::getObjectType() |
      WTSTAGE;
  }

  virtual WTObject* getOwner(){
    APILOG;
    return NULL;
  }

  void _render(cairo_t *cr);

  void addObject(WTContainer* Object_To_Add);

  void removeObject(WTContainer* Object_To_Remove);

  WTObject* getObjectByName(char* Name_Of_Object,
                            int Nth = 1);

  int getChildCount(){
    APILOG;
    return this->objects.size();
  }

  WTObject* getChildByIndex(int Child_Number);

  WTCamera* createCamera();

  WTCamera* createBitmapCamera(int iWidth,
                               int iHeight);

  bool getFogEnabled(){
    APILOG;
    return this->fog_enabled;
  }

  void setFogEnabled(bool Turn_On_Fog);

  float getFogStartDistance() {
    APILOG;
    return this->fog_start_distance;
  }

  void setFogStartDistance(float Distance);

  float getFogEndDistance() {
    APILOG;
    return this->fog_end_distance;
  }

  void setFogEndDistance(float Distance);

  float getFogDensity() {
    APILOG;
    return this->fog_density;
  }

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
