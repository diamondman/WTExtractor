package wildtangent.webdriver.impl;

public class WTFont extends wildtangent.webdriver.jni.WTFont
    implements wildtangent.webdriver.WTFont {

    public WTFont(long cPtr, boolean cMemoryOwn) {
        super(cPtr, cMemoryOwn);
    }


    public void setTextColor(int n, int n2, int n3) {
        this.setTextColor((byte)n, (byte)n2, (byte)n3);
    }

    public void setTextBkColor(int n, int n2, int n3) {
        this.setTextBkColor((byte)n, (byte)n2, (byte)n3);
    }

}

