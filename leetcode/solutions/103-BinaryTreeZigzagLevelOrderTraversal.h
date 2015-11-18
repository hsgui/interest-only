#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"
#include "Utils.h"

using namespace std;

class BinaryTreeZigzagLevelOrderTraversal
{
public:
    // this problem using the recursive algorithm
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) 
    {
        return zigzagLevelOrder(root, true);
    }

    vector<vector<int>> zigzagLevelOrder(TreeNode* root, bool leftToRight)
    {
        vector<vector<int>> levels;
        if (root == NULL)
        {
            return levels;
        }
        vector<int> head;
        head.push_back(root->val);
        levels.push_back(head);

        vector<vector<int>> leftLevel;
        vector<vector<int>> rightLevel;
        if (root->left != NULL)
        {
            leftLevel = zigzagLevelOrder(root->left, !leftToRight);
        }
        if (root->right != NULL)
        {
            rightLevel = zigzagLevelOrder(root->right, !leftToRight);
        }

        int maxChildrenLevel = max(leftLevel.size(), rightLevel.size());
        for (int i = 0; i < maxChildrenLevel; ++i)
        {
            vector<int> levelI;
            if (!leftToRight)
            {
                if (i < leftLevel.size())
                {
                    levelI.insert(levelI.end(), leftLevel[i].begin(), leftLevel[i].end());
                }
                if (i < rightLevel.size())
                {
                    levelI.insert(levelI.end(), rightLevel[i].begin(), rightLevel[i].end());
                }
            }
            else
            {
                if (i < rightLevel.size())
                {
                    levelI.insert(levelI.end(), rightLevel[i].begin(), rightLevel[i].end());
                }
                if (i < leftLevel.size())
                {
                    levelI.insert(levelI.end(), leftLevel[i].begin(), leftLevel[i].end());
                }
            }
            leftToRight = !leftToRight;
            
            levels.push_back(levelI);
        }

        return levels;
    }

    // todo: solve the problem using the iterative algorithm
    vector<vector<int>> zigzagLevelOrderV2(TreeNode* root)
    {
        vector<vector<int>> levels;

        return levels;
    }

    bool Test()
    {
        TreeNode t15(15);
        TreeNode t7(7);
        TreeNode t20(20);
        TreeNode t9(9);
        TreeNode t3(3);
        TreeNode t1(1);
        TreeNode t2(2);
        TreeNode t4(4);
        TreeNode t5(5);

        t20.left = &t15, t20.right = &t7;
        t3.left = &t9, t3.right = &t20;

        vector<vector<int>> expected =
        {
            { 3 },
            { 20, 9 },
            { 15, 7 }
        };

        vector<vector<int>> actual = zigzagLevelOrder(&t3);

        assert(Utils::equalVectorVector<int>(expected, actual) == true);

        t1.left = &t2, t1.right = &t3;
        t2.left = &t4, t2.right = NULL;
        t3.left = NULL, t3.right = &t5;
        t4.left = NULL, t4.right = NULL;
        t5.left = NULL, t5.right = NULL;

        expected = 
        {
            {1},
            {3, 2},
            {4, 5}
        };

        actual = zigzagLevelOrder(&t1);

        assert(Utils::equalVectorVector<int>(expected, actual) == true);

        return true;
    }
};