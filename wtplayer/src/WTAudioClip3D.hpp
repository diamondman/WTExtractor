#pragma once

#include "WTGroup.hpp"

class WTCamera;

class WTAudioClip3D : public WTGroup {

public:
  WTAudioClip3D(WT* wt_,
                char* File_Name,
                int WTCache_Type);

  int getObjectType(){
    APILOG;
    return this->WTGroup::getObjectType() |
      WTAUDIOCLIP3D;
  }

  void start(int loop = 0,
             int wait = 0);

  void stop();

  bool isPlaying();

  float getDoppler();

  void setDoppler(float Rate);

  int getVolumeScale();

  void setVolumeScale(int vol);

  float getPlaybackRateScale();

  void setPlaybackRateScale(float Rate);

  float getMinDistance();

  void setMinDistance(float min);

  float getMaxDistance();

  void setMaxDistance(float max);

  int getPlaybackLength();

  int getPlaybackPosition();

  WTCamera* getCamera();

  void setCamera(WTCamera* camera = 0);

  void removeCamera();
};
