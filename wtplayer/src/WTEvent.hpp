#pragma once

#include "basetypes.hpp"

class WTObject;

#define WTEVENT_RENDEREVENT               0 //The event is a render event.
#define WTEVENT_MOUSEEVENT                1 //Unknown mouse event.
#define WTEVENT_MOUSEMOVEEVENT            2 //The mouse moved.
#define WTEVENT_MOUSELEFTDBLCLICKEVENT    5 //The left button was double-clicked.
#define WTEVENT_MOUSELEFTBUTTONDOWN       6 //The left mouse button was pressed.
#define WTEVENT_MOUSELEFTBUTTONUP         7 //The left mouse button was released.
#define WTEVENT_MOUSERIGHTDBLCLICKEVENT   8 //The right button was double-clicked.
#define WTEVENT_MOUSERIGHTBUTTONDOWN      9 //The right mouse button was pressed.
#define WTEVENT_MOUSERIGHTBUTTONUP       10 //The right mouse button was released.
#define WTEVENT_MOUSEMIDDLEDBLCLICKEVENT 11 //The middle button was double-clicked.
#define WTEVENT_MOUSEMIDDLEBUTTONDOWN    12 //The middle mouse button was pressed.
#define WTEVENT_MOUSEMIDDLEBUTTONUP      13 //The middle mouse button was released.
#define WTEVENT_KEYBOARDEVENT            14 //A key was pressed or released.
#define WTEVENT_EXCEPTIONEVENT           15 //An exception event has occurred.

#define BTNSTATE_LEFT   1  //Left mouse button is pressed.
#define BTNSTATE_RIGHT  2  //Right mouse button is pressed.
#define BTNSTATE_SHIFT  4  //Shift key is pressed.
#define BTNSTATE_CTRL   8  //Control key is pressed.
#define BTNSTATE_MIDDLE 16 //Middle mouse button is pressed.

#define KEY_RELEASE 0
#define KEY_PRESS   1

class WTEvent {

public:
  WTEvent(int type=WTEVENT_EXCEPTIONEVENT, int interval=0);

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
