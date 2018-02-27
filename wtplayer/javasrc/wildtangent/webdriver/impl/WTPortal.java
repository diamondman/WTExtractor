package wildtangent.webdriver.impl;

public class WTPortal extends wildtangent.webdriver.jni.WTPortal
    implements wildtangent.webdriver.WTPortal {

    public WTPortal(long cPtr, boolean cMemoryOwn) {
        super(cPtr, cMemoryOwn);
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
        System.out.println("calling JAVA WTAPI {void WTPortal.setOnLoad(WTOnLoadEvent)}");
        callback.onLoadComplete(this);
        this.setOnLoad(new InternalLoadEvent(callback));
    };

    public void setOnLoadedWithChildren(wildtangent.webdriver.WTOnLoadEvent callback){
        System.out.println("calling JAVA WTAPI {void WTPortal.setOnLoadedWithChildren(WTOnLoadEvent)}");
        callback.onLoadComplete(this);
        this.setOnLoadedWithChildren(new InternalLoadEvent(callback));
    };

}

