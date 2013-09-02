package util.hsgui.com;

import java.util.SortedSet;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-9-2
 * Time: 下午4:33
 * To change this template use File | Settings | File Templates.
 */
public class Util {
    public static <T extends Comparable<? super T>> boolean isBetween(T low, T high, T value)
    {
        return value.compareTo(low) >= 0 && value.compareTo(high) <= 0;
    }
}
