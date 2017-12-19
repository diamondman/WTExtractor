#include "WTActor.hpp"
#include "WTBitmap.hpp"
#include "WTSurfaceShader.hpp"

int WTActor::getMaterialCount(){
  return 0;
}

char* WTActor::getMaterialName(int Material_Number){
  return (char*) "";
}

void WTActor::setOpacity(int Opacity){}

void WTActor::setColor(int Red,
                       int Green,
                       int Blue){}

void WTActor::setMaterial(WTBitmap* Bitmap,
                          char* Part_Of_Actor){}

void WTActor::removeMaterial(char* Material_Name){}

int WTActor::getMotionCount(){
  return 0;
}

char* WTActor::getMotionName(int Motion_Number){
  return (char*)"";
}

float WTActor::getMotionLength(char* Motion_Name){
  return 0;
}

void WTActor::playMotion(char* Motion_Name,
                         int Play_Motion_Forever,
                         int Wait_Until_Loaded,
                         float Speed,
                         float Start_At_Time,
                         float Notify_Before_Finishing){}

void WTActor::blendMotion(char* Motion_Name,
                          float Speed,
                          float Start_At_Time,
                          float Blend_Time,
                          float Initial_Blend_Amount,
                          float Final_Blend_Amount,
                          int Play_Motion_Forever,
                          int Wait_Until_Loaded,
                          float Notify_Before_Finishing){}

void WTActor::stopMotion(char* Motion_Name){}

void WTActor::setTexture(WTBitmap* Bitmap,
                         char* Part_Name){}

void WTActor::removeTexture(char* Part_Name){}

int WTActor::getPartCount(){
  return 0;
}

char* WTActor::getPartName(int Part_Number){
  return (char*)"";
}

void WTActor::setLODQuality(float quality){}

void WTActor::setLODMax(float max){}

void WTActor::setSurfaceShader(WTSurfaceShader* pShader,
                               char* Part_Of_Actor){}

float WTActor::getLODQuality(){
  return 0;
}

float WTActor::getLODMax(){
  return 0;
}

void WTActor::setLightMask(int LightMask){}

int WTActor::getLightMask(){
  return 0;
}

void WTActor::setMotionSpeed(float Speed){}

float WTActor::getBlendAmount(int BlendMotionNumber){
  return 0;
}

int WTActor::getPlayingMotionCount(){
  return 0;
}

int WTActor::getPlayingMotion(int BlendMotionNumber){
  return 0;
}

float WTActor::getPlayingMotionTime(int BlendMotionNumber){
  return 0;
}

int WTActor::getMotionNoteCount(int MotionNumber,
                                float StartTime,
                                float EndTime){
  return 0;
}

char* WTActor::getMotionNote(int MotionNumber,
                             int NoteNumber,
                             float StartTime,
                             float EndTime){
  return (char*)0;
}

float WTActor::getMotionNoteTime(int MotionNumber,
                                 int NoteNumber,
                                 float StartTime,
                                 float EndTime){
  return 0;
}

char* WTActor::getNextMotionNote(){
  return (char*)0;
}

void WTActor::setCollisionLOD(float bias){}

float WTActor::getCollisionLOD(){
  return 0;
}
