package com.hsgui.lang;

import java.lang.reflect.Array;

/**
 * Created with IntelliJ IDEA.
 * User: v-shuhua
 * Date: 10/17/13
 * Time: 2:00 PM
 * To change this template use File | Settings | File Templates.
 */
public class ArrayLearn {
    /**
     * cite: http://coolshell.cn/articles/9229.html
     * ClassFile{
     *     u4               magic; (cafebabe)
     *     u2               minor_version; (0)
     *     u2               major_version; (51)
     *     u2               constant_pool_count; (0x47, actually contains 70 constants)
     *     cp_info          constant_pool[constant_pool_count-1];
     *     u2               access_flags;
     *     u2               this_class;     the index in the constant_pool.
     *     u2               super_class;    the index in the constant_pool.
     *     u2               interfaces_count;
     *     u2               interfaces[interfaces_count];
     *     u2               fields_count;
     *     field_info       fields[fields_count];
     *     u2               methods_count;
     *     method_info      methods[methods_count];
     *     u2               attributes_count;
     *     attribute_info   attributes[attributes_count];
     * }
     *
     * method_info{
     *     u2               access_flags;
     *     u2               name_index;             the index in the constant_pool.
     *     u2               descriptor_index;       the index in the constant_pool.
     *     u2               attributes_count;       0x0001
     *     attribute_info   attributes[attributes_count];   the code.
     * }
     *
     * code_attribute{
     *     u2               attribute_name_index;       "Code" constant in the constant_pool.
     *     u4               attribute_length;           the code_attribute length, does not contain the length attribute_name_index and attribute_length.
     *     u2               max_stack;
     *     u2               max_locals;
     *     u4               code_length;
     *     u1               code[code_length];          0x00-0xff, at most 256 instruments.
     *     u2               exception_table_length;
     *     {
     *         u2       start_pc;
     *         u2       end_pc;
     *         u2       handler_pc;
     *         u2       catch_type;
     *     }exception_table[exception_table_length];
     *     u2               attributes_count;
     *     attribute_info   attributes[attributes_count];
     * }
     *
     */


    public static void main(String[] args){
        int[] old = {1, 2, 3};
        int[] bigger = (int[])ArrayLearn.resizeArray(old, 5);
        bigger[3] = 4;
        bigger[4] = 5;
    }

    public static Object resizeArray(Object oldArray, int newSize){
        int oldSize = Array.getLength(oldArray);
        Class elementType = oldArray.getClass().getComponentType();
        Object newArray = Array.newInstance(elementType, newSize);
        int preserveLength = Math.min(oldSize, newSize);
        if (preserveLength > 0){
            System.arraycopy(oldArray, 0, newArray, 0, preserveLength);
        }
        return newArray;
    }
}
