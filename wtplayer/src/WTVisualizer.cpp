#include "WTVisualizer.hpp"

float WTVisualizer::getBinData(int Bin_Number){
  return 0;
}

char* WTVisualizer::getBinDataAsString(int Start_Bin_Number,
                         int End_Bin_Number){
  return (char*)"";
}

void WTVisualizer::updateData(int Data_Type,
                              float Reserved_1,
                              char* Reserved_2){}

void WTVisualizer::setBinFreq(int Bin_Number,
                              float Frequency){}

float WTVisualizer::getBinFreq(int Bin_Number){
  return 0;
}

//[id(0x000036b6), hidden]
char* WTVisualizer::getInfo(int Type){
  return (char*)"";
}

int WTVisualizer::getPlaybackPosition(){
  return 0;
}

int WTVisualizer::getPlaybackLength(){
  return 0;
}

int WTVisualizer::updateProperties(){
  return 0;
}

char* WTVisualizer::getPropertyAsString(char* Name,
                                        int mostRecent){
  return (char*)"";
}

void WTVisualizer::setReceiverInfo(char* str,
                                   int ul1,
                                   int ul2,
                                   int ul3){}
