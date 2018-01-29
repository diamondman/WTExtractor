#include "InternalCallbackWrapper.hpp"

InternalCallbackWrapper::InternalCallbackWrapper() :
  IUnknown() {
  num = nextnum;
  nextnum++;
}

InternalCallbackWrapper::~InternalCallbackWrapper() {
  std::cout << "****InternalCallbackWrapper::~InternalCallbackWrapper()" << "; "
            << std::hex << static_cast<void*>(this) << std::endl;
}

void InternalCallbackWrapper::run(WTEvent *event) {
  std::cout << "****InternalCallbackWrapper::run()" << "; "
            << std::hex << static_cast<void*>(this) << std::endl;
}

unsigned long InternalCallbackWrapper::AddRef (){
  std::cout << "InternalCallbackWrapper " << num;
  return IUnknown::AddRef();
}

unsigned long InternalCallbackWrapper::Release(){
  std::cout << "InternalCallbackWrapper " << num;
  return IUnknown::Release();
}

int InternalCallbackWrapper::nextnum = 1;
