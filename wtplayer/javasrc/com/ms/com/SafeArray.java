package com.ms.com;

public class SafeArray {

	private byte[] arrby;

	public SafeArray(int i, int length) {}

	public void fromByteArray(byte[] arrby) {
		this.arrby = arrby;
	}

	public byte[] toByteArray() {
		return this.arrby;
	}
}
