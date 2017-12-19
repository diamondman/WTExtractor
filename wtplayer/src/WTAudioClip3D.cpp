#include "WTAudioClip3D.hpp"
#include "WTCamera.hpp"

void WTAudioClip3D::start(int loop,
                          int wait){}

void WTAudioClip3D::stop(){}

bool WTAudioClip3D::isPlaying(){
  return false;
}

float WTAudioClip3D::getDoppler(){
  return 0;
}

void WTAudioClip3D::setDoppler(float Rate){}

int WTAudioClip3D::getVolumeScale(){
  return 0;
}

void WTAudioClip3D::setVolumeScale(int vol){}

float WTAudioClip3D::getPlaybackRateScale(){
  return 0;
}

void WTAudioClip3D::setPlaybackRateScale(float Rate){}

float WTAudioClip3D::getMinDistance(){
  return 0;
}

void WTAudioClip3D::setMinDistance(float min){}

float WTAudioClip3D::getMaxDistance(){
  return 0;
}

void WTAudioClip3D::setMaxDistance(float max){}

int WTAudioClip3D::getPlaybackLength(){
  return 0;
}

int WTAudioClip3D::getPlaybackPosition(){
  return 0;
}

WTCamera* WTAudioClip3D::getCamera(){
  return 0;
}

void WTAudioClip3D::setCamera(WTCamera* camera){}

void WTAudioClip3D::removeCamera(){}
