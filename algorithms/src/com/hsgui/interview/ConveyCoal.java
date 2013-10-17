package com.hsgui.interview;

/**
 * Created with IntelliJ IDEA.
 * User: v-shuhua
 * Date: 10/17/13
 * Time: 4:59 PM
 * To change this template use File | Settings | File Templates.
 *
 * cite: http://coolshell.cn/articles/4429.html
 */
public class ConveyCoal {

    public static void main(String[] args){
        System.out.println("3000:1000 = " + ConveyCoal.maxCoalRemaining(3000, 1000));
    }

    /**
     * http://coolshell.cn/articles/4429.html/comment-page-2#comment-44708
     * @param coalAccount
     * @param maxCapacity
     * @return
     */
    public static int maxCoalRemaining(int coalAccount, int maxCapacity){
        int coalLeft = coalAccount;
        int distanceLeft = maxCapacity;
        int backAndForthCount = coalAccount/maxCapacity + (coalAccount % maxCapacity == 0 ? 0:1);
        int backAndForthTimes = 2 * backAndForthCount - 1;
        while (backAndForthTimes > 1){
            int costPerMile = backAndForthTimes;
            int milesToBeMoved = maxCapacity/costPerMile;
            coalLeft -= maxCapacity;                //maxCapacity = milesToBeMoved * costPerMile
            distanceLeft -= milesToBeMoved;
            backAndForthCount--;
            backAndForthTimes = 2*backAndForthCount - 1;
        }

        return maxCapacity - distanceLeft;
    }
}
