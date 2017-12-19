#pragma once

class WTEvent;

class WTEventCallback {

public:
  virtual void WTMouseEvent(WTEvent* pWTEventObj) = 0;

  virtual void WTRenderEvent(WTEvent* pWTEventObj) = 0;

  virtual void WTKeyboardEvent(WTEvent* pWTEventObj) = 0;

  virtual void WTExceptionEvent(WTEvent* pWTEventObj) = 0;

  virtual void WTJoystickEvent(WTEvent* pWTEventObj) = 0;
};
