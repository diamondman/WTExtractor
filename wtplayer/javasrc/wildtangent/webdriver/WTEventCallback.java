package wildtangent.webdriver;

import wildtangent.webdriver.WTEvent;

public interface WTEventCallback {
    public void onExceptionEvent(WTEvent var1);

    public void onKeyboardEvent(WTEvent var1);

    public void onRenderEvent(WTEvent var1);

    public void onMouseEvent(WTEvent var1);
}

