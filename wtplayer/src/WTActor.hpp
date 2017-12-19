#pragma once

#include "WTGroup.hpp"

class WTBitmap;
class WTSurfaceShader;

class WTActor : public WTGroup {

public:
  int getMaterialCount();

  char* getMaterialName(int Material_Number);

  void setOpacity(int Opacity);

  void setColor(int Red,
                int Green,
                int Blue);

  void setMaterial(WTBitmap* Bitmap,
                   char* Part_Of_Actor = (char*)"/");

  void removeMaterial(char* Material_Name = (char*)"/");

  int getMotionCount();

  char* getMotionName(int Motion_Number);

  float getMotionLength(char* Motion_Name);

  void playMotion(char* Motion_Name,
                  int Play_Motion_Forever = 0,
                  int Wait_Until_Loaded = 0,
                  float Speed = 1,
                  float Start_At_Time = 0,
                  float Notify_Before_Finishing = 0);

  void blendMotion(char* Motion_Name,
                   float Speed,
                   float Start_At_Time,
                   float Blend_Time,
                   float Initial_Blend_Amount,
                   float Final_Blend_Amount,
                   int Play_Motion_Forever = 0,
                   int Wait_Until_Loaded = 0,
                   float Notify_Before_Finishing = 0);

  void stopMotion(char* Motion_Name = (char*)"/");

  void setTexture(WTBitmap* Bitmap,
                  char* Part_Name = (char*)"/");

  void removeTexture(char* Part_Name = (char*)"/");

  int getPartCount();

  char* getPartName(int Part_Number);

  void setLODQuality(float quality);

  void setLODMax(float max);

  void setSurfaceShader(WTSurfaceShader* pShader,
                        char* Part_Of_Actor = (char*)"/");

  float getLODQuality();

  float getLODMax();

  void setLightMask(int LightMask);

  int getLightMask();

  void setMotionSpeed(float Speed);

  float getBlendAmount(int BlendMotionNumber);

  int getPlayingMotionCount();

  int getPlayingMotion(int BlendMotionNumber);

  float getPlayingMotionTime(int BlendMotionNumber);

  int getMotionNoteCount(int MotionNumber,
                         float StartTime,
                         float EndTime);

  char* getMotionNote(int MotionNumber,
                      int NoteNumber,
                      float StartTime,
                      float EndTime);

  float getMotionNoteTime(int MotionNumber,
                          int NoteNumber,
                          float StartTime,
                          float EndTime);

  char* getNextMotionNote();

  void setCollisionLOD(float bias);

  float getCollisionLOD();
};
