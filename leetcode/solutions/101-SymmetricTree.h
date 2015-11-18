#ifndef _SYMMETRIC_TREE_H_
#define _SYMMETRIC_TREE_H_

#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"

// https://leetcode.com/problems/symmetric-tree/
class SymmetricTree
{
public:
    bool isSymmetric(TreeNode* root)
    {
        if ((root == NULL) || (root != NULL && root->left == NULL && root->right == NULL))
        {
            return true;
        }
        else
        {
            return isSymmetric(root->left, root->right);
        }
    }

    bool isSymmetric(TreeNode* p, TreeNode* q)
    {
        if (p != NULL && q != NULL)
        {
            return (p->val == q->val)
                && isSymmetric(p->left, q->right)
                && isSymmetric(p->right, q->left);
        }
        else if (p == NULL && q == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Test()
    {
        TreeNode t1(1);
        TreeNode t2_1(2);
        TreeNode t2_2(2);
        TreeNode t3_1(3);
        TreeNode t3_2(3);
        TreeNode t4_1(4);
        TreeNode t4_2(4);

        t1.left = &t2_1, t1.right = &t2_2;
        t2_1.left = &t3_1, t2_1.right = &t4_1;
        t2_2.left = &t4_2, t2_2.right = &t3_2;

        bool expected = true;
        bool actual = isSymmetric(&t1);
        assert(expected == actual);

        return true;
    }
};

#endif