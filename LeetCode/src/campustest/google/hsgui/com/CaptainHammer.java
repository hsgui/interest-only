package campustest.google.hsgui.com;

import java.io.File;
import java.io.PrintWriter;
import java.util.Scanner;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-9-14
 * Time: 下午10:37
 * To change this template use File | Settings | File Templates.
 */
public class CaptainHammer {

    public static void main(String[] args) throws Exception{
        CaptainHammer hammer = new CaptainHammer();
        hammer.run();
    }

    public void run() throws Exception{
        String path = CaptainHammer.class.getClassLoader().getResource("").toURI().getPath().substring(1);
        Scanner in = new Scanner(new File(path + "A.in"));
        PrintWriter out = new PrintWriter(new File(path + "A.out"));
        int testCase = new Integer(in.nextLine());
        for (int i = 0; i < testCase; i++){
            String line = in.nextLine();
            String[] vd = line.split(" ");
            double theta = calculateTheta(new Integer(vd[0]), new Integer(vd[1]));
            out.printf("Case #%d: %.7f\n", i+1, theta);
        }
        out.flush();
        out.close();
        in.close();
    }

    public double calculateTheta(int v, int d){
        double g = 9.8;
        double temp = d*9.8/(v*v);
        double theta = Math.asin(Math.min(temp,1));
        return theta/(2*Math.PI)*180;
    }
}
