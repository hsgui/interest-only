#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"

using namespace std;

// https://leetcode.com/problems/balanced-binary-tree/

class BalancedBinaryTree
{
public:
    bool isBalanced(TreeNode* root)
    {
        if ((root == NULL))
        {
            return true;
        }
        int leftDepth, rightDepth;
        return isBalanced(root, leftDepth, rightDepth);
    }

    bool isBalanced(TreeNode* root, int& leftDepth, int& rightDepth)
    {
        if (root == NULL)
        {
            leftDepth = 0;
            rightDepth = 0;
            return true;
        }
        else if ((root != NULL) && (root->left == NULL) && (root->right == NULL))
        {
            leftDepth = 1;
            rightDepth = 1;
            return true;
        }
        else
        {
            int leftNodeLeftDepth, leftNodeRightDepth;
            int rightNodeLeftDepth, rightNodeRightDepth;
            bool isLeftBalanced = isBalanced(root->left, leftNodeLeftDepth, leftNodeRightDepth);
            if (isLeftBalanced)
            {
                bool isRightBalanced = isBalanced(root->right, rightNodeLeftDepth, rightNodeRightDepth);
                if (isRightBalanced)
                {
                    leftDepth = max(leftNodeLeftDepth, leftNodeRightDepth) + 1;
                    rightDepth = max(rightNodeLeftDepth, rightNodeRightDepth) + 1;
                    if (abs(leftDepth - rightDepth) <= 1)
                    {
                        return true;
                    }
                }
            }
            return false;
        }
    }

    bool Test()
    {
        TreeNode t1(1);
        TreeNode t2(2);
        TreeNode t3(3);
        TreeNode t4(4);
        TreeNode t5(5);
        TreeNode t6(6);
        TreeNode t7(7);

        t1.left = &t2, t1.right = &t3;
        t2.left = &t4, t2.right = &t5;
        t4.left = &t6;

        bool expected = false;
        bool actual = isBalanced(&t1);
        assert(actual == expected);

        t3.right = &t7;
        expected = true;
        actual = isBalanced(&t1);
        assert(actual == expected);

        return true;
    }
};