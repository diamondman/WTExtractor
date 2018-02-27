#pragma once

#include "basetypes.hpp"

class WTObject;

class WTEvent {

public:
  WTEvent(int interval=0);

  int getType(){
    APILOG;
    return _Type;
  }

  int getTime();

  int getInterval(){
    APILOG;
    return interval_;
  }

  //[id(0x0000138b), hidden]
  int getId(){
    APILOG;
    return 0;
  }

  int getWTX(){
    APILOG;
    return _WTX;
  }

  int getWTY(){
    APILOG;
    return _WTY;
  }

  int getX(){
    APILOG;
    return _X;
  }

  int getY(){
    APILOG;
    return _Y;
  }

  VARIANT getData(){
    APILOG;
    return nullptr;
  }

  WTObject* getStage(){
    APILOG;
    return _Stage;
  }

  WTObject* getCamera(){
    APILOG;
    return _Camera;
  }

  WTObject* getObject(){
    APILOG;
    return _Object;
  }

  int getButtonState(){
    APILOG;
    return _ButtonState;
  }

  int getExceptionType(){
    APILOG;
    return _ExceptionType;
  }

  int getExceptionData(){
    APILOG;
    return _ExceptionData;
  }

  int getKey(){
    APILOG;
    return _Key;
  }

  int getKeyState(){
    APILOG;
    return _KeyState;
  }

  //[id(0x00001398), hidden]
  void eventDone(){
    APILOG;
  }


  //private:
  int _Type;
  int interval_;
  int _WTX;
  int _WTY;
  int _X;
  int _Y;
  //VARIANT Data;
  WTObject* _Stage;
  WTObject* _Camera;
  WTObject* _Object;
  int _ButtonState;
  int _ExceptionType;
  int _ExceptionData;
  int _Key;
  int _KeyState;
};
