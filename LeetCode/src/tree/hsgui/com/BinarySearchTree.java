package tree.hsgui.com;

import node.tree.hsgui.com.BSTNode;
import util.hsgui.com.Util;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-9-2
 * Time: 下午4:18
 * To change this template use File | Settings | File Templates.
 */
public class BinarySearchTree {

    public static void main(String[] args)
    {
        BinarySearchTree tree = new BinarySearchTree();
        BSTNode head = BinarySearchTree.constructTheTestBST();
        System.out.println(tree.isBinarySearchTree(head));
    }

    private BSTNode head;
    public BinarySearchTree()
    {
        head = null;
    }

    public BinarySearchTree addNode(int value)
    {
        if (head == null)
        {
            BSTNode node = new BSTNode(value);
            head = node;
            return this;
        }
        int headValue = (Integer)head.value;
        if (value <= headValue){
            return addNode(value);
        }else{
            return addNode(value);
        }
    }

    public static boolean isBinarySearchTree(BSTNode root)
    {
        return isBinarySearchTreeHelper(root, Integer.MIN_VALUE, Integer.MAX_VALUE);
    }

    private static boolean isBinarySearchTreeHelper(BSTNode root, int low, int high)
    {
        if (root == null) return true;
        if (Util.isBetween(low, high, (Integer)root.value)){
            return isBinarySearchTreeHelper(root.left, low, (Integer)root.value) &&
                    isBinarySearchTreeHelper(root.right, (Integer)root.value, high);
        }
        else{
            return false;
        }
    }

    public static boolean isBinarySearchTreeInOrder(BSTNode root)
    {
        return isBinarySearchTreeInOrderHelper(root, Integer.MIN_VALUE);
    }

    public static boolean isBinarySearchTreeInOrderHelper(BSTNode root, int prev)
    {
        if (root == null) return true;
        if (isBinarySearchTreeInOrderHelper(root.left, prev)){
            int rootValue = (Integer)root.value;
            if (rootValue >= prev){
                return isBinarySearchTreeInOrderHelper(root.right, rootValue);
            }else{
                return false;
            }
        }else{
            return false;
        }
    }

    public static BSTNode constructTheTestBST()
    {
        BSTNode head = new BSTNode(4);
        BSTNode n1 = new BSTNode(1);
        BSTNode n2 = new BSTNode(2);
        BSTNode n3 = new BSTNode(3);
        BSTNode n5 = new BSTNode(5);

        n2.left = n1;
        n2.right = n3;
        head.left = n2;
        head.right = n5;

        return head;
    }
}
