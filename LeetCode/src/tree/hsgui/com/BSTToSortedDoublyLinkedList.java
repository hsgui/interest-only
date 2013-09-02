package tree.hsgui.com;

import node.tree.hsgui.com.BSTNode;
import node.tree.hsgui.com.DoublyLinkedListNode;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-9-2
 * Time: 上午10:12
 * To change this template use File | Settings | File Templates.
 */
public class BSTToSortedDoublyLinkedList {

    public static void main(String[] args)
    {
        BSTToSortedDoublyLinkedList toSortedDoublyLinkedList = new BSTToSortedDoublyLinkedList();

        BSTNode head = toSortedDoublyLinkedList.constructTheTestBST();
        head = toSortedDoublyLinkedList.bstToSortedDoublyLinkedList(head);
        toSortedDoublyLinkedList.printBSTWithDoublyLinkedListWay(head);
    }

    public BSTNode constructTheTestBST()
    {
        BSTNode head = new BSTNode(4);
        BSTNode n1 = new BSTNode(1);
        BSTNode n2 = new BSTNode(2);
        BSTNode n3 = new BSTNode(3);
        BSTNode n5 = new BSTNode(5);

        n2.previous = n1;
        n2.next = n3;
        head.previous = n2;
        head.next = n5;

        return head;
    }

    public BSTNode bstToSortedDoublyLinkedList(BSTNode bstreeHead)
    {
        if (bstreeHead == null){
            return bstreeHead;
        }
        if (bstreeHead.next == null && bstreeHead.previous == null){
            bstreeHead.next = bstreeHead;
            bstreeHead.previous = bstreeHead;
            return bstreeHead;
        }
        BSTNode leftHead = bstreeHead.previous;
        BSTNode rightHead = bstreeHead.next;

        bstreeHead.previous = bstreeHead;   //the root of the bst becomes a doubly linked list with only one node.
        bstreeHead.next = bstreeHead;
        if (leftHead != null){  //the left tree becomes a doubly linked list.
            leftHead = bstToSortedDoublyLinkedList(leftHead);
            bstreeHead = joinTwoDoublyLinkedList(leftHead, bstreeHead);
        }
        if (rightHead != null){ //the right tree becomes a doubly linked list.
            rightHead = bstToSortedDoublyLinkedList(rightHead);
            bstreeHead = joinTwoDoublyLinkedList(bstreeHead, rightHead);
        }
        return bstreeHead;
    }

    public BSTNode joinTwoDoublyLinkedList(BSTNode first, BSTNode second)
    {
        if (first == null){
            return second;
        }
        if (second == null){
            return first;
        }
        BSTNode lastNodeOfFirst = first.previous;
        BSTNode lastOfNodeOfSecond = second.previous;
        lastNodeOfFirst.next = second;
        lastOfNodeOfSecond.next = first;
        second.previous = lastNodeOfFirst;
        first.previous = lastOfNodeOfSecond;
        return first;
    }

    public void printBSTWithDoublyLinkedListWay(BSTNode bstreeHead)
    {
        BSTNode currentNode = bstreeHead;
        if (bstreeHead != null){
            do {
                System.out.println(currentNode.value);
                currentNode = currentNode.next;
            }while (currentNode != bstreeHead);
        }
    }
}
