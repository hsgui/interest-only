#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"

using namespace std;

// https://leetcode.com/problems/minimum-depth-of-binary-tree/

class MinimumDepthOfBinaryTree
{
public:
	int minDepth(TreeNode* root) 
	{
		int minDep = 0;
		if (root == NULL)
		{
			minDep = 0;
		}
		else if (root->left == NULL && root->right == NULL)
		{
			minDep = 1;
		}
		else
		{
			if (root->left == NULL)
			{
				minDep = minDepth(root->right) + 1;
			}
			else if (root->right == NULL)
			{
				minDep = minDepth(root->left) + 1;
			}
			else
			{
				minDep = min(minDepth(root->left), minDepth(root->right)) + 1;
			}
		}
		return minDep;
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
		TreeNode t8(8);

		t1.left = &t2, t1.right = &t3;
		t2.left = &t4, t2.right = &t5;
		t4.left = &t6;

		int expected = 2;
		int actual = minDepth(&t1);
		assert(expected == actual);

		t3.left = &t7;
		expected = 3;
		actual = minDepth(&t1);
		assert(expected == actual);

		t3.right = &t8;
		expected = 3;
		actual = minDepth(&t1);
		assert(expected == actual);

		return true;
	}
};