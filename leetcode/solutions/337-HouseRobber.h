#pragma once

#include "TreeNode.h"
#include <tuple>

using namespace std;

// https://leetcode.com/problems/house-robber-iii/
class HourseRobberIII
{
public:
    pair<int, int> postTravel(TreeNode* root)
    {
        pair<int, int> robSum(0, 0);
        if (root != nullptr)
        {
            pair<int, int> leftRobSum = postTravel(root->left);
            pair<int, int> rightRobSum = postTravel(root->right);
            int notRobRoot = leftRobSum.first + rightRobSum.first;
            int robRoot = root->val + leftRobSum.second + rightRobSum.second;
            robSum.first = max(notRobRoot, robRoot);
            robSum.second = notRobRoot;
        }

        return robSum;
    }

    int rob(TreeNode* root)
    {
        return postTravel(root).first;
    }
};