#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"

using namespace std;

// https://leetcode.com/problems/binary-tree-maximum-path-sum/
class BinaryTreeMaximumPathSum{
public:
	int maxPathSum(TreeNode* root)
	{
		int maxSumUtillRoot = 0;
		return maxPathSumInThisTree(root, maxSumUtillRoot);
	}

	int maxPathSumInThisTree(TreeNode* root, int& maxSumUtillRoot)
	{
		int maxSum = 0;
		if (root == NULL)
		{
			maxSumUtillRoot = 0;
			return maxSum;
		}
		if (root->left == NULL && root->right == NULL)
		{
			maxSumUtillRoot = root->val;
			return root->val;
		}

		int leftMaxSum = 0, rightMaxSum = 0;
		int maxSumUtillLeftRoot, maxSumUtillRightRoot = 0;
		if (root->left != NULL && root->right != NULL)
		{
			leftMaxSum = maxPathSumInThisTree(root->left, maxSumUtillLeftRoot);
			rightMaxSum = maxPathSumInThisTree(root->right, maxSumUtillRightRoot);

			maxSumUtillRoot = max(root->val, maxSumUtillLeftRoot + root->val);
			maxSumUtillRoot = max(maxSumUtillRoot, maxSumUtillRightRoot + root->val);

			maxSum = max(root->val, root->val + maxSumUtillLeftRoot);
			maxSum = max(maxSum, maxSum + maxSumUtillRightRoot);
			maxSum = max(maxSum, leftMaxSum);
			maxSum = max(maxSum, rightMaxSum);
		}
		else if (root->left != NULL && root->right == NULL)
		{
			leftMaxSum = maxPathSumInThisTree(root->left, maxSumUtillLeftRoot);

			maxSumUtillRoot = max(root->val, maxSumUtillLeftRoot + root->val);

			maxSum = max(maxSumUtillRoot, leftMaxSum);
		}
		else
		{
			rightMaxSum = maxPathSumInThisTree(root->right, maxSumUtillRightRoot);
			maxSumUtillRoot = max(root->val, maxSumUtillRightRoot + root->val);

			maxSum = max(maxSumUtillRoot, rightMaxSum);
		}

		return maxSum;
	}

	bool Test()
	{
		TreeNode t1(1);
		TreeNode t2(2);
		TreeNode t3(3);

		t1.left = &t2, t1.right = &t3;
		int expected = 6;
		int actual = maxPathSum(&t1);
		assert(expected == actual);

		TreeNode t3_1(-3);
		expected = -3;
		actual = maxPathSum(&t3_1);
		assert(expected == actual);

		TreeNode t2_1(2);
		TreeNode t1_1(-1);
		t2_1.left = &t1_1;
		expected = 2;
		actual = maxPathSum(&t2_1);
		assert(expected == actual);

		TreeNode t2_2(-2);
		t2_2.left = &t1_1;
		expected = -1;
		actual = maxPathSum(&t2_2);
		assert(expected == actual);

		t2_2.left = NULL, t2_2.right = &t3_1;
		t3_1.left = NULL, t3_1.right = NULL;
		expected = -2;
		actual = maxPathSum(&t2_2);
		assert(expected == actual);

		return true;
	}
};