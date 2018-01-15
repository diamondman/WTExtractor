#pragma once

class WTVector3D {

public:
  WTVector3D();

  float getY();

  void setY(float y);

  float getZ();

  void setZ(float z);

  float getX();

  void setX(float x);

private:
  float x, y, z;
};
