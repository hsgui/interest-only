package campustest.google.hsgui.com;

import java.io.File;
import java.io.PrintWriter;
import java.util.Scanner;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-9-23
 * Time: 上午9:08
 * To change this template use File | Settings | File Templates.
 */
public class ReadPhoneNumber {

    public static void main(String[] args) throws Exception {
        ReadPhoneNumber read = new ReadPhoneNumber();
        read.run();
    }

    public void run() throws Exception{
        String path = ReadPhoneNumber.class.getClassLoader().getResource("").toURI().getPath().substring(1);
        Scanner in = new Scanner(new File(path + "A.in"));
        PrintWriter out = new PrintWriter(new File(path + "A.out"));
        int testCount = new Integer(in.nextLine());
        for (int i =0; i<testCount;i++){
            String testCase = in.nextLine();
            String[] test = testCase.split(" ");
            String numberText = test[0];
            String pattern = test[1];
            String[] counts = pattern.split("-");
            int start = 0;

            StringBuilder builder = new StringBuilder();
            for (int j = 0; j < counts.length; j++){
                int count = new Integer(counts[j]);
                if (count == 0) continue;
                String numberString = readNumber(numberText.substring(start, start + count), count);
                builder.append(numberString);
                start = start + count;
            }
            out.printf("Case #%d: %s\n", (i+1), builder.toString().trim());
        }
        out.flush();
        out.close();
        in.close();
    }

    public String readNumber(String numberText, int length){
        int count = 0;
        int index = 0;
        char currentC = numberText.charAt(0);
        StringBuilder builder = new StringBuilder();
        while (index < length){
            if (numberText.charAt(index) == currentC){
                count++;
                index++;
            }else{
                String successiveNumber = readSuccessiveNumber(currentC, count);
                if (successiveNumber != null){
                    builder.append(successiveNumber);
                }else{
                    for (int i = 0; i < count; i++){
                        builder.append(readSuccessiveNumber(currentC, 1));
                    }
                }
                count = 0;
                currentC = numberText.charAt(index);
            }
        }
        if (index == length){
            String successiveNumber = readSuccessiveNumber(currentC, count);
            if (successiveNumber != null){
                builder.append(successiveNumber);
            }else{
                for (int i = 0; i < count; i++){
                    builder.append(readSuccessiveNumber(currentC, 1));
                }
            }
        }

        return builder.toString();
    }

    public String readSuccessiveNumber(char c, int count){
        String num = "";
        if (count > 10){
            return null;
        }
        switch (count){
            case 1:
                num ="";break;
            case 2:
                num = "double";break;
            case 3:
                num = "triple";break;
            case 4:
                num = "quadruple";break;
            case 5:
                num = "quintuple";break;
            case 6:
                num = "sextuple";break;
            case 7:
                num = "septuple";break;
            case 8:
                num = "octuple";break;
            case 9:
                num = "nonuple";break;
            case 10:
                num = "decuple";break;
            default:break;
        }

        String number="";
        switch (c){
            case '0':
                number = "zero";break;
            case '1':
                number = "one";break;
            case '2':
                number = "two";break;
            case '3':
                number = "three";break;
            case '4':
                number = "four";break;
            case '5':
                number = "five";break;
            case '6':
                number = "six";break;
            case '7':
                number = "seven";break;
            case '8':
                number = "eight";break;
            case '9':
                number = "nine";break;
            default:break;
        }
        if ("".equals(num)){
            return number+" ";
        }else{
            return num + " " + number + " ";
        }
    }
}
