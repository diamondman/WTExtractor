package wildtangent.webdriver.impl;

public class InternalMouseEvent extends wildtangent.webdriver.jni.InternalCallbackWrapper {

    private wildtangent.webdriver.WTEventCallback callback;

    public InternalMouseEvent(wildtangent.webdriver.WTEventCallback callback) {
        super();
        this.callback = callback;
    }

    public void run(WTEvent event) {
        System.out.println("**************InternalMouseEvent.run()");
        this.callback.onMouseEvent(event);
    }
}

