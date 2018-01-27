#include <atomic>

class IUnknown {
public:

  IUnknown() : refcount(0){}
  virtual ~IUnknown();

  virtual unsigned long AddRef();
  virtual unsigned long Release();

private:
  std::atomic_ulong refcount;
};
