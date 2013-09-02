package tree.hsgui.com;

import node.tree.hsgui.com.BSTNode;

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

        BSTNode head = BinarySearchTree.constructTheTestBST();
        head = toSortedDoublyLinkedList.bstToSortedDoublyLinkedList(head);
        toSortedDoublyLinkedList.printBSTWithDoublyLinkedListWay(head);
    }

    public BSTNode bstToSortedDoublyLinkedList(BSTNode bstreeHead)
    {
        if (bstreeHead == null){
            return bstreeHead;
        }
        if (bstreeHead.right == null && bstreeHead.left == null){
            bstreeHead.right = bstreeHead;
            bstreeHead.left = bstreeHead;
            return bstreeHead;
        }
        BSTNode leftHead = bstreeHead.left;
        BSTNode rightHead = bstreeHead.right;

        bstreeHead.left = bstreeHead;   //the root of the bst becomes a doubly linked list with only one node.
        bstreeHead.right = bstreeHead;
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
        BSTNode lastNodeOfFirst = first.left;
        BSTNode lastOfNodeOfSecond = second.left;
        lastNodeOfFirst.right = second;
        lastOfNodeOfSecond.right = first;
        second.left = lastNodeOfFirst;
        first.left = lastOfNodeOfSecond;
        return first;
    }

    public void printBSTWithDoublyLinkedListWay(BSTNode bstreeHead)
    {
        BSTNode currentNode = bstreeHead;
        if (bstreeHead != null){
            do {
                System.out.println(currentNode.value);
                currentNode = currentNode.right;
            }while (currentNode != bstreeHead);
        }
    }
}
