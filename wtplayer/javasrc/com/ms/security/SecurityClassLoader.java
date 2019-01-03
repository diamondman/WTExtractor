package com.ms.security;

public class SecurityClassLoader extends ClassLoader {
    @SuppressWarnings("rawtypes")
    protected Class defineClass(String name, byte[] b, int off, int length,
                                PermissionSet permissionSet,
                                java.security.Principal principal) {
        System.out.printf("DEFINE CLASS "+name+"\n");
        return super.defineClass(name, b, off, length);
    }
}
