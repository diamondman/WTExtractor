#include "WTEvent.hpp"

#include <chrono>

int WTEvent::getTime(){
  APILOG;
  using namespace std::chrono;
  int ms = (int)(duration_cast< milliseconds >
                 (system_clock::now().time_since_epoch()).count());
  std::cout << "  Ret " << std::dec << ms << " ms;" << std::endl;
  return ms;
}

int WTEvent::getInterval(){
  APILOG;
  return 90;
}
