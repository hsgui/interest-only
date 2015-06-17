#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"

using namespace std;

// https://leetcode.com/problems/invert-binary-tree/
class InvertBinaryTree
{
public:
	TreeNode* invertTree(TreeNode* root) 
	{
		if (root == NULL)
		{
			return root;
		}

		assert(root != NULL);
		TreeNode* exchange = root->left;
		root->left = root->right;
		root->right = exchange;
		invertTree(root->left);
		invertTree(root->right);

		return root;
	}

	bool Test()
	{
		TreeNode t1(1);
		TreeNode t2(2);
		TreeNode t3(3);
		TreeNode t4(4);
		TreeNode t6(6);
		TreeNode t7(7);
		TreeNode t9(9);

		t4.left = &t2, t4.right = &t7;
		t2.left = &t1, t2.right = &t3;
		t7.left = &t6, t7.right = &t9;

		TreeNode* result = invertTree(&t4);
		assert(result->left == &t7 && result->right == &t2);
		assert(t7.left == &t9 && t7.right == &t6);
		assert(t2.left == &t3 && t2.right == &t1);
		return true;
	}
};