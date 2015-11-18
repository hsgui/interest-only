#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"

using namespace std;

class BinaryTreePostorderTraversal{
public:
    vector<int> postorderTraversal(TreeNode* root)
    {
        vector<int> postorder;
        if (root == NULL)
        {
            return postorder;
        }
        TreeNode* childRoot = root;
        TreeNode* lastRoot = NULL;
        vector<TreeNode*> rootStack;
        rootStack.push_back(childRoot);
        while (!rootStack.empty())
        {
            childRoot = rootStack.back();
            // enter the stack
            if (lastRoot == NULL)
            {
                if (childRoot->left == NULL)
                {
                    if (childRoot->right == NULL)
                    {
                        lastRoot = childRoot;
                        rootStack.pop_back();
                        postorder.push_back(childRoot->val);
                    }
                    else
                    {
                        rootStack.push_back(childRoot->right);
                    }
                }
                else
                {
                    rootStack.push_back(childRoot->left);
                }
            }
            // pop from the stack
            else
            {
                if (childRoot->left == lastRoot)
                {
                    if (childRoot->right == NULL)
                    {
                        lastRoot = childRoot;
                        rootStack.pop_back();
                        postorder.push_back(childRoot->val);
                    }
                    else
                    {
                        rootStack.push_back(childRoot->right);
                        lastRoot = NULL;
                    }
                }
                else if (childRoot->right == lastRoot)
                {
                    rootStack.pop_back();
                    lastRoot = childRoot;
                    postorder.push_back(childRoot->val);
                }
                else
                {
                    assert(false);
                }
            }
        }

        return postorder;
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
        t3.left = &t6, t3.right = &t7;

        vector<int> inorder = { 4, 5, 2, 6, 7, 3, 1 };

        vector<int> actual = postorderTraversal(&t1);
        assert(equal(actual.begin(), actual.end(), inorder.begin()));

        t2.left = NULL, t2.right = &t3;
        t3.left = NULL, t3.right = &t1;
        t1.left = NULL, t1.right = NULL;
        inorder = { 1, 3, 2 };
        actual = postorderTraversal(&t2);
        assert(equal(actual.begin(), actual.end(), inorder.begin()));

        return true;
    }
};