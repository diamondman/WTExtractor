#pragma once

#include "WTObject.hpp"

class WTVector3D;
class WTOrientation3D;
class WTCollisionInfo;
class WTSurfaceShader;

class WTContainer : public WTObject {

public:
  void setPosition(float x,
                   float y,
                   float Z);

  WTVector3D* getPosition();

  void setAbsolutePosition(float x,
                           float y,
                           float Z);

  WTVector3D* getAbsolutePosition();

  void moveBy(float x,
              float y,
              float Z);

  void setOrientation(float x,
                      float y,
                      float Z,
                      float Angle);

  WTOrientation3D* getOrientation();

  WTVector3D* getOrientationVector();

  WTVector3D* getOrientationUp();

  void setOrientationVector(float X_Forward,
                            float Y_Forward,
                            float Z_Forward,
                            float X_Up,
                            float Y_Up,
                            float Z_Up);

  void setConstantRotation(float x,
                           float y,
                           float Z,
                           float Angle);

  WTOrientation3D* getConstantRotation();

  void setRotation(float x,
                   float y,
                   float Z,
                   float Angle,
                   int Relative_To_World = 0);

  void setLookAt(WTContainer* Container_To_Look_At,
                 int Look_Type = 0);

  void unsetLookAt();

  WTContainer* getLookAt();

  void attach(WTObject* Object_To_Attach);

  void attachBitmap(WTObject* Bitmap_To_Add,
                    float Scale_Width,
                    float Scale_Height,
                    int X_Center,
                    int Y_Center);

  void detach();

  WTObject* getAttached();

  void setBitmapSize(float Scale_Width,
                     float Scale_Height);

  void setBitmapOpacity(int Opacity);

  void setScale(float x,
                float y = 0,
                float Z = 0);

  void setAbsoluteScale(float x,
                        float y = 0,
                        float Z = 0);

  void setScaleTare();

  void setPickPriority(int Pick_Priority);

  int getPickPriority();

  void highlight(bool Turn_On_Highlight);

  bool isHighlighted();

  void setVisible(bool Turn_On_Visibility);

  bool getVisible();

  char* getPositionAsString();

  char* getAbsolutePositionAsString();

  char* getOrientationVectorAsString();

  char* getOrientationUpAsString();

  void setAbsoluteOrientation(float x,
                              float y,
                              float Z,
                              float Angle);

  WTCollisionInfo* checkCollision(float x,
                                  float y,
                                  float Z,
                                  bool Position_Is_Relative_To_Object,
                                  int Collision_Mask,
                                  int Collision_Detail = 3,
                                  int Collision_Flags = 0,
                                  int Reserved = 0);

  WTVector3D* getAbsoluteOrientationVector();

  WTVector3D* getAbsoluteOrientationUp();

  void setAbsoluteOrientationVector(float X_Forward,
                                    float Y_Forward,
                                    float Z_Forward,
                                    float X_Up,
                                    float Y_Up,
                                    float Z_Up);

  void setCollisionBox(float X1,
                       float X2,
                       float Y1,
                       float Y2,
                       float Z1,
                       float Z2,
                       int Reserved = 0);

  void setCollisionMask(int Mask,
                        int Reserved = 0);

  int getCollisionMask();

  void makeCollisionBox(int Box_Type = 3,
                        int Box_Flags = 0,
                        int Reserved = 0);

  void attachSurfaceShader(WTSurfaceShader* Shader_To_Add,
                           float Scale_Width,
                           float Scale_Height,
                           int X_Center,
                           int Y_Center);

  void setBitmapOrientation(float Amount);

  void setBitmapTextureRect(float u0,
                            float v0,
                            float U1,
                            float V1);

  WTVector3D* getGeometryExtents(bool Max_Extents,
                                 bool With_Children = false);

};
