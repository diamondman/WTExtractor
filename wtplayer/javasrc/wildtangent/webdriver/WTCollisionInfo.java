package wildtangent.webdriver;

import wildtangent.webdriver.WTObject;
import wildtangent.webdriver.WTVector3D;

public interface WTCollisionInfo {
    public WTObject getAttachedObject();

    public WTVector3D getNewPosition();

    public float getImpactDistance();

    public WTVector3D getImpactNormal();

    public WTObject getHitObject();
}

