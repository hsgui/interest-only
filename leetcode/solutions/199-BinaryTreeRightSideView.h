#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"

using namespace std;

// https://leetcode.com/problems/binary-tree-right-side-view/
class BinaryTreeRightSideView{
public:
    // this is very similar with Binary tree level order traversal
    vector<int> rightSideView(TreeNode* root)
    {
        vector<int> rightView;

        if (root == NULL)
        {
            return rightView;
        }

        rightView.push_back(root->val);
        vector<int> leftRightView = rightSideView(root->left);
        vector<int> rightRightView = rightSideView(root->right);
        
        int maxLevel = max(leftRightView.size(), rightRightView.size());
        for (int i = 0; i < maxLevel; ++i)
        {
            if (i < rightRightView.size())
            {
                rightView.push_back(rightRightView[i]);
            }
            else if (i < leftRightView.size())
            {
                rightView.push_back(leftRightView[i]);
            }
        }

        return rightView;
    }

    bool Test()
    {
        TreeNode t15(15);
        TreeNode t7(7);
        TreeNode t20(20);
        TreeNode t9(9);
        TreeNode t3(3);

        t20.left = &t15, t20.right = &t7;
        t3.left = &t9, t3.right = &t20;

        vector<int> expected =
        {
            3,
            20,
            7
        };

        vector<int> actual = rightSideView(&t3);

        assert(equal(expected.begin(), expected.end(), actual.begin()));

        return true;
    }
};