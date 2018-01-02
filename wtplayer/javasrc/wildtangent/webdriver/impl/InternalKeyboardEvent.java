package wildtangent.webdriver.impl;

public class InternalKeyboardEvent extends wildtangent.webdriver.jni.InternalCallbackWrapper {

    private wildtangent.webdriver.WTEventCallback callback;

    public InternalKeyboardEvent(wildtangent.webdriver.WTEventCallback callback) {
        super();
        this.callback = callback;
    }

    public void run(WTEvent event) {
        System.out.println("**************InternalKeyboardEvent.run()");
        this.callback.onKeyboardEvent(event);
    }
}

