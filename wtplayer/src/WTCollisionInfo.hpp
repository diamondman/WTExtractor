#pragma once

class WTObject;
class WTVector3D;

class WTCollisionInfo {

public:
  WTObject* getHitObject();

  WTObject* getAttachedObject();

  WTVector3D* getNewPosition();

  WTVector3D* getImpactNormal();

  float getImpactDistance();
};
