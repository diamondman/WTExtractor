package wildtangent.webdriver.impl;

public class WT extends wildtangent.webdriver.jni.WT
    implements wildtangent.webdriver.WT {

    public WT(long cPtr, boolean cMemoryOwn) {
        super(cPtr, cMemoryOwn);
    }

    public WT(String localver_path, int width, int height) {
        super(localver_path, width, height);
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


    private InternalKeyboardEventCallback keyboardEvent;
    private InternalRenderEventCallback renderEvent;
    private InternalMouseEventCallback mouseEvent;
    private InternalExceptionEventCallback exceptionEvent;

    public void setOnKeyboardEvent(wildtangent.webdriver.WTEventCallback callback){
        System.out.println("calling JAVA WTAPI {void WT.setOnKeyboardEvent(WTEventCallback)}");
        //InternalKeyboardEventCallback keyboardEvent = new InternalKeyboardEventCallback(callback);
        keyboardEvent = new InternalKeyboardEventCallback(callback);
        this.setOnKeyboardEvent(keyboardEvent);
    };

    public void setOnRenderEvent(wildtangent.webdriver.WTEventCallback callback){
        System.out.println("calling JAVA WTAPI {void WT.setOnRenderEvent(WTEventCallback)}");
        for (StackTraceElement ste : Thread.currentThread().getStackTrace()) {
            System.out.println("    " + ste);
        }
        //InternalRenderEventCallback renderEvent = new InternalRenderEventCallback(callback);
        renderEvent = new InternalRenderEventCallback(callback);
        this.setOnRenderEvent(renderEvent);
    };

    public void setOnMouseEvent(wildtangent.webdriver.WTEventCallback callback){
        System.out.println("calling JAVA WTAPI {void WT.setOnMouseEvent(WTEventCallback)}");
        //InternalMouseEventCallback mouseEvent = new InternalMouseEventCallback(callback);
        mouseEvent = new InternalMouseEventCallback(callback);
        this.setOnMouseEvent(mouseEvent);
    };

    public void setOnExceptionEvent(wildtangent.webdriver.WTEventCallback callback){
        System.out.println("calling JAVA WTAPI {void WT.setOnExceptionEvent(WTEventCallback)}");
        //InternalExceptionEventCallback exceptionEvent = new InternalExceptionEventCallback(callback);
        exceptionEvent = new InternalExceptionEventCallback(callback);
        this.setOnExceptionEvent(exceptionEvent);
    };

}
