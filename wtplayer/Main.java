import wildtangent.webdriver.WTVector3D;
import wildtangent.webdriver.WTObject;

public class Main
{

    static {
        System.loadLibrary("WTEngine");
    }

    public static void main(String[] args)
    {
        WTVector3D v = new WTVector3D();
        v.setX(4.04f);
        System.out.printf("X is %f\n", v.getX());

        WTObject wto = new WTObject();
        System.out.printf("Name: %s\n", wto.getName());
        //System.out.println(wto.getUserData());

        Object o = new String("HELLO");
        wto.setUserData(o);
        System.out.println(wto.getUserData());
    }
}
