#pragma once

#include <iostream>

#include "IUnknown.hpp"

class WTEvent;

class InternalCallbackWrapper {

public:
  InternalCallbackWrapper();

  virtual ~InternalCallbackWrapper();

  virtual void run(WTEvent *event);

  static int nextnum;
  int num;
};
