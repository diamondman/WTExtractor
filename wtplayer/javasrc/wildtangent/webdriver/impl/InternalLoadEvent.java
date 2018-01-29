package wildtangent.webdriver.impl;

public class InternalLoadEvent extends wildtangent.webdriver.jni.InternalOnLoadCallbackWrapper {

    private wildtangent.webdriver.WTOnLoadEvent callback;

    public InternalLoadEvent(wildtangent.webdriver.WTOnLoadEvent callback) {
        super();
        System.out.println("**************Creating a InternalLoadEvent");
        this.callback = callback;
    }

    public void run(wildtangent.webdriver.jni.WTObject o) {
        System.out.println("**************InternalRenderEvent.run()");
	wildtangent.webdriver.WTObject adapted = (wildtangent.webdriver.WTObject)o;
        this.callback.onLoadComplete(adapted);
    }
}

