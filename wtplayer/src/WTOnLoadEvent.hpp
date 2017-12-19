#pragma once

class WTObject;

class WTOnLoadEvent {
public:
  virtual void onLoadComplete(WTObject* pObject) = 0;
};
