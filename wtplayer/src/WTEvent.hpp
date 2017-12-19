#pragma once

#include "basetypes.hpp"

class WTObject;

class WTEvent {

public:
  int getType();

  int getTime();

  int getInterval();

  //[id(0x0000138b), hidden]
  int getId();

  int getWTX();

  int getWTY();

  int getX();

  int getY();

  VARIANT getData();

  WTObject* getStage();

  WTObject* getCamera();

  WTObject* getObject();

  int getButtonState();

  int getExceptionType();

  int getExceptionData();

  int getKey();

  int getKeyState();

  //[id(0x00001398), hidden]
  void eventDone();
};
