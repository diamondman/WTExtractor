package wildtangent.webdriver;

import wildtangent.webdriver.WTContainer;
import wildtangent.webdriver.WTObject;

public interface WTGroup
extends WTContainer {
    public boolean getLightingStatus();

    public void removeObject(WTContainer var1);

    public WTObject getChildByIndex(int var1);

    public WTObject getObjectByName(String var1, int var2);

    public WTObject getObjectByName(String var1);

    public int addObject(WTContainer var1);

    public int getChildCount();
}

