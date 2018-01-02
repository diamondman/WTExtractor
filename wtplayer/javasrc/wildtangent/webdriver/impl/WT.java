package wildtangent.webdriver.impl;

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


    public void setOnKeyboardEvent(wildtangent.webdriver.WTEventCallback callback){
        System.out.println("calling JAVA WTAPI {void WT.setOnKeyboardEvent(WTEventCallback)}");
        this.setOnKeyboardEvent(new InternalKeyboardEvent(callback));
    };

    public void setOnRenderEvent(wildtangent.webdriver.WTEventCallback callback){
        System.out.println("calling JAVA WTAPI {void WT.setOnRenderEvent(WTEventCallback)}");
        this.setOnRenderEvent(new InternalRenderEvent(callback));
    };

    public void setOnMouseEvent(wildtangent.webdriver.WTEventCallback callback){
        System.out.println("calling JAVA WTAPI {void WT.setOnMouseEvent(WTEventCallback)}");
        this.setOnMouseEvent(new InternalMouseEvent(callback));
    };

    public void setOnExceptionEvent(wildtangent.webdriver.WTEventCallback callback){
        System.out.println("calling JAVA WTAPI {void WT.setOnExceptionEvent(WTEventCallback)}");
        this.setOnExceptionEvent(new InternalExceptionEvent(callback));
    };

}
