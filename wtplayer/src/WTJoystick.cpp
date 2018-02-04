#include "basetypes.hpp"

#include "WTJoystick.hpp"
#include "WTFile.hpp"

int WTJoystick::getCount(){
  APILOG;
  return 0;
}

int WTJoystick::getButtonCount(int Joystick_Number){
  APILOG;
  return 0;
}

int WTJoystick::getAxisFlags(int Joystick_Number){
  APILOG;
  return 0;
}

int WTJoystick::getPOVCount(int Joystick_Number){
  APILOG;
  return 0;
}

bool WTJoystick::setNotifyEvent(bool Turn_Joystick_Events_On,
                    int Joystick_Number){
  APILOG;
  return false;
}

int WTJoystick::getButtonState(int Joystick_Number){
  APILOG;
  return 0;
}

int WTJoystick::getPosition(int Axis_Number,
                int Joystick_Number){
  APILOG;
  return 0;
}

int WTJoystick::getPOVState(int POV_Number,
                int Joystick_Number){
  APILOG;
  return 0;
}

int WTJoystick::getEventJoystick(){
  APILOG;
  return 0;
}

int WTJoystick::getEventTime(){
  APILOG;
  return 0;
}

int WTJoystick::getButtonStateEvent(){
  APILOG;
  return 0;
}

int WTJoystick::getAxisStateEvent(){
  APILOG;
  return 0;
}

int WTJoystick::getPOVStateEvent(int POV){
  APILOG;
  return 0;
}

void WTJoystick::setSensitivity(int Sensitivity,
                    int Joystick_Number){
  APILOG;
}

void WTJoystick::setDeadZone(int Dead_Zone,
                 int Joystick_Number){
  APILOG;
}

void WTJoystick::setPositionRange(int Range,
                      int Joystick_Number){
  APILOG;
}

int WTJoystick::getSensitivity(int Joystick_Number){
  APILOG;
  return 0;
}

int WTJoystick::getDeadZone(int Joystick_Number){
  APILOG;
  return 0;
}

int WTJoystick::getPositionRange(int Joystick_Number){
  APILOG;
  return 0;
}

int WTJoystick::getPositionEvent(int Axis_Number){
  APILOG;
  return 0;
}

bool WTJoystick::getNotifyEvent(int Joystick_Number){
  APILOG;
  return false;
}

char* WTJoystick:: getHardwareName(int Joystick_Number){
  APILOG;
  return (char*)"";
}

void WTJoystick::reset(int Reserved){
  APILOG;
}

int WTJoystick::getEffectByName(char* Effect_Name,
                    int Joystick_Number){
  APILOG;
  return 0;
}

int WTJoystick::getEffectCount(int Joystick_Number){
  APILOG;
  return 0;
}

char* WTJoystick::getEffectName(int Effect_Number,
                    int Joystick_Number){
  APILOG;
  return (char*)"";
}

float WTJoystick::getGain(int Effect_Number,
              int Joystick_Number){
  APILOG;
  return 0;
}

int WTJoystick::getSpecialFlags(int Joystick_Number){
  APILOG;
  return 0;
}

void WTJoystick::loadEffectsFromFile(WTFile* Effects_File,
                         int Joystick_Number){
  APILOG;
}

void WTJoystick::setGain(float Gain,
             int Effect_Number,
             int Joystick_Number){
  APILOG;
}

void WTJoystick::startEffect(int Effect_Number,
                 int Joystick_Number){
  APILOG;
}

int WTJoystick::startEffectOnButton(int Effect_Number,
                        int Button_Number,
                        int Repeat_Interval,
                        int Joystick_Number){
  APILOG;
  return 0;
}

void WTJoystick::stopEffect(int Effect_Number,
                int Joystick_Number){
  APILOG;
}

void WTJoystick::stopEffectOnButton(int Effect_Number,
                        int Button_Number,
                        int Joystick_Number){
  APILOG;
}
