#pragma once

#include <list>

class WTDrop;

class container_WTDrop {
public:
  virtual void _moveDropToFront(WTDrop* drop) = 0;

  void removeDrop(WTDrop* Drop_To_Remove);
};
