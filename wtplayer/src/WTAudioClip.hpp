#pragma once

#include "WTObject.hpp"

class WTAudioClip : public WTObject {

public:
  WTAudioClip(WT* wt_,
              char* File_Name,
              int WTCache_Type);

  int getObjectType(){
    APILOG;
    return this->WTObject::getObjectType() |
      WTAUDIOCLIP;
  }

  void start(int Play_Sound_Forever = 0,
             int Wait_Until_Loaded = 0);

  void start(bool Play_Sound_Forever,
             bool Wait_Until_Loaded = false){
    this->start((int)Play_Sound_Forever, (int)Wait_Until_Loaded);
  }

  void stop();

  int getVolume();

  void setVolume(int Volume);

  int getPan();

  void setPan(int Pan);

  long getFrequency();

  void setFrequency(int Frequency);

  //[id(0x00002719), hidden]
  bool getIsPlaying();

  bool isPlaying();

  float getPlaybackRate();

  void setPlaybackRate(float lRate);

  int getPlaybackLength();

  int getPlaybackPosition();
};
