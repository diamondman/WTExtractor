package wildtangent.webdriver;

import wildtangent.webdriver.WTCamera;
import wildtangent.webdriver.WTGroup;

public interface WTAudioClip3D
extends WTGroup {
    public void setPlaybackRateScale(float var1);

    public void stop();

    public float getMinDistance();

    public void setMinDistance(float var1);

    public void removeCamera();

    public int getVolumeScale();

    public void setVolumeScale(int var1);

    public float getDoppler();

    public void setDoppler(float var1);

    public float getMaxDistance();

    public void setMaxDistance(float var1);

    public int getPlaybackPosition();

    public boolean isPlaying();

    public int getPlaybackLength();

    public void start(int var1, int var2);

    public void start(int var1);

    public void start();

    public WTCamera getCamera();

    public void setCamera(WTCamera var1);

    public void setCamera();

    public float getPlaybackRateScale();
}

