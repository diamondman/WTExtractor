package wildtangent.webdriver.impl;

public class WTFile extends wildtangent.webdriver.jni.WTFile
    implements wildtangent.webdriver.WTFile {

    public WTFile(long cPtr, boolean cMemoryOwn) {
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
        System.out.println("calling JAVA WTAPI {void WTFile.setOnLoad(WTOnLoadEvent)}");
        System.out.println(">>>> Starting onLoad callback");
        callback.onLoadComplete(this);
        System.out.println("<<<< Ending onLoad callback");
        this.setOnLoad(new InternalLoadEvent(callback));
    };

    public void setOnLoadedWithChildren(wildtangent.webdriver.WTOnLoadEvent callback){
        System.out.println("calling JAVA WTAPI {void WTFile.setOnLoadedWithChildren(WTOnLoadEvent)}");
        System.out.println(">>>> Starting onLoad callback");
        callback.onLoadComplete(this);
        System.out.println("<<<< Ending onLoad callback");
        this.setOnLoadedWithChildren(new InternalLoadEvent(callback));
    };

    public void close() {
        System.out.println("*************************************FILE CLOSING*************************");
        for (StackTraceElement ste : Thread.currentThread().getStackTrace()) {
            System.out.println("  "+ste);
        }
        super.close();
    }
}

