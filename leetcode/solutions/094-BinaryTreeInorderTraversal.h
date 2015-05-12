#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"

using namespace std;

class BinaryTreeInorderTraversal
{
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> inorder;
		if (root == NULL)
		{
			return inorder;
		}

		TreeNode* childRoot = root;
		vector<TreeNode*> rootStack;
		rootStack.push_back(childRoot);
		while (!rootStack.empty())
		{
			childRoot = rootStack.back();
			if (childRoot->left != NULL)
			{
				rootStack.push_back(childRoot->left);
			}
			else
			{
				inorder.push_back(childRoot->val);
				rootStack.pop_back();
				if (childRoot->right != NULL)
				{
					rootStack.push_back(childRoot->right);
				}
			}
		}

		return inorder;
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

		vector<int> inorder = { 4, 2, 5, 1, 6, 3, 7 };

		vector<int> actual = inorderTraversal(&t1);
		assert(equal(actual.begin(), actual.end(), inorder.begin()));

		return true;
	}
};