#pragma once

#include "WTObject.hpp"

class WTAudioClip : public WTObject {

public:
  void start(int Play_Sound_Forever = 0,
             int Wait_Until_Loaded = 0);

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
