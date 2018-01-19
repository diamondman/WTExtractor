package wildtangent.webdriver.impl;

public class WTString3D extends wildtangent.webdriver.jni.WTString3D
    implements wildtangent.webdriver.WTString3D {

    public WTString3D(long cPtr, boolean cMemoryOwn) {
        super(cPtr, cMemoryOwn);
    }

    public WTString3D() {
        super();
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
        System.out.println("calling JAVA WTAPI {void WTString3D.setOnLoad(WTOnLoadEvent)}");
        this.setOnLoad(new InternalLoadEvent(callback));
    };

    public void setOnLoadedWithChildren(wildtangent.webdriver.WTOnLoadEvent callback){
        System.out.println("calling JAVA WTAPI {void WTString3D.setOnLoadedWithChildren(WTOnLoadEvent)}");
        this.setOnLoadedWithChildren(new InternalLoadEvent(callback));
    };

}
