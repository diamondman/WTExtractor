package wildtangent.webdriver.impl;

public class InternalExceptionEvent extends wildtangent.webdriver.jni.InternalCallbackWrapper {

    private wildtangent.webdriver.WTEventCallback callback;

    public InternalExceptionEvent(wildtangent.webdriver.WTEventCallback callback) {
        super();
        System.out.println("**************Creating a InternalExceptionEvent");
        this.callback = callback;
    }

    public void run(wildtangent.webdriver.jni.WTEvent event) {
        System.out.println("**************InternalExceptionEvent.run()");
        wildtangent.webdriver.WTEvent adapted = new wildtangent.webdriver.impl.WTEvent(event);
        this.callback.onExceptionEvent(adapted);
    }

    protected void finalize() {
        System.out.println("********* Java Finalizing an InternalExceptionEvent!!");
        super.finalize();
    }

}

