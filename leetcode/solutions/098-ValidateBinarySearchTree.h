#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"

using namespace std;

// https://leetcode.com/problems/validate-binary-search-tree/
class ValidateBinarySearchTree{
public:
    bool isValidBST(TreeNode* root)
    {
        if (root == NULL)
        {
            return true;
        }

        int max, min;
        return isValidBST(root, max, min);
    }

    bool isValidBST(TreeNode* root, int& max, int& min)
    {
        assert(root != NULL);
        int subTreeMax, subTreeMin;
        if (root->left == NULL)
        {
            min = root->val;
        }
        else
        {
            bool valid = isValidBST(root->left, subTreeMax, subTreeMin);
            if (!(valid && subTreeMax < root->val))
            {
                return false;
            }
            min = subTreeMin;
        }
        if (root->right == NULL)
        {
            max = root->val;
        }
        else
        {
            bool valid = isValidBST(root->right, subTreeMax, subTreeMin);
            if (!(valid && subTreeMin > root->val))
            {
                return false;
            }
            max = subTreeMax;
        }

        return true;
    }
    // thread binary tree - inorder traversal
    // runtime error!!!
    bool isValidBSTV2(TreeNode* root) 
    {
        TreeNode* current = root;
        TreeNode* parent = NULL;
        while (current != NULL)
        {
            if (current->left == NULL)
            {
                if (parent != NULL && parent->val > current->val)
                {
                    return false;
                }
                parent = current;
                current = current->right;
            }
            else
            {
                TreeNode* pre = current->left;
                for (; pre->right != NULL && pre->right != current; pre = pre->right);
                if (pre->right == NULL)
                {
                    pre->right = current;
                    current = current->left;
                }
                else
                {
                    if (parent != NULL && parent->val > current->val)
                    {
                        return false;
                    }
                    pre->right = NULL;
                    parent = current;
                    current = current->right;
                }
            }
        }
        return true;
    }

    bool Test()
    {
        TreeNode t0(0);
        TreeNode t1(1);
        TreeNode t1_1(1);
        TreeNode t2(2);
        TreeNode t3(3);
        TreeNode t4(4);
        TreeNode t5(5);

        assert(isValidBST(NULL) == true);
        assert(isValidBST(&t1) == true);

        t3.left = &t1, t3.right = &t4;
        t1.right = &t2;
        assert(isValidBST(&t3) == true);

        t4.left = &t5;
        assert(isValidBST(&t3) == false);

        t0.left = &t1, t0.right = NULL;
        t1.left = NULL, t1.right = NULL;
        assert(isValidBST(&t0) == false);

        t1.left = &t1_1, t1.right = NULL;
        assert(isValidBST(&t1) == false);

        return true;
    }
};