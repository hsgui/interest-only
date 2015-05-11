#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"
#include "100-SameTree.h"

using namespace std;

class ConstructBinaryTreeFromPreorderInorderTraversal
{
public:
	TreeNode* buildTree(vector<int>& preorder, int preStart, int preEnd, vector<int>& inorder, int inStart, int inEnd)
	{
		if (preEnd < preStart)
		{
			return NULL;
		}
		int head = preorder[preStart];
		TreeNode* root = new TreeNode(head);
		if (preStart == preEnd)
		{
			return root;
		}

		int leftLength = 0;
		for (leftLength = 0; leftLength + inStart <= inEnd && inorder[leftLength + inStart] != head; ++leftLength);

		root->left = buildTree(preorder, preStart + 1, preStart + leftLength, inorder, inStart, inStart + leftLength - 1);
		root->right = buildTree(preorder, preStart + leftLength + 1, preEnd, inorder, inStart + leftLength + 1, inEnd);

		return root;
	}

	// recursive algorithm
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
	{
		return buildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
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
		t3.left = &t6, t3.right = &t7;
		vector<int> preorder = { 1, 2, 4, 5, 3, 6, 7 };
		vector<int> inorder = { 4, 2, 5, 1, 6, 3, 7 };

		TreeNode* actual = buildTree(preorder, inorder);
		SameTree sameTree;
		assert(sameTree.isSameTree(actual, &t1) == true);

		return true;
	}
};