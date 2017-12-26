package wildtangent.webdriver;

public interface WTVisualizer {
    public boolean updateProperties();

    public void updateData(int var1, float var2, String var3);

    public void setBinFreq(int var1, float var2);

    public float getBinFreq(int var1);

    public String getBinDataAsString(int var1, int var2);

    public int getPlaybackPosition();

    public String getInfo(int var1);

    public int getPlaybackLength();

    public void setReceiverInfo(String var1, int var2, int var3, int var4);

    public void setReceiverInfo(String var1, int var2, int var3);

    public void setReceiverInfo(String var1, int var2);

    public float getBinData(int var1);

    public void setReceiverInfo(String var1);

    public String getPropertyAsString(String var1, int var2);

    public String getPropertyAsString(String var1);
}

