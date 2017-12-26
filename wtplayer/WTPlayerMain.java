import wildtangent.webdriver.WT;
import wildtangent.webdriver.WTVector3D;
import wildtangent.webdriver.WTObject;
import wildtangent.webdriver.wt3dLib;
import netscape.javascript.JSObject;
import com.ms.com.Variant;
import java.applet.Applet;
import java.net.URLClassLoader;
import java.net.URL;

import java.lang.reflect.Method;
import java.lang.reflect.InvocationTargetException;

public class WTPlayerMain
{

    static {
        System.loadLibrary("WTEngine");
    }

    public static void main(String[] args)
    {
        for(String arg : args)
            System.out.println("ARG: " + arg);

        //WTVector3D v = new wildtangent.webdriver.impl.WTVector3D();
        //v.setX(4.04f);
        //System.out.printf("X is %f\n", v.getX());
        //
        //WTObject wto = new wildtangent.webdriver.impl.WTObject();
        //System.out.printf("Name: %s\n", wto.getName());
        ////System.out.println(wto.getUserData());
        //
        //Object o = new String("HELLO");
        //wto.setUserData(o);
        //System.out.println(wto.getUserData());
        //
        //Variant var = new Variant(0);
        //
        //WT wt = new wildtangent.webdriver.impl.WT();
        //
        //WT wt2 = wt3dLib.getWT(wt);
        //
        //Applet a = new Applet();
        //
        //JSObject host = JSObject.getWindow(a);
        //host.eval("alert(\"" + "DEPR" + "\");");

        //Print class loader name loaded this class
        System.out.println("Current Class Loader : "
                           + WTPlayerMain.class.getClassLoader().getClass().getName());

        ClassLoader loader = ClassLoader.getSystemClassLoader();
        //ClassLoader loader = classVar.getClassLoader();

        URL[] urls = ((URLClassLoader)loader).getURLs();
        for(URL url: urls){
            System.out.println(url.getFile());
        }

        WT wt = new wildtangent.webdriver.impl.WT();

        try{
            Class<?> gameMainClass = loader.loadClass("dark.Main");
            Class<?> class2 = loader.loadClass("dark.cGameLoader");
            Object gameMain = gameMainClass.newInstance();
            System.out.println("OBJECT MADE: " + gameMain);

            Class[] arrclass = {Object.class, int.class};
            Method gameBegin = gameMainClass.getMethod("begin", arrclass);

            Object[] arrobject = {wt, 1};
            gameBegin.invoke(gameMain, arrobject);
        } catch (ClassNotFoundException | InstantiationException |
                 IllegalAccessException | NoSuchMethodException |
                 InvocationTargetException e){
            e.printStackTrace();
        }

        //oMain m = new Main();
    }
}
