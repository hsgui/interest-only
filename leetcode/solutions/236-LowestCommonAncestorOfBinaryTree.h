#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>

#include "TreeNode.h"

// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
class LowestCommonAncestorOfBinaryTree
{
public:
	// assumption: p & q must in root
	// so the common ancestor must exist
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == nullptr || root == p || root == q)
		{
			return root;
		}

		TreeNode* left = lowestCommonAncestor(root->left, p, q);
		TreeNode* right = lowestCommonAncestor(root->right, p, q);

		if (left != nullptr && right != nullptr)
		{
			return root;
		}
		
		return left != nullptr ? left : right;
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
		t4.left = &t6;

		TreeNode* root = &t1;
		TreeNode* p = &t6;
		TreeNode* q = &t5;
		assert(lowestCommonAncestor(root, p, q) == &t2);

		return true;
	}
};