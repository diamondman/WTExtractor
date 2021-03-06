#pragma once

#include "WT.hpp"

class WTVisualizer {

public:
  WTVisualizer(WT* wt_,
               const char* Visualizer_Type,
               const char* Get_Audio_From,
               int Number_Of_Data_Bins);

  float getBinData(int Bin_Number);

  char* getBinDataAsString(int Start_Bin_Number,
                           int End_Bin_Number);

  void updateData(int Data_Type,
                  float Reserved_1,
                  char* Reserved_2);

  void setBinFreq(int Bin_Number,
                  float Frequency);

  float getBinFreq(int Bin_Number);

  //[id(0x000036b6), hidden]
  char* getInfo(int Type);

  int getPlaybackPosition();

  int getPlaybackLength();

  bool updateProperties();

  char* getPropertyAsString(char* Name,
                            int mostRecent = 1);

  void setReceiverInfo(char* str,
                       int ul1 = 0,
                       int ul2 = 0,
                       int ul3 = 0);

protected:
  WT* wt;
};
