package wildtangent.webdriver;

import wildtangent.webdriver.WTObject;

public interface WTFile
extends WTObject {
    public int status();

    public void close();

    public byte readByte();

    public float readFloat();

    public short readShort();

    public double readDouble();

    //public byte[] readAll();

    public boolean eof();

    public String readLine();

    public int getEndian();

    public int setEndian(int var1);

    public void seek(int var1);

    public int readInt();

    public int length();

    public String readString(int var1);

    public String readString();

    public int move(int var1);
}

