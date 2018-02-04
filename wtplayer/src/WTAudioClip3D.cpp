#include "basetypes.hpp"

#include "WTAudioClip3D.hpp"
#include "WTCamera.hpp"

WTAudioClip3D::WTAudioClip3D(WT* wt_,
                             char* File_Name,
                             int WTCache_Type) :
  WTGroup(wt_) {
}

WTAudioClip3D::~WTAudioClip3D() {
  if(this->camera)
    this->camera->Release();
  this->camera = NULL;
}

void WTAudioClip3D::start(int loop,
                          int wait){
  APILOG;
}

void WTAudioClip3D::stop(){
  APILOG;
}

bool WTAudioClip3D::isPlaying(){
  APILOG;
  return false;
}

float WTAudioClip3D::getDoppler(){
  APILOG;
  return 0;
}

void WTAudioClip3D::setDoppler(float Rate){
  APILOG;
}

int WTAudioClip3D::getVolumeScale(){
  APILOG;
  return 0;
}

void WTAudioClip3D::setVolumeScale(int vol){
  APILOG;
}

float WTAudioClip3D::getPlaybackRateScale(){
  APILOG;
  return 0;
}

void WTAudioClip3D::setPlaybackRateScale(float Rate){
  APILOG;
}

float WTAudioClip3D::getMinDistance(){
  APILOG;
  return 0;
}

void WTAudioClip3D::setMinDistance(float min){
  APILOG;
}

float WTAudioClip3D::getMaxDistance(){
  APILOG;
  return 0;
}

void WTAudioClip3D::setMaxDistance(float max){
  APILOG;
}

int WTAudioClip3D::getPlaybackLength(){
  APILOG;
  return 0;
}

int WTAudioClip3D::getPlaybackPosition(){
  APILOG;
  return 0;
}

WTCamera* WTAudioClip3D::getCamera(){
  APILOG;
  return this->camera;
}

void WTAudioClip3D::setCamera(WTCamera* camera){
  APILOG;
  if(this->camera)
    this->camera->Release();
  this->camera = camera;
  this->camera->AddRef();
}

void WTAudioClip3D::removeCamera(){
  APILOG;
  if(this->camera) {
    this->camera->Release();
    this->camera = NULL;
  }
}
