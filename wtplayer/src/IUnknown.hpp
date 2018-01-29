#pragma once

#include <atomic>

class IUnknown {
public:

  IUnknown();
  virtual ~IUnknown();

  virtual unsigned long AddRef();
  virtual unsigned long Release();
  virtual unsigned long GetRefCount();

private:
  std::atomic_ulong refcount;
};
