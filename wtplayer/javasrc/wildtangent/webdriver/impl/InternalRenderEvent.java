package wildtangent.webdriver.impl;

public class InternalRenderEvent extends wildtangent.webdriver.jni.InternalCallbackWrapper {

    private wildtangent.webdriver.WTEventCallback callback;

    public InternalRenderEvent(wildtangent.webdriver.WTEventCallback callback) {
        super();
        this.callback = callback;
    }

    public void run(wildtangent.webdriver.jni.WTEvent event) {
        System.out.println("**************InternalRenderEvent.run()");
	wildtangent.webdriver.WTEvent adapted = new wildtangent.webdriver.impl.WTEvent(event);
        this.callback.onRenderEvent(adapted);
    }
}

