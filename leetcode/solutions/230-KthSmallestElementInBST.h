#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"

using namespace std;

// https://leetcode.com/problems/kth-smallest-element-in-a-bst/
class KthSmallestElementInBST
{
public:
	struct Result
	{
		bool isFound;
		int countOrValue;
	};

	int kthSmallest(TreeNode* root, int k) 
	{
		Result r = findKthSmallest(root, k);

		assert(r.isFound);
		return r.countOrValue;
	}

	Result findKthSmallest(TreeNode* root, int k)
	{
		Result result;
		if (root == nullptr)
		{
			result.isFound = false;
			result.countOrValue = 0;
			return result;
		}

		result = findKthSmallest(root->left, k);
		if (!result.isFound)
		{
			assert(result.countOrValue < k);
			if (result.countOrValue == k - 1)
			{
				result.isFound = true;
				result.countOrValue = root->val;
			}
			else
			{
				Result rightResult = findKthSmallest(root->right, k - 1 - result.countOrValue);
				if (!rightResult.isFound)
				{
					result.countOrValue += 1 + rightResult.countOrValue;
				}
				else
				{
					result = rightResult;
				}
			}
		}
		
		return result;
	}

	bool Test()
	{
		TreeNode t1(1);
		TreeNode t2(2);
		TreeNode t3(3);
		TreeNode t4(4);
		TreeNode t5(5);

		t3.left = &t2, t3.right = &t4;
		t2.left = &t1;
		t4.right = &t5;

		TreeNode* root = &t3;
		assert(kthSmallest(root, 1) == 1);
		assert(kthSmallest(root, 2) == 2);
		assert(kthSmallest(root, 3) == 3);
		assert(kthSmallest(root, 4) == 4);
		assert(kthSmallest(root, 5) == 5);
		return true;
	}
};