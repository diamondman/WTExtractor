package wildtangent.webdriver.impl;

public class InternalExceptionEventCallback extends wildtangent.webdriver.jni.InternalCallbackWrapper {

    private wildtangent.webdriver.WTEventCallback callback;

    public InternalExceptionEventCallback(wildtangent.webdriver.WTEventCallback callback) {
        super();
        System.out.println("**************Creating a InternalExceptionEventCallback");
        this.callback = callback;
    }

    public void run(wildtangent.webdriver.jni.WTEvent event) {
        System.out.println("**************InternalExceptionEventCallback.run()");
        wildtangent.webdriver.WTEvent adapted = new wildtangent.webdriver.impl.WTEvent(event);
        this.callback.onExceptionEvent(adapted);
    }

    protected void finalize() {
        System.out.println("********* Java Finalizing an InternalExceptionEventCallback!!");
        super.finalize();
    }

}

