#pragma once

#include <iostream>

class WTObject;

class InternalOnLoadCallbackWrapper {

public:
  virtual ~InternalOnLoadCallbackWrapper() {
    std::cout << "****InternalOnLoadCallbackWrapper::~InternalOnLoadCallbackWrapper()" << std::endl;
  }

  virtual void run(WTObject *o) {
    std::cout << "****InternalOnLoadCallbackWrapper::run()" << std::endl;
  }

};
