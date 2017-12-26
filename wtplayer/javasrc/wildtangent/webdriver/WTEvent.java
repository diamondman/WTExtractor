package wildtangent.webdriver;

import wildtangent.webdriver.WTObject;

public interface WTEvent {
    public int getId();

    public int getExceptionData();

    public int getWTX();

    public int getX();

    public int getButtonState();

    public int getTime();

    public int getExceptionType();

    public WTObject getStage();

    public int getKeyState();

    public int getInterval();

    public int getWTY();

    public int getY();

    public int getType();

    public int getKey();

    public WTObject getCamera();

    public WTObject getObject();
}

