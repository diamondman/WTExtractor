#include "InternalCallbackWrapper.hpp"

InternalCallbackWrapper::InternalCallbackWrapper() {
  num = nextnum++;
}

InternalCallbackWrapper::~InternalCallbackWrapper() {
  std::cout << "****InternalCallbackWrapper::~InternalCallbackWrapper()" << "; "
            << std::hex << static_cast<void*>(this) << std::endl;
}

void InternalCallbackWrapper::run(WTEvent *event) {
  std::cout << "****InternalCallbackWrapper::run()" << "; "
            << std::hex << static_cast<void*>(this)
            << "; " << std::dec << this->num << std::endl;
}

int InternalCallbackWrapper::nextnum = 1;
