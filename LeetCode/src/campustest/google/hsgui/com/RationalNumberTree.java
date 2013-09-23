package campustest.google.hsgui.com;

import java.io.File;
import java.io.PrintWriter;
import java.util.Scanner;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-9-23
 * Time: 上午10:11
 * To change this template use File | Settings | File Templates.
 */
public class RationalNumberTree {

    public static void main(String[] args) throws Exception{
        RationalNumberTree t = new RationalNumberTree();
        t.run();
    }

    public void run() throws Exception{
        String path = RationalNumberTree.class.getClassLoader().getResource("").toURI().getPath().substring(1);
        Scanner in = new Scanner(new File(path + "B.in"));
        PrintWriter out = new PrintWriter(new File(path + "B.out"));
        int testCount = new Integer(in.nextLine());
        for (int i =1; i<=testCount;i++){
            String testCase = in.nextLine();
            String[] command = testCase.split(" ");
            if (command[0].equals("1")){
                long n = new Long(command[1]);
                out.printf("Case #%d: %d %d\n", i, p(n), q(n));
            }else{
                long p = new Long(command[1]);
                long q = new Long(command[2]);
                out.printf("Case #%d: %d\n", i, th(p, q));
            }
        }
        out.flush();
        out.close();
        in.close();
    }

    public int th(long p, long q){
        if (p == 1 && q == 1) return 1;
        if ( p > q){
            return 2*th(p-q, q) + 1;
        }else{
            return 2*th(p, q-p);
        }
    }

    public int p(long n){
        if (n == 1) return 1;
        long parent = n/2;
        if (n % 2 == 0){
            return p(parent);
        }else{
            return p(parent) + q(parent);
        }
    }

    public int q(long n){
        if (n == 1) return 1;
        long parent = n/2;
        if (n % 2 == 0){
            return q(parent) + p(parent);
        }else{
            return q(parent);
        }
    }
}
