package netscape.javascript;

import java.applet.Applet;

public class JSObject{
    public Object eval(String s){
        System.out.printf("Javascript Call: {%s}\n", s);
        return null;
    }

    public static JSObject getWindow(Applet applet){
        return new JSObject();
    }
}
