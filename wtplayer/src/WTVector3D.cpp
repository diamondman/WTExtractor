#include "basetypes.hpp"
#include "WTVector3D.hpp"

WTVector3D::WTVector3D() :
  x(0), y(0), z(0) {
}

WTVector3D::WTVector3D(float x,
                       float y,
                       float z) :
  x(x), y(y), z(z) {
}

float WTVector3D::getY(){
  APILOG;
  return this->y;
}

void WTVector3D::setY(float y){
  APILOG;
  this->y = y;
}

float WTVector3D::getZ(){
  APILOG;
  return this->z;
}

void WTVector3D::setZ(float z){
  APILOG;
  this->z = z;
}

float WTVector3D::getX(){
  APILOG;
  return this->x;
}

void WTVector3D::setX(float x){
  APILOG;
  this->x = x;
}
