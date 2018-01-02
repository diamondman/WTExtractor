#pragma once

#include <iostream>

class WTEvent;

class InternalCallbackWrapper {

public:
  virtual ~InternalCallbackWrapper() {
    std::cout << "****InternalCallbackWrapper::~InternalCallbackWrapper()" << std::endl;
  }

  virtual void run(WTEvent *event) {
    std::cout << "****InternalCallbackWrapper::run()" << std::endl;
  }

};
