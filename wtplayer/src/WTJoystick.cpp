#include "WTJoystick.hpp"
#include "WTFile.hpp"

int WTJoystick::getCount(){
  return 0;
}

int WTJoystick::getButtonCount(int Joystick_Number){
  return 0;
}

int WTJoystick::getAxisFlags(int Joystick_Number){
  return 0;
}

int WTJoystick::getPOVCount(int Joystick_Number){
  return 0;
}

bool WTJoystick::setNotifyEvent(bool Turn_Joystick_Events_On,
                    int Joystick_Number){
  return false;
}

int WTJoystick::getButtonState(int Joystick_Number){
  return 0;
}

int WTJoystick::getPosition(int Axis_Number,
                int Joystick_Number){
  return 0;
}

int WTJoystick::getPOVState(int POV_Number,
                int Joystick_Number){
  return 0;
}

int WTJoystick::getEventJoystick(){
  return 0;
}

int WTJoystick::getEventTime(){
  return 0;
}

int WTJoystick::getButtonStateEvent(){
  return 0;
}

int WTJoystick::getAxisStateEvent(){
  return 0;
}

int WTJoystick::getPOVStateEvent(int POV){
  return 0;
}

void WTJoystick::setSensitivity(int Sensitivity,
                    int Joystick_Number){}

void WTJoystick::setDeadZone(int Dead_Zone,
                 int Joystick_Number){}

void WTJoystick::setPositionRange(int Range,
                      int Joystick_Number){}

int WTJoystick::getSensitivity(int Joystick_Number){
  return 0;
}

int WTJoystick::getDeadZone(int Joystick_Number){
  return 0;
}

int WTJoystick::getPositionRange(int Joystick_Number){
  return 0;
}

int WTJoystick::getPositionEvent(int Axis_Number){
  return 0;
}

bool WTJoystick::getNotifyEvent(int Joystick_Number){
  return false;
}

char* WTJoystick:: getHardwareName(int Joystick_Number){
  return (char*)"";
}

void WTJoystick::reset(int Reserved){}

int WTJoystick::getEffectByName(char* Effect_Name,
                    int Joystick_Number){
  return 0;
}

int WTJoystick::getEffectCount(int Joystick_Number){
  return 0;
}

char* WTJoystick::getEffectName(int Effect_Number,
                    int Joystick_Number){
  return (char*)"";
}

float WTJoystick::getGain(int Effect_Number,
              int Joystick_Number){
  return 0;
}

int WTJoystick::getSpecialFlags(int Joystick_Number){
  return 0;
}

void WTJoystick::loadEffectsFromFile(WTFile* Effects_File,
                         int Joystick_Number){}

void WTJoystick::setGain(float Gain,
             int Effect_Number,
             int Joystick_Number){}

void WTJoystick::startEffect(int Effect_Number,
                 int Joystick_Number){}

int WTJoystick::startEffectOnButton(int Effect_Number,
                        int Button_Number,
                        int Repeat_Interval,
                        int Joystick_Number){
  return 0;
}

void WTJoystick::stopEffect(int Effect_Number,
                int Joystick_Number){}

void WTJoystick::stopEffectOnButton(int Effect_Number,
                        int Button_Number,
                        int Joystick_Number){}
