#include "basetypes.hpp"
#include "WTEvent.hpp"
#include "WTObject.hpp"

#include <chrono>

int WTEvent::getType(){
  APILOG;
  return _Type;
}

int WTEvent::getTime(){
  APILOG;
  using namespace std::chrono;
  int ms = (int)(duration_cast< milliseconds >
                 (system_clock::now().time_since_epoch()).count());
  std::cout << "  Ret " << std::dec << ms << " ms;" << std::endl;
  return ms;
}

int WTEvent::getInterval(){
  APILOG;
  return 90;
}

//[id(0x0000138b), hidden]
int WTEvent::getId(){
  APILOG;
  return 0;
}

int WTEvent::getWTX(){
  APILOG;
  return _WTX;
}

int WTEvent::getWTY(){
  APILOG;
  return _WTY;
}

int WTEvent::getX(){
  APILOG;
  return _X;
}

int WTEvent::getY(){
  APILOG;
  return _Y;
}

VARIANT WTEvent::getData(){
  APILOG;
}

WTObject* WTEvent::getStage(){
  APILOG;
  return _Stage;
}

WTObject* WTEvent::getCamera(){
  APILOG;
  return _Camera;
}

WTObject* WTEvent::getObject(){
  APILOG;
  return _Object;
}

int WTEvent::getButtonState(){
  APILOG;
  return _ButtonState;
}

int WTEvent::getExceptionType(){
  APILOG;
  return _ExceptionType;
}

int WTEvent::getExceptionData(){
  APILOG;
  return _ExceptionData;
}

int WTEvent::getKey(){
  APILOG;
  return _Key;
}

int WTEvent::getKeyState(){
  APILOG;
  return _KeyState;
}

//[id(0x00001398), hidden]
void WTEvent::eventDone(){
  APILOG;
}
