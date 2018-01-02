import wildtangent.webdriver.WT;
import wildtangent.webdriver.WTVector3D;
import wildtangent.webdriver.WTObject;
import wildtangent.webdriver.wt3dLib;
import netscape.javascript.JSObject;
import com.ms.com.Variant;

import java.applet.Applet;
import java.net.URLClassLoader;
import java.net.URL;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ArrayBlockingQueue;

import java.lang.reflect.Method;
import java.lang.reflect.InvocationTargetException;

public class WTPlayerMain
{

	public enum Message {
	    Quit
	}

    static {
        System.loadLibrary("WTEngine");
    }

    private ArrayBlockingQueue<Message> q = new ArrayBlockingQueue<Message>(128);
    private boolean loop = true;

    public WTPlayerMain(){
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
            Applet gameMain = (Applet)gameMainClass.newInstance();
            System.out.println("OBJECT MADE: " + gameMain);

            Class[] arrclass = {Object.class, int.class};
            Method gameBegin = gameMainClass.getMethod("begin", arrclass);

            Object[] arrobject = {wt, 1};
            gameBegin.invoke(gameMain, arrobject);
        } catch (ClassNotFoundException | InstantiationException |
                 IllegalAccessException | NoSuchMethodException |
                 InvocationTargetException e){
            e.printStackTrace();
        } catch (ClassCastException e) {
            System.err.println("Error! Failed to load game: The game's main class must extend java.applet.Applet.");
            e.printStackTrace();
        }

        /*Runtime.getRuntime().addShutdownHook(new Thread() {
            public void run() {
                System.out.println("CTRLC hit");
                loop = false;
                q.add(Message.Quit);
            }
         });*/

        while(loop) {
			try {
				Message val = q.take();
				switch(val) {
				case Quit:
					System.out.println("QUIT MESSAGE");
					loop = false;
					break;
				}
			} catch (InterruptedException e) {
				System.out.println("INTERRUPT " + e.toString());
			}
		}

        System.out.println("MAIN ENDING NORMALLY");

    }

    public static void main(String[] args)
    {
        for(String arg : args)
            System.out.println("ARG: " + arg);

        new WTPlayerMain();
    }
}
