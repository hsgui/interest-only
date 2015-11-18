#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"
#include "100-SameTree.h"

using namespace std;

class ConstructBinaryTreeFromInorderPostorderTraversal
{
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder)
    {
        return buildTree(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
    }

    TreeNode* buildTree(vector<int>& inorder, int inStart, int inEnd, vector<int>& postorder, int postStart, int postEnd)
    {
        if (inStart > inEnd)
        {
            return NULL;
        }
        
        int head = postorder[postEnd];
        TreeNode* root = new TreeNode(head);
        int leftLength = 0;
        for (leftLength = 0; leftLength + inStart <= inEnd && inorder[leftLength + inStart] != head; ++leftLength);

        root->left = buildTree(inorder, inStart, inStart + leftLength - 1, postorder, postStart, postStart + leftLength - 1);
        root->right = buildTree(inorder, inStart + leftLength + 1, inEnd, postorder, postStart + leftLength, postEnd - 1);

        return root;
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

        vector<int> inorder = { 4, 2, 5, 1, 6, 3, 7 };
        vector<int> postOrder = { 4, 5, 2, 6, 7, 3, 1 };

        TreeNode* actual = buildTree(inorder, postOrder);
        SameTree sameTree;
        assert(sameTree.isSameTree(actual, &t1) == true);

        return true;
    }
};