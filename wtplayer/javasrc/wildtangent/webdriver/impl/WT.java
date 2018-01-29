package wildtangent.webdriver.impl;

public class WT extends wildtangent.webdriver.jni.WT
    implements wildtangent.webdriver.WT {

    public WT(long cPtr, boolean cMemoryOwn) {
        super(cPtr, cMemoryOwn);
    }

    public WT(String localver_path) {
        super(localver_path);
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


    private InternalKeyboardEvent keyboardEvent;
    private InternalRenderEvent renderEvent;
    private InternalMouseEvent mouseEvent;
    private InternalExceptionEvent exceptionEvent;

    public void setOnKeyboardEvent(wildtangent.webdriver.WTEventCallback callback){
        System.out.println("calling JAVA WTAPI {void WT.setOnKeyboardEvent(WTEventCallback)}");
        //InternalKeyboardEvent keyboardEvent = new InternalKeyboardEvent(callback);
        keyboardEvent = new InternalKeyboardEvent(callback);
        this.setOnKeyboardEvent(keyboardEvent);
    };

    public void setOnRenderEvent(wildtangent.webdriver.WTEventCallback callback){
        System.out.println("calling JAVA WTAPI {void WT.setOnRenderEvent(WTEventCallback)}");
        for (StackTraceElement ste : Thread.currentThread().getStackTrace()) {
            System.out.println("    " + ste);
        }
        //InternalRenderEvent renderEvent = new InternalRenderEvent(callback);
        renderEvent = new InternalRenderEvent(callback);
        this.setOnRenderEvent(renderEvent);
    };

    public void setOnMouseEvent(wildtangent.webdriver.WTEventCallback callback){
        System.out.println("calling JAVA WTAPI {void WT.setOnMouseEvent(WTEventCallback)}");
        //InternalMouseEvent mouseEvent = new InternalMouseEvent(callback);
        mouseEvent = new InternalMouseEvent(callback);
        this.setOnMouseEvent(mouseEvent);
    };

    public void setOnExceptionEvent(wildtangent.webdriver.WTEventCallback callback){
        System.out.println("calling JAVA WTAPI {void WT.setOnExceptionEvent(WTEventCallback)}");
        //InternalExceptionEvent exceptionEvent = new InternalExceptionEvent(callback);
        exceptionEvent = new InternalExceptionEvent(callback);
        this.setOnExceptionEvent(exceptionEvent);
    };

}
