package wildtangent.webdriver;

public interface WTJoystick {
    public int getButtonStateEvent();

    public int getAxisStateEvent();

    public int getPositionEvent(int var1);

    public String getHardwareName(int var1);

    public String getHardwareName();

    public void setPositionRange(int var1, int var2);

    public void setPositionRange(int var1);

    public int getPositionRange(int var1);

    public int getPositionRange();

    public int getPOVState(int var1, int var2);

    public int getPOVState(int var1);

    public int getEffectCount(int var1);

    public int getEffectCount();

    public float getGain(int var1, int var2);

    public float getGain(int var1);

    public void setGain(float var1, int var2, int var3);

    public void setGain(float var1, int var2);

    public void setOnEvent(WTEventJoystickCallback var1);

    public void loadEffectsFromFile(WTFile var1, int var2);

    public void loadEffectsFromFile(WTFile var1);

    public int getAxisFlags(int var1);

    public int getAxisFlags();

    public void startEffect(int var1, int var2);

    public void startEffect(int var1);

    public int startEffectOnButton(int var1, int var2, int var3, int var4);

    public int startEffectOnButton(int var1, int var2, int var3);

    public void stopEffect(int var1, int var2);

    public int getButtonCount(int var1);

    public int getButtonCount();

    public void reset(int var1);

    public void reset();

    public void stopEffect(int var1);

    public int getPOVCount(int var1);

    public int getPOVCount();

    public int getButtonState(int var1);

    public int getButtonState();

    public int getPOVStateEvent(int var1);

    public void stopEffectOnButton(int var1, int var2, int var3);

    public void stopEffectOnButton(int var1, int var2);

    public int getEffectByName(String var1, int var2);

    public void setSensitivity(int var1, int var2);

    public void setSensitivity(int var1);

    public void setSensitivity();

    public int getSensitivity(int var1);

    public int getSensitivity();

    public void setDeadZone(int var1, int var2);

    public void setDeadZone(int var1);

    public void setDeadZone();

    public int getDeadZone(int var1);

    public int getDeadZone();

    public int getEffectByName(String var1);

    public String getEffectName(int var1, int var2);

    public String getEffectName(int var1);

    public int getPosition(int var1, int var2);

    public int getPosition(int var1);

    public int getEventJoystick();

    public int getCount();

    public boolean setNotifyEvent(boolean var1, int var2);

    public boolean setNotifyEvent(boolean var1);

    public boolean getNotifyEvent(int var1);

    public boolean getNotifyEvent();

    public int getSpecialFlags(int var1);

    public int getSpecialFlags();

    public int getEventTime();
}

