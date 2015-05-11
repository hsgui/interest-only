#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"

using namespace std;

class MaximumDepthOfBinaryTree
{
public:
	int maxDepth(TreeNode* root)
	{
		int maxDep = 1;
		if (root == NULL)
		{
			maxDep = 0;
		}
		else if (root->left == NULL && root->right == NULL)
		{
			maxDep = 1;
		}
		else
		{
			int leftMax = maxDepth(root->left);
			int rightMax = maxDepth(root->right);
			maxDep = max(leftMax, rightMax) + 1;
		}
		return maxDep;
	}

	// todo: solve it using imperative algorithm
	int maxDepthV2(TreeNode* root)
	{
		int maxDep = 0;

		return maxDep;
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

		int expected = 3;
		int actual = maxDepth(&t3);

		assert(expected == actual);

		return true;
	}
};