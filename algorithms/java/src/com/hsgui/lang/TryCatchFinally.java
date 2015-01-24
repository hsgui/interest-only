package com.hsgui.lang;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-10-10
 * Time: 下午9:43
 * To change this template use File | Settings | File Templates.
 */
public class TryCatchFinally {

    public static void main(String[] args){
        TryCatchFinally t = new TryCatchFinally();
        System.out.println(t.test1());
    }

    public int test1(){
        int i = 2;
        try{
            i = 3;
            System.out.println("try: i=" + i);
            throw new ClassNotFoundException();
        }catch (Exception ex){
            System.out.println("catch: i=" + i);
            return i;
        }finally {
            i = 4;
            System.out.println("finally: i=" + i);
            return i;
        }
    }
}
