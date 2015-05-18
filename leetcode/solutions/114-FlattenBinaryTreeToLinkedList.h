#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"
#include "100-SameTree.h"

using namespace std;

// https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
class FlattenBinaryTreeToLinkedList{
public:
	// we should change the left field of TreeNode to NULL!!!
	void flatten(TreeNode* root)
	{
		flattenWithTail(root);
	}

	TreeNode* flattenWithTail(TreeNode* head)
	{
		if (head == NULL)
		{
			return NULL;
		}
		TreeNode* linkTail;
		if (head->left == NULL && head->right == NULL)
		{
			linkTail = head;
		}
		else if (head->left == NULL && head->right != NULL)
		{
			TreeNode* tail = flattenWithTail(head->right);
			linkTail = tail;
		}
		else if (head->left != NULL && head->right == NULL)
		{
			TreeNode* tail = flattenWithTail(head->left);
			head->right = head->left;
			linkTail = tail;
		}
		else
		{
			TreeNode* leftTreeRoot = head->left;
			TreeNode* rightTreeRoot = head->right;
			TreeNode* leftTail = flattenWithTail(leftTreeRoot);
			TreeNode* rightTail = flattenWithTail(rightTreeRoot);

			head->right = leftTreeRoot;
			leftTail->right = rightTreeRoot;

			linkTail = rightTail;
		}
		head->left = NULL;
		return linkTail;
	}

	bool Test()
	{
		TreeNode t1(1);
		TreeNode t2(2);
		TreeNode t3(3);
		TreeNode t4(4);
		TreeNode t5(5);
		TreeNode t6(6);

		t1.left = &t2, t1.right = &t5;
		t2.left = &t3, t2.right = &t4;
		t5.right = &t6;

		flatten(&t1);

		TreeNode t1_1(1);
		TreeNode t2_1(2);
		TreeNode t3_1(3);
		TreeNode t4_1(4);
		TreeNode t5_1(5);
		TreeNode t6_1(6);

		t1_1.right = &t2_1;
		t2_1.right = &t3_1;
		t3_1.right = &t4_1;
		t4_1.right = &t5_1;
		t5_1.right = &t6_1;

		SameTree sameTree;
		assert(sameTree.isSameTree(&t1, &t1_1));

		TreeNode t0(0);
		flatten(&t0);

		TreeNode t0_1(0);
		assert(sameTree.isSameTree(&t0_1, &t0));

		t1.left = &t2, t1.right = NULL;
		t2.left = &t3, t2.right = NULL;
		t3.left = NULL, t3.right = NULL;
		flatten(&t1);

		t1_1.left = NULL, t1_1.right = &t2_1;
		t2_1.left = NULL, t2_1.right = &t3_1;
		t3_1.left = NULL, t3_1.right = NULL;
		assert(sameTree.isSameTree(&t1, &t1_1));
		return true;
	}
};