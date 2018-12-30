import java.applet.Applet;
import java.lang.reflect.Method;
import java.lang.reflect.InvocationTargetException;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ArrayBlockingQueue;

import wildtangent.webdriver.WT;


public class WTPlayerMain {

    public enum Message {
        Quit
    }

    static {
        System.loadLibrary("WTEngine");
    }

    private ArrayBlockingQueue<Message> q = new ArrayBlockingQueue<Message>(128);
    private boolean loop = true;

    public WTPlayerMain(String localver_path){
        System.out.println("Current Class Loader : "
                           + WTPlayerMain.class.getClassLoader().getClass().getName());

        ClassLoader loader = ClassLoader.getSystemClassLoader();
        System.out.println("Current System Class Loader : " +
                           ClassLoader.getSystemClassLoader().getClass().getName());

        WT wt = new wildtangent.webdriver.impl.WT(localver_path, 800, 600);

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
            System.err.println("Error! Failed to load game: The game's main "+
                               "class must extend java.applet.Applet.");
            e.printStackTrace();
        }

        /*Runtime.getRuntime().addShutdownHook(new Thread() {
            public void run() {
                System.out.println("CTRLC hit");
                loop = false;
                q.add(Message.Quit);
            }
         });*/

        /*try {
            Thread.sleep(5000);
            wt.stop();
            Thread.sleep(5000);
            wt.start();
            Thread.sleep(5000);
            wt.stop();
            Thread.sleep(5000);
            wt.start();
        } catch (InterruptedException e) {

        }*/

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

        if(args.length < 1)
            System.out.println("Please provide a path to a game's localver directory.");
        else
            new WTPlayerMain(args[0]);
    }
}
