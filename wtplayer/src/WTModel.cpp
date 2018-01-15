#include "basetypes.hpp"
#include "WTModel.hpp"
#include "WTBitmap.hpp"
#include "WTSurfaceShader.hpp"
#include "WTVector3D.hpp"

WTModel::WTModel(){
}

WTModel::WTModel(char* File_Name,
                 int WTCache_Type){
}

void setColor(int Red,
              int Green,
              int Blue,
              char* Part_Name){
  APILOG;
}

void WTModel::setScale(float x,
                       float y,
                       float Z){
  APILOG;
}

void WTModel::setAbsoluteScale(float x,
                               float y,
                               float Z){
  APILOG;
}

void WTModel::setScaleTare(){
  APILOG;
}

void WTModel::setTexture(WTBitmap* Texture_To_Use,
                         char* Part_Name,
                         int loadOrder){
  APILOG;
}

void WTModel::setTextureRect(char* Face_Name,
                             float U1,
                             float V1,
                             float U2,
                             float V2){
  APILOG;
}

WTVector3D* WTModel::getVertex(int Vertex_Number,
                               char* Part_Name){
  APILOG;
  return new WTVector3D();
}

void WTModel::setOpacity(int Opacity,
                         char* Part_Name){
  APILOG;
}

void WTModel::setRGBA(int Red,
                      int Green,
                      int Blue,
                      int Opacity,
                      char* Part_Name){
  APILOG;
}

void WTModel::setMaterial(int Red_Emissivity,
                          int Green_Emissivity,
                          int Blue_Emissivity,
                          float Specular_Power,
                          int Red_Specular,
                          int Green_Specular,
                          int Blue_Specular){
  APILOG;
}

void WTModel::removeTexture(char* Part_Name){
  APILOG;
}

void WTModel::setPatchHeightExtents(float Minimum_Height,
                                    float Maximum_Height){
  APILOG;
}

void WTModel::setPatchPtHeight(int S,
                               int T,
                               int Height,
                               int Reserved){
  APILOG;
}

void WTModel::setPatchPtUV(int S,
                           int T,
                           float U,
                           float V,
                           char* Side){
  APILOG;
}

void WTModel::setPatchAreaUV(int S1,
                             int T1,
                             int S2,
                             int T2,
                             float U1,
                             float V1,
                             float U2,
                             float V2,
                             char* Side){
  APILOG;
}

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
                             char* Side){
  APILOG;
}

void WTModel::setPatchPtPos(int S,
                            int T,
                            float x,
                            float y,
                            float Z,
                            int Reserved){
  APILOG;
}

int WTModel::hasDxAnimations(){
  APILOG;
  return 0;
}

bool WTModel::isDxAnimationPlaying(int Animation_Number){
  APILOG;
  return false;
}

void WTModel::playDxAnimation(float Start_At_Time,
                              float Stop_At_Time,
                              bool Play_Animation_Forever,
                              bool Wait_Until_Loaded,
                              int Animation_Number){
  APILOG;
}

void WTModel::setDxAnimationTime(float Time,
                                 int Animation_Number){
  APILOG;
}

void WTModel::setDxAnimationRate(int Rate,
                                 int Animation_Number){
  APILOG;
}

void WTModel::stopDxAnimation(int Animation_Number){
  APILOG;
}

int WTModel::getDxAnimationRate(int Animation_Number){
  APILOG;
  return 0;
}

float WTModel::getDxAnimationLength(int Animation_Number){
  APILOG;
  return 0;
}

void WTModel::setPatchHeightWithString(char* Heights,
                                       int Height,
                                       int Width,
                                       int S,
                                       int T){
  APILOG;
}

void WTModel::updateNormals(int Normal_Type){
  APILOG;
}

void WTModel::setPatchTileTexture(int S,
                                  int T,
                                  WTBitmap* Texture_To_Use,
                                  char* Side){
  APILOG;
}

void WTModel::setPatchTileColor(int S,
                                int T,
                                unsigned char Red,
                                unsigned char Green,
                                unsigned char Blue,
                                unsigned char Opacity,
                                char* Side){
  APILOG;
}

void WTModel::setPatchPtColor(int S,
                              int T,
                              unsigned char Red,
                              unsigned char Green,
                              unsigned char Blue,
                              unsigned char Opacity,
                              char* Side){
  APILOG;
}

void WTModel::setPatchTileMaterial(int S,
                                   int T,
                                   int Red_Emissivity,
                                   int Green_Emissivity,
                                   int Blue_Emissivity,
                                   float Specular_Power,
                                   int Red_Specular,
                                   int Green_Specular,
                                   int Blue_Specular,
                                   char* Side){
  APILOG;
}

void WTModel::removePatchAreaTexture(int S1,
                                     int T1,
                                     int S2,
                                     int T2,
                                     char* Side){
  APILOG;
}

void WTModel::setSurfaceShader(WTSurfaceShader* SurfaceShader_To_Use,
                               char* Part_Name,
                               int loadOrder){
  APILOG;
}

void WTModel::setPatchTileSurfaceShader(int S,
                                        int T,
                                        WTSurfaceShader* SurfaceShader_To_Use,
                                        char* Side){
  APILOG;
}

void WTModel::setPatchPtNormal(int S,
                               int T,
                               float x,
                               float y,
                               float Z,
                               int Reserved){
  APILOG;
}

void WTModel::setLightMask(int LightMask){
  APILOG;
}

int WTModel::getLightMask(){
  APILOG;
  return 0;
}

void WTModel::setVertexColor(int Vertex,
                             unsigned char Red,
                             unsigned char Green,
                             unsigned char Blue,
                             unsigned char Opacity){
  APILOG;
}

void WTModel::setFaceTexture(int Face,
                             WTBitmap* Texture_To_Use){
  APILOG;
}

void WTModel::setVertexUV(int Vertex,
                          float U,
                          float V){
  APILOG;
}

void WTModel::setFaceNormal(int Face,
                            float x,
                            float y,
                            float Z){
  APILOG;
}

void WTModel::setFaceColor(int Face,
                           unsigned char Red,
                           unsigned char Green,
                           unsigned char Blue,
                           unsigned char Opacity){
  APILOG;
}

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
                    bool Bottom_Cap){
  APILOG;
}

int WTModel::getVertexCount(){
  APILOG;
  return 0;
}

int WTModel::getFaceCount(){
  APILOG;
  return 0;
}

void WTModel::setVertexNormal(int Vertex,
                              float x,
                              float y,
                              float Z){
  APILOG;
}

void WTModel::setVertexPosition(int Vertex,
                                float x,
                                float y,
                                float Z){
  APILOG;
}

void WTModel::setFaceSurfaceShader(int Face,
                                   WTSurfaceShader* Surface_Shader){
  APILOG;
}

void WTModel::setFaces(int Index_Array[],
                       int Face_Array[],
                       int Index_Array_Size,
                       int Index_Lower_Bound,
                       int Face_Lower_Bound){
  APILOG;
}

void WTModel::setFace(int Face,
                      int Vertex1,
                      int Vertex2,
                      int Vertex3){
  APILOG;
}

int WTModel::addVertex(float x,
                       float y,
                       float Z){
  APILOG;
  return 0;
}

int WTModel::addVertices(float Vertex_Array[],
                         float Normal_Array[], //optional
                         int Vertex_Array_Size,
                         int Vertex_Lower_Bound,
                         int Normal_Lower_Bound){
  APILOG;
  return 0;
}

int WTModel::removeVertex(int Vertex){
  APILOG;
  return 0;
}

int WTModel::removeVertices(int Vertex_Array[]){
  APILOG;
  return 0;
}

int WTModel::addFace(int Vertex1,
                     int Vertex2,
                     int Vertex3){
  APILOG;
  return 0;
}

int WTModel::addFaces(int Face_Array[],
                      int Face_Array_Size,
                      int Face_Lower_Bound){
  APILOG;
  return 0;
}

int WTModel::removeFace(int Face){
  APILOG;
  return 0;
}

int WTModel::removeFaces(int Face_Array[]){
  APILOG;
  return 0;
}

void WTModel::setVerticesPositions(int Vertex_Array[],
                                   float Positions_Array[],
                                   int Vertex_Array_Size,
                                   int Vertex_Lower_Bound,
                                   int Pos_Lower_Bound){
  APILOG;
}

void WTModel::setUVMapping(int Mapping){
  APILOG;
}

void WTModel::setVerticesUVs(int Vertex_Array[],
                             float UVs_Array[],
                             int Vertex_Array_Size,
                             int Vertex_Lower_Bound,
                             int UV_Lower_Bound){
  APILOG;
}

void WTModel::clear(bool ClearTextures){
  APILOG;
}
