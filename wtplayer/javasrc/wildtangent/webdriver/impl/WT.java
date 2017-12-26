package wildtangent.webdriver.impl;

//import wildtangent.webdriver.WTActor;
//import wildtangent.webdriver.WTGroup;

public class WT extends wildtangent.webdriver.jni.WT
    implements wildtangent.webdriver.WT {

    public WT(long cPtr, boolean cMemoryOwn) {
        super(cPtr, cMemoryOwn);
    }

    public WT() {
        super();
    }


    public synchronized void shutdown() {
    }

    public void focus() {
        //this.takeFocus();
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


    public void setOnKeyboardEvent(wildtangent.webdriver.WTEventCallback var1){};

    public void setOnRenderEvent(wildtangent.webdriver.WTEventCallback var1){};

    public void setOnMouseEvent(wildtangent.webdriver.WTEventCallback var1){};

    public void setOnExceptionEvent(wildtangent.webdriver.WTEventCallback var1){};

}
