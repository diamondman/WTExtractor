package wildtangent.webdriver.impl;

public class InternalRenderEventCallback extends wildtangent.webdriver.jni.InternalCallbackWrapper {

    private wildtangent.webdriver.WTEventCallback callback;

    public InternalRenderEventCallback(wildtangent.webdriver.WTEventCallback callback) {
        super();
        System.out.println("**************Creating a InternalRenderEventCallback");
        this.callback = callback;
    }

    public void run(wildtangent.webdriver.jni.WTEvent event) {
        System.out.println("**************InternalRenderEventCallback.run(): " +
                           Thread.currentThread().getName() + "; " + this);
        for (StackTraceElement ste : Thread.currentThread().getStackTrace()) {
            System.out.println("    " + ste);
        }
	wildtangent.webdriver.WTEvent adapted = new wildtangent.webdriver.impl.WTEvent(event);
        this.callback.onRenderEvent(adapted);
    }

    protected void finalize() {
        System.out.println("********* Java Finalizing an InternalRenderEventCallback!!");
        super.finalize();
    }

}
