#pragma once

class WTKeyboardPollInfo {

public:
  int getNextKeyDown();

  int isKeyDown(int key);
};
