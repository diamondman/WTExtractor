#pragma once

class WTFile;

class WTJoystick {

public:
  int getCount();

  int getButtonCount(int Joystick_Number = 0);

  int getAxisFlags(int Joystick_Number = 0);

  int getPOVCount(int Joystick_Number = 0);

  bool setNotifyEvent(bool Turn_Joystick_Events_On,
                      int Joystick_Number = 0);

  int getButtonState(int Joystick_Number = 0);

  int getPosition(int Axis_Number,
                  int Joystick_Number = 0);

  int getPOVState(int POV_Number,
                  int Joystick_Number = 0);

  int getEventJoystick();

  int getEventTime();

  int getButtonStateEvent();

  int getAxisStateEvent();

  int getPOVStateEvent(int POV);

  void setSensitivity(int Sensitivity = 0,
                      int Joystick_Number = 0);

  void setDeadZone(int Dead_Zone = 0,
                   int Joystick_Number = 0);

  void setPositionRange(int Range,
                        int Joystick_Number = 0);

  int getSensitivity(int Joystick_Number = 0);

  int getDeadZone(int Joystick_Number = 0);

  int getPositionRange(int Joystick_Number = 0);

  int getPositionEvent(int Axis_Number);

  bool getNotifyEvent(int Joystick_Number = 0);

  char* getHardwareName(int Joystick_Number = 0);

  void reset(int Reserved = 0);

  int getEffectByName(char* Effect_Name,
                      int Joystick_Number = 0);

  int getEffectCount(int Joystick_Number = 0);

  char* getEffectName(int Effect_Number,
                      int Joystick_Number = 0);

  float getGain(int Effect_Number,
                int Joystick_Number = 0);

  int getSpecialFlags(int Joystick_Number = 0);

  void loadEffectsFromFile(WTFile* Effects_File,
                           int Joystick_Number = 0);

  void setGain(float Gain,
               int Effect_Number,
               int Joystick_Number = 0);

  void startEffect(int Effect_Number,
                   int Joystick_Number = 0);

  int startEffectOnButton(int Effect_Number,
                          int Button_Number,
                          int Repeat_Interval,
                          int Joystick_Number = 0);

  void stopEffect(int Effect_Number,
                  int Joystick_Number = 0);

  void stopEffectOnButton(int Effect_Number,
                          int Button_Number,
                          int Joystick_Number = 0);
};
