package wildtangent.webdriver;

public interface WTObject {
    public WTObject getOwner();

    public boolean isLoadedWithChildren();

    public boolean isValid();

    public void setOnLoad(WTOnLoadEvent var1);

    public boolean getIsValid();

    public int getObjectType();

    public Object getOption(int var1);

    public void setOption(int var1, Object var2);

    public void setOption(int var1, boolean var2);

    public void setOption(int var1, double var2);

    public void setOption(int var1, float var2);

    public void setOption(int var1, int var2);

    //public WTObject duplicate();

    public boolean isLoaded();

    public WT getCreator();

    public void setOnLoadedWithChildren(WTOnLoadEvent var1);

    public int getErrorNumber();

    public void setErrorNumber(int var1);

    public String getName();

    public void setName(String var1);

    public void setUserData(Object var1);

    public Object getUserData();

    public boolean getIsLoaded();
}
