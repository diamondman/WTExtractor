#pragma once

#include "WTGroup.hpp"

class WTShadow : public WTGroup {

public:
  WTShadow(int Type,
           int Width,
           int Height);

  int getObjectType(){
    APILOG;
    return this->WTGroup::getObjectType() |
      WTSHADOW;
  }

  int getType();

  void setEnable(bool enabled);

  bool getEnable();

  void setFieldOfView(float Fov);

  float getFieldOfView();

  void setResolution(int Width,
                     int Height);

  int getWidth();

  int getHeight();

  void addCaster(WTGroup* Group_To_Add,
                 int Red = 100,
                 int Green = 100,
                 int Blue = 100);

  void removeCaster(WTGroup* Group_To_Remove);

  void addReceiver(WTGroup* Group_To_Add);

  void removeReceiver(WTGroup* Group_To_Remove);

  void setCasterColor(WTGroup* Group,
                      int Red,
                      int Green,
                      int Blue);

  int getCasterColorRed(WTGroup* Group);

  int getCasterColorGreen(WTGroup* Group);

  int getCasterColorBlue(WTGroup* Group);

  void setFiltering(int FilteringMethod);

  int getFiltering();

  void setRange(bool RelativeToCaster,
                float Near = 0,
                float Far = 5000);

  void enableCulling(bool Enable,
                     bool EnableExtraCullPlanes);
};
