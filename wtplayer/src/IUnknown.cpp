#include "IUnknown.hpp"
#include <iostream>

IUnknown::~IUnknown() {}

unsigned long IUnknown::AddRef (){
  std::cout << "                Adding a ref!" << std::endl;
  //throw new std::logic_error("DERP");
  return this->refcount.fetch_add(1, std::memory_order_relaxed);
}

unsigned long IUnknown::Release(){
  ulong oldval = this->refcount.fetch_sub(1, std::memory_order_relaxed);
  if(oldval - 1 == 0){
    std::cout << "Deleting an object" << std::endl;
    delete this;
  }
  return oldval;
}
