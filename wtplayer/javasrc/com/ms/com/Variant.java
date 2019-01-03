package com.ms.com;

public class Variant {
    /* Types copied from https://www.javatips.net/api/jacob-master/src/com/jacob/com/Variant.java */
    public static final short VariantEmpty = 0;
//  public static final short VariantShort = 2;
    public static final short VariantInt = 3;
    public static final short VariantFloat = 4;
    public static final short VariantDouble = 5;
    public static final short VariantString = 8;
    public static final short VariantBoolean = 11;
    public static final short VariantSafeArray = 27;

    private final short type;
    private int valint = 0;
    private double valdouble = 0;
    private float valfloat = 0;
    private String valstring = "";
    private boolean valbool = false;
    private SafeArray valsafearray = null;

    public Variant(int val) {
        this.type = VariantInt;
        this.valint = val;
    }
    public Variant(float val) {
        this.type = VariantFloat;
        this.valfloat = val;
    }
    public Variant(double val) {
        this.type = VariantDouble;
        this.valdouble = val;
    }
    public Variant(String val) {
        this.type = VariantString;
        this.valstring = val;
    }
    public Variant(boolean val) {
        this.type = VariantBoolean;
        this.valbool = val;
    }
    public Variant() {
        this.type = VariantEmpty;
    }

    public short getvt(){
        return this.type;
    }

    public boolean getBoolean(){
        return this.valbool;
    }
    public double getDouble(){
        return this.valdouble;
    }
    public float getFloat(){
        return this.valfloat;
    }
    public int getInt(){
        return this.valint;
    }
    public String getString(){
        return this.valstring;
    }

    public SafeArray toSafeArray() {
        return this.valsafearray;
    }
    public void putSafeArray(SafeArray val) {
        this.valsafearray = val;
    }
    public void putSafeArray(byte[] val) {
        this.valsafearray = new SafeArray(0, 0);
        this.valsafearray.fromByteArray(val);
    }
}
