package campustest.google.hsgui.com;

import java.io.File;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-9-23
 * Time: 上午11:12
 * To change this template use File | Settings | File Templates.
 */
public class SortingP {

    public static void main(String[] args) throws Exception {
        SortingP p = new SortingP();
        p.run();
    }

    public void run() throws Exception{
        String path = RationalNumberTree.class.getClassLoader().getResource("").toURI().getPath().substring(1);
        Scanner in = new Scanner(new File(path + "C.in"));
        PrintWriter out = new PrintWriter(new File(path + "C.out"));
        int testCount = new Integer(in.nextLine());
        for (int i =1; i<=testCount;i++){
            int number = new Integer(in.nextLine());
            String line = in.nextLine();
            String[] numbers = line.split(" ");
            ArrayList<Integer> array = new ArrayList<Integer>(number);
            for (int j = 0; j < number; j++){
                array.add(new Integer(numbers[j]));
                sorting(array);
            }
            out.printf("Case #%d:", i);
            for (int j = 0; j < number;j++){
                out.printf(" %d", array.get(j));
            }
            out.printf("\n");
        }
        out.flush();
        out.close();
        in.close();
    }

    public void sorting(ArrayList<Integer> array){
        int length = array.size();
        for (int i = 0; i < length; i++){
            int j = i - 1;
            int vi = array.get(i);
            int lastPos = i;
            int odd = Math.abs(array.get(i)) % 2;
            while (j >= 0){
                if (odd == 1){   //odd
                    if (Math.abs(array.get(j)) %2 == odd){
                        if (vi < array.get(j)){
                            array.set(lastPos, array.get(j));
                            lastPos = j;
                        }
                    }
                }else{
                    if (Math.abs(array.get(j)) %2 == odd){
                        if (vi > array.get(j)){
                            array.set(lastPos, array.get(j));
                            lastPos = j;
                        }
                    }
                }
                j--;
            }
            array.set(lastPos, vi);
        }
    }
}
