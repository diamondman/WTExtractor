#pragma once

#include <iostream>
#include "IUnknown.hpp"

class WTEvent;

class InternalCallbackWrapper : public IUnknown {

public:
  InternalCallbackWrapper();

  virtual ~InternalCallbackWrapper();

  virtual void run(WTEvent *event);

  virtual unsigned long AddRef();
  virtual unsigned long Release();

  static int nextnum;
  int num;
};
