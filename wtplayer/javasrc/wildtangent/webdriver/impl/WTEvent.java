package wildtangent.webdriver.impl;

public class WTEvent extends wildtangent.webdriver.jni.WTEvent
    implements wildtangent.webdriver.WTEvent {

    /*public WTEvent(long cPtr, boolean cMemoryOwn) {
        super(cPtr, cMemoryOwn);
    }*/

    public class WTEventSub extends wildtangent.webdriver.jni.WTEvent {
        public WTEventSub(long cPtr, boolean cMemoryOwn) {
            super(cPtr, cMemoryOwn);
        }
    }

    wildtangent.webdriver.jni.WTEvent event;

    public WTEvent(long cPtr, boolean cMemoryOwn) {
        this.event = new WTEventSub(cPtr, cMemoryOwn);
        System.out.printf("=============GetInverval!!! : %d\n", this.event.getInterval());
    }

    public WTEvent(wildtangent.webdriver.jni.WTEvent event) {
        this.event = event;
        System.out.printf("=============GetInverval!!! : %d\n", this.event.getInterval());
    }


    public int getId(){
        return this.event.getId();
    }

    public int getExceptionData(){
        return this.event.getExceptionData();
    }

    public int getWTX(){
        return this.event.getWTX();
    }

    public int getX(){
        return this.event.getX();
    }

    public int getButtonState(){
        return this.event.getButtonState();
    }

    public int getTime(){
        return this.event.getTime();
    }

    public int getExceptionType(){
        return this.event.getExceptionType();
    }

    public wildtangent.webdriver.WTObject getStage(){
        return this.event.getStage();
    }

    public int getKeyState(){
        return this.event.getKeyState();
    }

    public int getInterval(){
        return this.event.getInterval();
    }

    public int getWTY(){
        return this.event.getWTY();
    }

    public int getY(){
        return this.event.getY();
    }

    public int getType(){
        return this.event.getType();
    }

    public int getKey(){
        return this.event.getKey();
    }

    public wildtangent.webdriver.WTObject getCamera(){
        return this.event.getCamera();
    }

    public wildtangent.webdriver.WTObject getObject(){
        return this.event.getObject();
    }
}

