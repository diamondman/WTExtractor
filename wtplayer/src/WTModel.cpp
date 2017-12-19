#include "WTModel.hpp"
#include "basetypes.hpp"
#include "WTBitmap.hpp"
#include "WTSurfaceShader.hpp"
#include "WTVector3D.hpp"

void setColor(int Red,
              int Green,
              int Blue,
              char* Part_Name){}

void WTModel::setScale(float x,
                       float y,
                       float Z){}

void WTModel::setAbsoluteScale(float x,
                               float y,
                               float Z){}

void WTModel::setScaleTare(){}

void WTModel::setTexture(WTBitmap* Texture_To_Use,
                         char* Part_Name,
                         int loadOrder){}

void WTModel::setTextureRect(char* Face_Name,
                             float U1,
                             float V1,
                             float U2,
                             float V2){}

WTVector3D* WTModel::getVertex(int Vertex_Number,
                               char* Part_Name){
  return 0;
}

void WTModel::setOpacity(int Opacity,
                         char* Part_Name){}

void WTModel::setRGBA(int Red,
                      int Green,
                      int Blue,
                      int Opacity,
                      char* Part_Name){}

void WTModel::setMaterial(int Red_Emissivity,
                          int Green_Emissivity,
                          int Blue_Emissivity,
                          float Specular_Power,
                          int Red_Specular,
                          int Green_Specular,
                          int Blue_Specular){}

void WTModel::removeTexture(char* Part_Name){}

void WTModel::setPatchHeightExtents(float Minimum_Height,
                                    float Maximum_Height){}

void WTModel::setPatchPtHeight(int S,
                               int T,
                               int Height,
                               int Reserved){}

void WTModel::setPatchPtUV(int S,
                           int T,
                           float U,
                           float V,
                           char* Side){}

void WTModel::setPatchAreaUV(int S1,
                             int T1,
                             int S2,
                             int T2,
                             float U1,
                             float V1,
                             float U2,
                             float V2,
                             char* Side){}

void WTModel::setPatchTileUV(int S,
                             int T,
                             float U1,
                             float V1,
                             float U2,
                             float V2,
                             float U3,
                             float V3,
                             float U4,
                             float V4,
                             char* Side){}

void WTModel::setPatchPtPos(int S,
                            int T,
                            float x,
                            float y,
                            float Z,
                            int Reserved){}

int WTModel::hasDxAnimations(){
  return 0;
}

bool WTModel::isDxAnimationPlaying(int Animation_Number){
  return false;
}

void WTModel::playDxAnimation(float Start_At_Time,
                              float Stop_At_Time,
                              bool Play_Animation_Forever,
                              bool Wait_Until_Loaded,
                              int Animation_Number){}

void WTModel::setDxAnimationTime(float Time,
                                 int Animation_Number){}

void WTModel::setDxAnimationRate(int Rate,
                                 int Animation_Number){}

void WTModel::stopDxAnimation(int Animation_Number){}

int WTModel::getDxAnimationRate(int Animation_Number){
  return 0;
}

float WTModel::getDxAnimationLength(int Animation_Number){
  return 0;
}

void WTModel::setPatchHeightWithString(char* Heights,
                                       int Height,
                                       int Width,
                                       int S,
                                       int T){}

void WTModel::updateNormals(int Normal_Type){}

void WTModel::setPatchTileTexture(int S,
                                  int T,
                                  WTBitmap* Texture_To_Use,
                                  char* Side){}

void WTModel::setPatchTileColor(int S,
                                int T,
                                unsigned char Red,
                                unsigned char Green,
                                unsigned char Blue,
                                unsigned char Opacity,
                                char* Side){}

void WTModel::setPatchPtColor(int S,
                              int T,
                              unsigned char Red,
                              unsigned char Green,
                              unsigned char Blue,
                              unsigned char Opacity,
                              char* Side){}

void WTModel::setPatchTileMaterial(int S,
                                   int T,
                                   int Red_Emissivity,
                                   int Green_Emissivity,
                                   int Blue_Emissivity,
                                   float Specular_Power,
                                   int Red_Specular,
                                   int Green_Specular,
                                   int Blue_Specular,
                                   char* Side){}

void WTModel::removePatchAreaTexture(int S1,
                                     int T1,
                                     int S2,
                                     int T2,
                                     char* Side){}

void WTModel::setSurfaceShader(WTSurfaceShader* SurfaceShader_To_Use,
                               char* Part_Name,
                               int loadOrder){}

void WTModel::setPatchTileSurfaceShader(int S,
                                        int T,
                                        WTSurfaceShader* SurfaceShader_To_Use,
                                        char* Side){}

void WTModel::setPatchPtNormal(int S,
                               int T,
                               float x,
                               float y,
                               float Z,
                               int Reserved){}

void WTModel::setLightMask(int LightMask){}

int WTModel::getLightMask(){
  return 0;
}

void WTModel::setVertexColor(int Vertex,
                             unsigned char Red,
                             unsigned char Green,
                             unsigned char Blue,
                             unsigned char Opacity){}

void WTModel::setFaceTexture(int Face,
                             WTBitmap* Texture_To_Use){}

void WTModel::setVertexUV(int Vertex,
                          float U,
                          float V){}

void WTModel::setFaceNormal(int Face,
                            float x,
                            float y,
                            float Z){}

void WTModel::setFaceColor(int Face,
                           unsigned char Red,
                           unsigned char Green,
                           unsigned char Blue,
                           unsigned char Opacity){}

void WTModel::sweep(float Start_Angle,
                    float End_Angle,
                    int Sections,
                    float x,
                    float y,
                    float Z,
                    float Axis_X,
                    float Axis_Y,
                    float Axis_Z,
                    bool Top_Cap,
                    bool Bottom_Cap){}

int WTModel::getVertexCount(){
  return 0;
}

int WTModel::getFaceCount(){
  return 0;
}

void WTModel::setVertexNormal(int Vertex,
                              float x,
                              float y,
                              float Z){}

void WTModel::setVertexPosition(int Vertex,
                                float x,
                                float y,
                                float Z){}

void WTModel::setFaceSurfaceShader(int Face,
                                   WTSurfaceShader* Surface_Shader){}

void WTModel::setFaces(VARIANT Index_Array,
                       VARIANT Face_Array,
                       int Index_Array_Size,
                       int Index_Lower_Bound,
                       int Face_Lower_Bound){}

void WTModel::setFace(int Face,
                      int Vertex1,
                      int Vertex2,
                      int Vertex3){}

int WTModel::addVertex(float x,
                       float y,
                       float Z){
  return 0;
}

int WTModel::addVertices(VARIANT Vertex_Array,
                         VARIANT Normal_Array, //optional
                         int Vertex_Array_Size,
                         int Vertex_Lower_Bound,
                         int Normal_Lower_Bound){
  return 0;
}

int WTModel::removeVertex(int Vertex){
  return 0;
}

int WTModel::removeVertices(VARIANT Vertex_Array){
  return 0;
}

int WTModel::addFace(int Vertex1,
                     int Vertex2,
                     int Vertex3){
  return 0;
}

int WTModel::addFaces(VARIANT Face_Array,
                      int Face_Array_Size,
                      int Face_Lower_Bound){
  return 0;
}

int WTModel::removeFace(int Face){
  return 0;
}

int WTModel::removeFaces(VARIANT Face_Array){
  return 0;
}

void WTModel::setVerticesPositions(VARIANT Vertex_Array,
                                   VARIANT Positions_Array,
                                   int Vertex_Array_Size,
                                   int Vertex_Lower_Bound,
                                   int Pos_Lower_Bound){}

void WTModel::setUVMapping(int Mapping){}

void WTModel::setVerticesUVs(VARIANT Vertex_Array,
                             VARIANT UVs_Array,
                             int Vertex_Array_Size,
                             int Vertex_Lower_Bound,
                             int UV_Lower_Bound){}

void WTModel::clear(bool ClearTextures){}
