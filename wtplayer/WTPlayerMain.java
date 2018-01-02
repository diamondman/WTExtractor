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

public class WTPlayerMain implements wildtangent.webdriver.WTEventCallback
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

        URL[] urls = ((URLClassLoader)loader).getURLs();
        for(URL url: urls){
            System.out.println(url.getFile());
        }

        wildtangent.webdriver.WT wt = new wildtangent.webdriver.impl.WT();

        wt.setOnRenderEvent(this);
        wt.setOnExceptionEvent(this);
        wt.setOnMouseEvent(this);
        wt.setOnKeyboardEvent(this);
        wt.start();

        /*try{
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
        }*/

        /*Runtime.getRuntime().addShutdownHook(new Thread() {
            public void run() {
                System.out.println("CTRLC hit");
                loop = false;
                q.add(Message.Quit);
            }
         });*/

		try {
			Thread.sleep(5000);
			wt.stop();
			Thread.sleep(5000);
			wt.start();
			Thread.sleep(5000);
			wt.stop();
			Thread.sleep(5000);
			wt.start();
		} catch (InterruptedException e) {

        }

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


    public void onExceptionEvent(wildtangent.webdriver.WTEvent var1) {}

    public void onKeyboardEvent(wildtangent.webdriver.WTEvent var1) {}

	public void onRenderEvent(wildtangent.webdriver.WTEvent var1) {
		System.out.println("CALL FROM JAVA RENDER EVENT HANDLER!!!!!!!!!!!!!!!!");
	}

    public void onMouseEvent(wildtangent.webdriver.WTEvent var1) {}

    public static void main(String[] args)
    {
        for(String arg : args)
            System.out.println("ARG: " + arg);

        new WTPlayerMain();
    }
}
