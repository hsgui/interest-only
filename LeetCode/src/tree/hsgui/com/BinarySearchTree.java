package tree.hsgui.com;

import node.tree.hsgui.com.BSTNode;
import node.tree.hsgui.com.SingleLinkedListNode;
import util.hsgui.com.Util;

import java.util.Stack;

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

    public int maxTreeHeight(BSTNode root)
    {
        if (root == null) return 0;
        return Math.max(maxTreeHeight(root.left), maxTreeHeight(root.right)) + 1;
    }

    /**
     * cite: http://leetcode.com/2010/04/maximum-height-of-binary-tree.html
     *       http://en.wikipedia.org/wiki/Tree_traversal#Post-order
     * @param root
     * @return the max height of the tree.
     */
    public int maxTreeHeightIterativeWithPostOrderTraversal(BSTNode root)
    {
        if (root == null) return 0;
        Stack<BSTNode> stack = new Stack<BSTNode>();
        int maxHeight = 0;
        BSTNode previousNode = null;

        stack.push(root);
        while (!stack.isEmpty()){
            BSTNode currentNode = stack.peek();
            if (previousNode == null || previousNode.left == currentNode || previousNode.right == currentNode){
                if (currentNode.left != null){
                    stack.push(currentNode.left);
                }else if (currentNode.right != null){
                    stack.push(currentNode.right);
                }
            }else if (currentNode.left == previousNode){
                if (currentNode.right != null){
                    stack.push(currentNode.right);
                }
            }else{
                //visit the currentNode;
                stack.pop();
            }
            previousNode = currentNode;
            if (stack.size() > maxHeight){
                maxHeight = stack.size();
            }
        }
        return maxHeight;
    }

    /**
     * cite: http://leetcode.com/2010/04/binary-search-tree-in-order-traversal.html
     * traversal the tree in order iteratively.
     * 1. use the threaded binary tree to traversal the tree without recursion.
     * 2. add a parent pointer to the data structure, this allows us to return to a node's parent.
     *    To determine when to print a node's value, we would have to determine when it's returned from.
     *    If it's returned from its left child, then print its value then traversa to its right child,
     *    on the other hand if it's returned from its right child, then traversa up one level to its parent.
     * @param root
     */
    public void inOrderTraversalIterative1(BSTNode root)
    {
        Stack<BSTNode> stack = new Stack<BSTNode>();
        boolean done = false;
        BSTNode current = root;
        while (!done){
            if (current != null){
                stack.push(current);
                current = current.left;
            }else{
                if (stack.empty()){
                    done = true;
                }else{
                    current = stack.pop();
                    System.out.println(current.value);
                    current = current.right;
                }
            }
        }
    }

    public void writeBSTWithPreOrder(BSTNode root)
    {

    }

    /**
     * 1. we can read all the data into memory first.
     * 2. read one node's data, and insert into the proper position of the tree.
     *    2.1 we can see each node as the root of some tree. so each node have associated interval.
     * @param fileName
     */
    public void readBSTWithPreOrder(String fileName)
    {
        Stack<RootWithKeyInterval> stack = new Stack<RootWithKeyInterval>();
        int[] keys = {30, 20, 10, 40, 35, 50};
        int currentIndex = 1;
        BSTNode root = new BSTNode(keys[0]);
        RootWithKeyInterval rootInterval = new RootWithKeyInterval();
        rootInterval.root = root;
        rootInterval.lowKey = Integer.MIN_VALUE;
        rootInterval.highKey = Integer.MAX_VALUE;
        while (!stack.isEmpty()){
            RootWithKeyInterval currentRootInterval = stack.peek();
            if (Util.isBetween(currentRootInterval.lowKey, currentRootInterval.highKey, keys[currentIndex])){
                int currentRootKey = (Integer)currentRootInterval.root.value;
                BSTNode childRoot = new BSTNode(keys[currentIndex]);
                if (currentRootKey < keys[currentIndex]){
                    currentRootInterval.root.left = childRoot;

                    RootWithKeyInterval leftRootInterval = new RootWithKeyInterval();
                    leftRootInterval.root = childRoot;
                    leftRootInterval.lowKey = currentRootInterval.lowKey;
                    leftRootInterval.highKey = currentRootKey;
                    stack.push(leftRootInterval);
                    currentIndex++;
                }
                else{
                    currentRootInterval.root.right = childRoot;
                    RootWithKeyInterval rightRootInterval = new RootWithKeyInterval();
                    rightRootInterval.root = childRoot;
                    rightRootInterval.lowKey = currentRootKey;
                    rightRootInterval.highKey = currentRootInterval.highKey;
                    stack.pop();
                    stack.push(rightRootInterval);
                    currentIndex++;
                }
            }else{
                stack.pop();
            }
        }
    }

    public void writeBSTWithPostOrder(BSTNode root)
    {

    }

    /**
     * with the post order traversal, we need read all data into memory first.
     * @param fileName
     */
    public void readBSTWithPostOrder(String fileName)
    {
    }

    /**
     * cite: http://leetcode.com/2010/11/convert-sorted-array-into-balanced.html
     *       this method is a top-down approach
     * @param sortedArray : the array that is already sorted.
     * @param start       : the start position of the array.
     * @param end         : the end position of the array.
     * @return
     */
    public BSTNode sortedArray2BSTree(int[] sortedArray, int start, int end)
    {
        if (start > end) return null;
        int mid = (start + end) / 2;
        BSTNode root = new BSTNode(sortedArray[mid]);
        root.left = sortedArray2BSTree(sortedArray, start, mid - 1);
        root.right = sortedArray2BSTree(sortedArray, mid + 1, end);

        return root;
    }

    public BSTNode linkedList2BSTree(SingleLinkedListNode head, int start, int end)
    {
        if (start > end) return null;
        int mid = start + (end - start) / 2;
        BSTNode leftChild = linkedList2BSTree(head, start, mid - 1);
        BSTNode root = new BSTNode(head.value);
        root.left = leftChild;
        head = head.next;
        root.right = linkedList2BSTree(head, mid + 1, end);
        return root;
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

    /**
     * represents a subtree with key in the interval [lowKey, highKey)
     */
    private class RootWithKeyInterval
    {
        private BSTNode root;
        private int lowKey;
        private int highKey;
    }
}
