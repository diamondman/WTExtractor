#include "basetypes.hpp"
#include "WTActor.hpp"
#include "WTBitmap.hpp"
#include "WTSurfaceShader.hpp"

int WTActor::getMaterialCount(){
  APILOG;
  return 0;
}

char* WTActor::getMaterialName(int Material_Number){
  APILOG;
  return (char*) "";
}

void WTActor::setOpacity(int Opacity){
  APILOG;
}

void WTActor::setColor(int Red,
                       int Green,
                       int Blue){
  APILOG;
}

void WTActor::setMaterial(WTBitmap* Bitmap,
                          char* Part_Of_Actor){
  APILOG;
}

void WTActor::removeMaterial(char* Material_Name){
  APILOG;
}

int WTActor::getMotionCount(){
  APILOG;
  return 0;
}

char* WTActor::getMotionName(int Motion_Number){
  APILOG;
  return (char*)"";
}

float WTActor::getMotionLength(char* Motion_Name){
  APILOG;
  return 0;
}

void WTActor::playMotion(char* Motion_Name,
                         int Play_Motion_Forever,
                         int Wait_Until_Loaded,
                         float Speed,
                         float Start_At_Time,
                         float Notify_Before_Finishing){
  APILOG;
}

void WTActor::blendMotion(char* Motion_Name,
                          float Speed,
                          float Start_At_Time,
                          float Blend_Time,
                          float Initial_Blend_Amount,
                          float Final_Blend_Amount,
                          int Play_Motion_Forever,
                          int Wait_Until_Loaded,
                          float Notify_Before_Finishing){
  APILOG;
}

void WTActor::stopMotion(char* Motion_Name){
  APILOG;
}

void WTActor::setTexture(WTBitmap* Bitmap,
                         char* Part_Name){
  APILOG;
}

void WTActor::removeTexture(char* Part_Name){
  APILOG;
}

int WTActor::getPartCount(){
  APILOG;
  return 0;
}

char* WTActor::getPartName(int Part_Number){
  APILOG;
  return (char*)"";
}

void WTActor::setLODQuality(float quality){
  APILOG;
}

void WTActor::setLODMax(float max){
  APILOG;
}

void WTActor::setSurfaceShader(WTSurfaceShader* pShader,
                               char* Part_Of_Actor){
  APILOG;
}

float WTActor::getLODQuality(){
  APILOG;
  return 0;
}

float WTActor::getLODMax(){
  APILOG;
  return 0;
}

void WTActor::setLightMask(int LightMask){
  APILOG;
}

int WTActor::getLightMask(){
  APILOG;
  return 0;
}

void WTActor::setMotionSpeed(float Speed){
  APILOG;
}

float WTActor::getBlendAmount(int BlendMotionNumber){
  APILOG;
  return 0;
}

int WTActor::getPlayingMotionCount(){
  APILOG;
  return 0;
}

int WTActor::getPlayingMotion(int BlendMotionNumber){
  APILOG;
  return 0;
}

float WTActor::getPlayingMotionTime(int BlendMotionNumber){
  APILOG;
  return 0;
}

int WTActor::getMotionNoteCount(int MotionNumber,
                                float StartTime,
                                float EndTime){
  APILOG;
  return 0;
}

char* WTActor::getMotionNote(int MotionNumber,
                             int NoteNumber,
                             float StartTime,
                             float EndTime){
  APILOG;
  return (char*)0;
}

float WTActor::getMotionNoteTime(int MotionNumber,
                                 int NoteNumber,
                                 float StartTime,
                                 float EndTime){
  APILOG;
  return 0;
}

char* WTActor::getNextMotionNote(){
  APILOG;
  return (char*)0;
}

void WTActor::setCollisionLOD(float bias){
  APILOG;
}

float WTActor::getCollisionLOD(){
  APILOG;
  return 0;
}
