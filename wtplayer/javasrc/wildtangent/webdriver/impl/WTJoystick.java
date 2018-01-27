package wildtangent.webdriver.impl;

import wildtangent.webdriver.WTEventJoystickCallback;

public class WTJoystick extends wildtangent.webdriver.jni.WTJoystick
    implements wildtangent.webdriver.WTJoystick {

    public WTJoystick(long cPtr, boolean cMemoryOwn) {
        super(cPtr, cMemoryOwn);
    }


    public void setOnEvent(WTEventJoystickCallback wTEventJoystickCallback) {
        /*if (this.rni_wt == null) {
            System.out.println("Error: no rni_wt to hook the joystick to");
        }
        this.rni_wt.setOnJoystickEvent(wTEventJoystickCallback);*/
    }

}

