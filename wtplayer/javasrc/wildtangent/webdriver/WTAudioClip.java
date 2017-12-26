package wildtangent.webdriver;

import wildtangent.webdriver.WTObject;

public interface WTAudioClip
extends WTObject {
    public void stop();

    public int getVolume();

    public void setVolume(int var1);

    public int getPlaybackPosition();

    public int getPan();

    public void setPan(int var1);

    public boolean isPlaying();

    public int getFrequency();

    public void setFrequency(int var1);

    public int getPlaybackLength();

    public void start(int var1, int var2);

    public void start(int var1);

    public void start();

    public void start(boolean var1, boolean var2);

    public void start(boolean var1);

    public float getPlaybackRate();

    public void setPlaybackRate(float var1);

    public boolean getIsPlaying();
}

