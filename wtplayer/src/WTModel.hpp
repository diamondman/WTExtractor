#pragma once

#include "WTObject.hpp"
#include "basetypes.hpp"

class WTBitmap;
class WTSurfaceShader;
class WTVector3D;

class WTModel : public WTObject {

public:
  WTModel();

  WTModel(char* File_Name,
          int WTCache_Type);

  void setColor(int Red,
                int Green,
                int Blue,
                char* Part_Name = (char*)"/");

  void setScale(float x,
                float y = 0,
                float Z = 0);

  void setAbsoluteScale(float x,
                        float y = 0,
                        float Z = 0);

  void setScaleTare();

  void setTexture(WTBitmap* Texture_To_Use,
                  char* Part_Name = (char*)"/",
                  int loadOrder = 0);

  void setTextureRect(char* Face_Name,
                      float U1,
                      float V1,
                      float U2,
                      float V2);

  WTVector3D* getVertex(int Vertex_Number,
                        char* Part_Name = (char*)"/");

  void setOpacity(int Opacity,
                  char* Part_Name = (char*)"/");

  void setRGBA(int Red,
               int Green,
               int Blue,
               int Opacity,
               char* Part_Name = (char*)"/");

  void setMaterial(int Red_Emissivity,
                   int Green_Emissivity,
                   int Blue_Emissivity,
                   float Specular_Power,
                   int Red_Specular,
                   int Green_Specular,
                   int Blue_Specular);

  void removeTexture(char* Part_Name = (char*)"/");

  void setPatchHeightExtents(float Minimum_Height,
                             float Maximum_Height);

  void setPatchPtHeight(int S,
                        int T,
                        int Height,
                        int Reserved = 0);

  void setPatchPtUV(int S,
                    int T,
                    float U,
                    float V,
                    char* Side = (char*)"/");

  void setPatchAreaUV(int S1,
                      int T1,
                      int S2,
                      int T2,
                      float U1,
                      float V1,
                      float U2,
                      float V2,
                      char* Side = (char*)"/");

  void setPatchTileUV(int S,
                      int T,
                      float U1,
                      float V1,
                      float U2,
                      float V2,
                      float U3,
                      float V3,
                      float U4,
                      float V4,
                      char* Side = (char*)"/");

  void setPatchPtPos(int S,
                     int T,
                     float x,
                     float y,
                     float Z,
                     int Reserved = 0);

  int hasDxAnimations();

  bool isDxAnimationPlaying(int Animation_Number = -1);

  void playDxAnimation(float Start_At_Time = 0,
                       float Stop_At_Time = -1,
                       bool Play_Animation_Forever = 1,
                       bool Wait_Until_Loaded = 0,
                       int Animation_Number = -1);

  void setDxAnimationTime(float Time,
                          int Animation_Number = -1);

  void setDxAnimationRate(int Rate,
                          int Animation_Number = -1);

  void stopDxAnimation(int Animation_Number = -1);

  int getDxAnimationRate(int Animation_Number = -1);

  float getDxAnimationLength(int Animation_Number = -1);

  void setPatchHeightWithString(char* Heights,
                                int Height = -1,
                                int Width = -1,
                                int S = 0,
                                int T = 0);

  void updateNormals(int Normal_Type = 0);

  void setPatchTileTexture(int S,
                           int T,
                           WTBitmap* Texture_To_Use,
                           char* Side = (char*)"/");

  void setPatchTileColor(int S,
                         int T,
                         unsigned char Red,
                         unsigned char Green,
                         unsigned char Blue,
                         unsigned char Opacity = 255,
                         char* Side = (char*)"/");

  void setPatchPtColor(int S,
                       int T,
                       unsigned char Red,
                       unsigned char Green,
                       unsigned char Blue,
                       unsigned char Opacity = 255,
                       char* Side = (char*)"/");

  void setPatchTileMaterial(int S,
                            int T,
                            int Red_Emissivity,
                            int Green_Emissivity,
                            int Blue_Emissivity,
                            float Specular_Power,
                            int Red_Specular,
                            int Green_Specular,
                            int Blue_Specular,
                            char* Side = (char*)"/");

  void removePatchAreaTexture(int S1,
                              int T1,
                              int S2,
                              int T2,
                              char* Side = (char*)"/");

  void setSurfaceShader(WTSurfaceShader* SurfaceShader_To_Use,
                        char* Part_Name = (char*)"/",
                        int loadOrder = 0);

  void setPatchTileSurfaceShader(int S,
                                 int T,
                                 WTSurfaceShader* SurfaceShader_To_Use,
                                 char* Side = (char*)"/");

  void setPatchPtNormal(int S,
                        int T,
                        float x,
                        float y,
                        float Z,
                        int Reserved = 0);

  void setLightMask(int LightMask);

  int getLightMask();

  void setVertexColor(int Vertex,
                      unsigned char Red,
                      unsigned char Green,
                      unsigned char Blue,
                      unsigned char Opacity = 255);

  void setFaceTexture(int Face,
                      WTBitmap* Texture_To_Use);

  void setVertexUV(int Vertex,
                   float U,
                   float V);

  void setFaceNormal(int Face,
                     float x,
                     float y,
                     float Z);

  void setFaceColor(int Face,
                    unsigned char Red,
                    unsigned char Green,
                    unsigned char Blue,
                    unsigned char Opacity = 255);

  void sweep(float Start_Angle,
             float End_Angle,
             int Sections,
             float x,
             float y,
             float Z,
             float Axis_X,
             float Axis_Y,
             float Axis_Z,
             bool Top_Cap,
             bool Bottom_Cap);

  int getVertexCount();

  int getFaceCount();

  void setVertexNormal(int Vertex,
                       float x,
                       float y,
                       float Z);

  void setVertexPosition(int Vertex,
                         float x,
                         float y,
                         float Z);

  void setFaceSurfaceShader(int Face,
                            WTSurfaceShader* Surface_Shader);

  void setFaces(int Index_Array[],
                int Face_Array[],
                int Index_Array_Size = -1,
                int Index_Lower_Bound = 0,
                int Face_Lower_Bound = 0);

  void setFace(int Face,
               int Vertex1,
               int Vertex2,
               int Vertex3);

  int addVertex(float x,
                float y,
                float Z);

  int addVertices(float Vertex_Array[],
                  float Normal_Array[] = 0, //optional
                  int Vertex_Array_Size = -1,
                  int Vertex_Lower_Bound = 0,
                  int Normal_Lower_Bound = 0);

  int removeVertex(int Vertex);

  int removeVertices(int Vertex_Array[]);

  int addFace(int Vertex1,
              int Vertex2,
              int Vertex3);

  int addFaces(int Face_Array[],
               int Face_Array_Size = -1,
               int Face_Lower_Bound = 0);

  int removeFace(int Face);

  int removeFaces(int Face_Array[]);

  void setVerticesPositions(int Vertex_Array[],
                            float Positions_Array[],
                            int Vertex_Array_Size = -1,
                            int Vertex_Lower_Bound = 0,
                            int Pos_Lower_Bound = 0);

  void setUVMapping(int Mapping);

  void setVerticesUVs(int Vertex_Array[],
                      float UVs_Array[],
                      int Vertex_Array_Size = -1,
                      int Vertex_Lower_Bound = 0,
                      int UV_Lower_Bound = 0);

  void clear(bool ClearTextures = true);
};
