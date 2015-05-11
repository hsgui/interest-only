#ifndef _SAME_TREE_H_
#define _SAME_TREE_H_

#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"

using namespace std;

class SameTree
{
public:
	// recursive algorithm
	bool isSameTree(TreeNode* p, TreeNode* q)
	{
		if (p != NULL && q != NULL)
		{
			return (p->val == q->val)
				&& isSameTree(p->left, q->left)
				&& isSameTree(p->right, q->right);
		}
		else if (p == NULL && q == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// todo: iterative algorithm
	bool isSameTreeV2(TreeNode* p, TreeNode* q)
	{
		return true;
	}

	bool Test()
	{
		TreeNode t1(1);
		TreeNode t2(2);
		TreeNode t3(3);
		TreeNode t4(4);

		t1.left = &t2, t1.right = &t3;
		t2.left = &t4;
		assert(isSameTree(&t1, &t2) == false);
		assert(isSameTree(&t1, NULL) == false);
		assert(isSameTree(NULL, NULL) == true);
		assert(isSameTree(&t1, &t1) == true);
		assert(isSameTree(&t1, &t2) == false);

		return true;
	}
};

#endif