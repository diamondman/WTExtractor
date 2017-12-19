#pragma once

class WTMousePollInfo {

public:
  int getMickeyX();

  int getMickeyY();

  int getMickeyZ();

  int getPixelX(int origin = 0);

  int getPixelY(int origin = 0);

  int getButtons();
};
