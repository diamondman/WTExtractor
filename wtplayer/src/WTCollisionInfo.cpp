#include "WTCollisionInfo.hpp"
#include "WTObject.hpp"
#include "WTVector3D.hpp"

WTObject* WTCollisionInfo::getHitObject(){
  return 0;
}

WTObject* WTCollisionInfo::getAttachedObject(){
  return 0;
}

WTVector3D* WTCollisionInfo::getNewPosition(){
  return 0;
}

WTVector3D* WTCollisionInfo::getImpactNormal(){
  return 0;
}

float WTCollisionInfo::getImpactDistance(){
  return 0;
}
