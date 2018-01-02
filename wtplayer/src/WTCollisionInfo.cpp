#include "basetypes.hpp"
#include "WTCollisionInfo.hpp"
#include "WTObject.hpp"
#include "WTVector3D.hpp"

WTObject* WTCollisionInfo::getHitObject(){
  APILOG;
  return 0;
}

WTObject* WTCollisionInfo::getAttachedObject(){
  APILOG;
  return 0;
}

WTVector3D* WTCollisionInfo::getNewPosition(){
  APILOG;
  return 0;
}

WTVector3D* WTCollisionInfo::getImpactNormal(){
  APILOG;
  return 0;
}

float WTCollisionInfo::getImpactDistance(){
  APILOG;
  return 0;
}
