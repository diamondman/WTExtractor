package wildtangent.webdriver.impl;

public class WTBitmap extends wildtangent.webdriver.jni.WTBitmap
    implements wildtangent.webdriver.WTBitmap {

    public WTBitmap(long cPtr, boolean cMemoryOwn) {
        super(cPtr, cMemoryOwn);
    }

    public void setTextColor(int n, int n2, int n3) {
        this.setTextColor((byte)n, (byte)n2, (byte)n3);
    }

    public void setDrawColor(int n, int n2, int n3) {
        this.setDrawColor((byte)n, (byte)n2, (byte)n3);
    }

    public void setTextBkColor(int n, int n2, int n3) {
        this.setTextBkColor((byte)n, (byte)n2, (byte)n3);
    }

    public void setColorKey(int n, int n2, int n3) {
        this.setColorKey((byte)n, (byte)n2, (byte)n3);
    }

    public void setColor(int n, int n2, int n3) {
        this.setColor((byte)n, (byte)n2, (byte)n3);
    }


    public void setOption(int n, Object object) {
        //this.internal_setOption(n, object);
        //this.setOption_xfer(n, object);
    }

    public void setOption(int n, boolean bl) {
        this.setOption(n, new Boolean(bl));
    }

    public void setOption(int n, double d) {
        this.setOption(n, new Double(d));
    }

    public void setOption(int n, float f) {
        this.setOption(n, new Float(f));
    }

    public void setOption(int n, int n2) {
        this.setOption(n, new Integer(n2));
    }

    public void setOnLoad(wildtangent.webdriver.WTOnLoadEvent callback){
        System.out.println("calling JAVA WTAPI {void WTBitmap.setOnLoad(WTOnLoadEvent)}");
        callback.onLoadComplete(this);
        this.setOnLoad(new InternalLoadEvent(callback));
    };

    public void setOnLoadedWithChildren(wildtangent.webdriver.WTOnLoadEvent callback){
        System.out.println("calling JAVA WTAPI {void WTBitmap.setOnLoadedWithChildren(WTOnLoadEvent)}");
        callback.onLoadComplete(this);
        this.setOnLoadedWithChildren(new InternalLoadEvent(callback));
    };

}
