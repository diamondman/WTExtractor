package wildtangent.webdriver;

public class wt3dLib {
    public static WT getWT(Object o) {
        System.out.println(" --- Create WT Object ---");
        if(o instanceof WT){
            return (WT)o;
        }
        throw new IllegalArgumentException("The parameter must be an instance of WT.");
    }
}
