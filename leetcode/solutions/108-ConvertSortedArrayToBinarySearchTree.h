#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"

using namespace std;

class ConvertSortedArrayToBinarySearchTree
{
public:
	// https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
	TreeNode* sortedArrayToBST(vector<int>& nums) 
	{
		return sortedArrayToBST(nums, 0, nums.size() - 1);
	}

	TreeNode* sortedArrayToBST(vector<int>& nums, int start, int end)
	{
		if (start > end)
		{
			return NULL;
		}
		else if (start == end)
		{
			return new TreeNode(nums[start]);
		}
		else
		{
			// middle >= start and middle < end;
			int middle = (end - start) / 2 + start;
			TreeNode* root = new TreeNode(nums[middle]);
			root->left = sortedArrayToBST(nums, start, middle - 1);
			root->right = sortedArrayToBST(nums, middle + 1, end);
			return root;
		}
	}

	bool Test()
	{
		vector<int> nums = { 1, 2, 3 };
		TreeNode* root = sortedArrayToBST(nums);
		assert(root->val == 2 && root->left->val == 1 && root->right->val == 3);

		nums = {};
		root = sortedArrayToBST(nums);
		assert(root == NULL);

		nums = { 1, 3 };
		root = sortedArrayToBST(nums);
		assert(root->val == 1 && root->right->val == 3);

		return true;
	}
};