#include "IUnknown.hpp"
#include <iostream>

IUnknown::IUnknown() :
  refcount(0) {
}

IUnknown::~IUnknown() {}

unsigned long IUnknown::AddRef (){
  ulong oldval = this->refcount.fetch_add(1, std::memory_order_relaxed);
  std::cout << "                Adding a ref! At " << (oldval + 1) << "; "
            << std::hex << static_cast<void*>(this) << std::endl;
  return oldval;
}

unsigned long IUnknown::Release(){
  ulong oldval = this->refcount.fetch_sub(1, std::memory_order_relaxed);
  std::cout << "                Killing a ref! At " << (oldval - 1) << "; "
            << std::hex << static_cast<void*>(this);
  if(oldval - 1 == 0){
    std::cout << " Deleting!";
    delete this;
  }
  std::cout << std::endl;
  return oldval;
}

unsigned long IUnknown::GetRefCount() {
  return this->refcount.load();
}
