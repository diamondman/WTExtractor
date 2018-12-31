package wildtangent.webdriver.impl;

public class InternalKeyboardEventCallback extends wildtangent.webdriver.jni.InternalCallbackWrapper {

    private wildtangent.webdriver.WTEventCallback callback;

    public InternalKeyboardEventCallback(wildtangent.webdriver.WTEventCallback callback) {
        super();
        System.out.println("**************Creating a InternalKeyboardEventCallback");
        this.callback = callback;
    }

    public void run(wildtangent.webdriver.jni.WTEvent event) {
        System.out.println("**************InternalKeyboardEventCallback.run()");
	wildtangent.webdriver.WTEvent adapted = new wildtangent.webdriver.impl.WTEvent(event);
        this.callback.onKeyboardEvent(adapted);
    }

    protected void finalize() {
        System.out.println("********* Java Finalizing an InternalKeyboardEventCallback!!");
        super.finalize();
    }

}

