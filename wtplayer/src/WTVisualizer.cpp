#include "basetypes.hpp"
#include "WTVisualizer.hpp"

WTVisualizer::WTVisualizer(){
}

WTVisualizer::WTVisualizer(char* Visualizer_Type,
                           char* Get_Audio_From,
                           int Number_Of_Data_Bins){
}

float WTVisualizer::getBinData(int Bin_Number){
  APILOG;
  return 0;
}

char* WTVisualizer::getBinDataAsString(int Start_Bin_Number,
                         int End_Bin_Number){
  APILOG;
  return (char*)"";
}

void WTVisualizer::updateData(int Data_Type,
                              float Reserved_1,
                              char* Reserved_2){
  APILOG;
}

void WTVisualizer::setBinFreq(int Bin_Number,
                              float Frequency){
  APILOG;
}

float WTVisualizer::getBinFreq(int Bin_Number){
  APILOG;
  return 0;
}

//[id(0x000036b6), hidden]
char* WTVisualizer::getInfo(int Type){
  APILOG;
  return (char*)"";
}

int WTVisualizer::getPlaybackPosition(){
  APILOG;
  return 0;
}

int WTVisualizer::getPlaybackLength(){
  APILOG;
  return 0;
}

bool WTVisualizer::updateProperties(){
  APILOG;
  return false;
}

char* WTVisualizer::getPropertyAsString(char* Name,
                                        int mostRecent){
  APILOG;
  return (char*)"";
}

void WTVisualizer::setReceiverInfo(char* str,
                                   int ul1,
                                   int ul2,
                                   int ul3){
  APILOG;
}
