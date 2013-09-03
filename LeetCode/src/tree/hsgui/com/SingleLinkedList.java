package tree.hsgui.com;

import node.tree.hsgui.com.SingleLinkedListNode;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-9-3
 * Time: 下午3:58
 * To change this template use File | Settings | File Templates.
 */
public class SingleLinkedList {


    public static void main(String[] args)
    {
        SingleLinkedList list = new SingleLinkedList();
        SingleLinkedListNode head = list.createSingleLinkedListWithCycle();
        System.out.println("contains cycle: " + list.isContainsCycleInLinkedList(head));
        list.cycleFindingWithFloyd(head);
    }

    /**
     * cite: http://en.wikipedia.org/wiki/Floyd%27s_cycle-finding_algorithm#Tortoise_and_hare
     * find the cycle in the linked list: the start position of the cycle and the length of the cycle.
     * @param head
     */
    public void cycleFindingWithFloyd(SingleLinkedListNode head)
    {
        int cycleStartPosition = 0;
        int cycleLength = 0;

        String formatString = "cycleStartPosition: %d, cycleLength: %d";
        String logString;
        if (head == null){
            logString = String.format(formatString, cycleStartPosition, cycleLength);
        }else{
            SingleLinkedListNode slow = head;
            SingleLinkedListNode fast = head.next;
            while (slow != null && fast != null && fast.next != null){
                slow = slow.next;
                fast = fast.next.next;
                if (slow == fast){
                    break;
                }
            }
            if (slow == null || fast == null || fast.next == null){     //no cycle.
                logString = String.format(formatString, cycleStartPosition, cycleLength);
            }else{
                slow = head;
                fast = fast.next;
                while (fast != slow){
                    cycleStartPosition++;
                    slow = slow.next;
                    fast = fast.next;
                }
                cycleLength = 1;
                fast = fast.next;
                while (slow != fast){
                    fast = fast.next;
                    cycleLength++;
                }
                logString = String.format(formatString, cycleStartPosition, cycleLength);
            }
        }

        System.out.println(logString);
    }


    public boolean isContainsCycleInLinkedList(SingleLinkedListNode head)
    {
        if (head == null){
            return false;
        }
        SingleLinkedListNode slow = head;
        SingleLinkedListNode fast = head.next;
        while (slow != null && fast != null && fast.next != null){
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast){
                return true;
            }
        }
        return false;
    }

    /**
     * a single linked list with a cycle, which is (4 -> 5 -> 6 -> 7 -> 4):
     * x4 = x8; x_i = x_(i+k*4), i >= 4, k>=0;
     * {1, 2, 3, 4, 5, 6, 7, 4, 5, 6, 7, 4, ...}
     * @return
     */
    public SingleLinkedListNode createSingleLinkedListWithCycle()
    {
        SingleLinkedListNode n1 = new SingleLinkedListNode(1);
        SingleLinkedListNode n2 = new SingleLinkedListNode(2);
        SingleLinkedListNode n3 = new SingleLinkedListNode(3);
        SingleLinkedListNode n4 = new SingleLinkedListNode(4);
        SingleLinkedListNode n5 = new SingleLinkedListNode(5);
        SingleLinkedListNode n6 = new SingleLinkedListNode(6);
        SingleLinkedListNode n7 = new SingleLinkedListNode(7);

        n1.next = n2;
        n2.next = n3;
        n3.next = n4;
        n4.next = n5;
        n5.next = n6;
        n6.next = n7;
        n7.next = n4;

        return n1;
    }
}
