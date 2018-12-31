package wildtangent.webdriver.impl;

public class InternalMouseEventCallback extends wildtangent.webdriver.jni.InternalCallbackWrapper {

    private wildtangent.webdriver.WTEventCallback callback;

    public InternalMouseEventCallback(wildtangent.webdriver.WTEventCallback callback) {
        super();
        System.out.println("**************Creating a InternalMouseEventCallback");
        this.callback = callback;
    }

    public void run(wildtangent.webdriver.jni.WTEvent event) {
        System.out.println("**************InternalMouseEventCallback.run()");
	wildtangent.webdriver.WTEvent adapted = new wildtangent.webdriver.impl.WTEvent(event);
        this.callback.onMouseEvent(adapted);
    }

    protected void finalize() {
        System.out.println("********* Java Finalizing an InternalMouseEventCallback!!");
        super.finalize();
    }

}

