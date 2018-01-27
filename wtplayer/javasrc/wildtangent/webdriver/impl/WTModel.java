package wildtangent.webdriver.impl;

public class WTModel extends wildtangent.webdriver.jni.WTModel
    implements wildtangent.webdriver.WTModel {

    public WTModel(long cPtr, boolean cMemoryOwn) {
        super(cPtr, cMemoryOwn);
    }


    public void setFaceColor(int n, int n2, int n3, int n4, int n5) {
        this.setFaceColor(n, (byte)n2, (byte)n3, (byte)n4, (byte)n5);
    }

    public void setFaceColor(int n, int n2, int n3, int n4) {
        this.setFaceColor(n, (byte)n2, (byte)n3, (byte)n4, -1);
    }


    public void setPatchPtColor(int n, int n2, int n3, int n4, int n5, int n6, String string) {
        this.setPatchPtColor(n, n2, (byte)n3, (byte)n4, (byte)n5, (byte)n6, string);
    }

    public void setPatchPtColor(int n, int n2, int n3, int n4, int n5, int n6) {
        this.setPatchPtColor(n, n2, (byte)n3, (byte)n4, (byte)n5, (byte)n6, "/");
    }


    public void setVertexColor(int n, int n2, int n3, int n4, int n5) {
        this.setVertexColor(n, (byte)n2, (byte)n3, (byte)n4, (byte)n5);
    }

    public void setVertexColor(int n, int n2, int n3, int n4) {
        this.setVertexColor(n, (byte)n2, (byte)n3, (byte)n4, -1);
    }


    public void setPatchTileColor(int n, int n2, int n3, int n4, int n5, int n6, String string) {
        this.setPatchTileColor(n, n2, (byte)n3, (byte)n4, (byte)n5, (byte)n6, string);
    }

    public void setPatchTileColor(int n, int n2, int n3, int n4, int n5, int n6) {
        this.setPatchTileColor(n, n2, (byte)n3, (byte)n4, (byte)n5, (byte)n6, "/");
    }


    public void setOption(int n, Object object) {
        //this.internal_setOption(n, object);
        //this.setOption_xfer(n, object);
    }

    public void setOption(int n, boolean bl) {
        this.setOption(n, new Boolean(bl));
    }

    public void setOption(int n, double d) {
        this.setOption(n, new Double(d));
    }

    public void setOption(int n, float f) {
        this.setOption(n, new Float(f));
    }

    public void setOption(int n, int n2) {
        this.setOption(n, new Integer(n2));
    }

    public void setOnLoad(wildtangent.webdriver.WTOnLoadEvent callback){
        System.out.println("calling JAVA WTAPI {void WTModel.setOnLoad(WTOnLoadEvent)}");
        this.setOnLoad(new InternalLoadEvent(callback));
    };

    public void setOnLoadedWithChildren(wildtangent.webdriver.WTOnLoadEvent callback){
        System.out.println("calling JAVA WTAPI {void WTModel.setOnLoadedWithChildren(WTOnLoadEvent)}");
        this.setOnLoadedWithChildren(new InternalLoadEvent(callback));
    };

}
