package com.app.myapplication;

public class DynamicJNI {

    static {
        System.loadLibrary("dynamic-lib");
    }

    public native int getSum(int a, int b);

    public native String getNativeString();

    public native int sum(int a, int b);

}
