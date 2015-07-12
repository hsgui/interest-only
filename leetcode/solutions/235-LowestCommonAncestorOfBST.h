#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>

#include "TreeNode.h"

// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
class LowestCommonAncestorOfBST
{
public:
	// this is a binary search tree
	// assumption: p and q are in the tree!
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == nullptr)
		{
			return nullptr;
		}
		if (root->val == p->val || root->val == q->val)
		{
			return root;
		}
		if (root->val < p->val && root->val < q->val)
		{
			return lowestCommonAncestor(root->right, p, q);
		}
		if (root->val > p->val && root->val > q->val)
		{
			return lowestCommonAncestor(root->left, p, q);
		}
		if ((root->val > p->val && root->val < q->val)
			|| (root->val < p->val && root->val > q->val))
		{
			return root;
		}
		return nullptr;
	}

	bool Test()
	{
		TreeNode t6(6);
		TreeNode t2(2);
		TreeNode t0(0);
		TreeNode t8(8);
		TreeNode t4(4);
		TreeNode t3(3);
		TreeNode t5(5);
		TreeNode t7(7);
		TreeNode t9(9);

		t6.left = &t2, t6.right = &t8;
		t2.left = &t0, t2.right = &t4;
		t4.left = &t3, t4.right = &t5;
		t8.left = &t7, t8.right = &t9;

		TreeNode* ancestor = nullptr;
		TreeNode* root = &t6;
		ancestor = lowestCommonAncestor(root, &t2, &t8);
		assert(ancestor->val == 6);

		ancestor = lowestCommonAncestor(root, &t2, &t4);
		assert(ancestor->val == 2);
		return true;
	}
};