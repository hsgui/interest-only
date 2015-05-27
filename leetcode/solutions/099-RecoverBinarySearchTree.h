#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"

using namespace std;

class RecoverBinarySearchTree
{
public:

	// http://en.wikipedia.org/wiki/Threaded_binary_tree
	// in-order traversal
	// think about the ordered array, transfer the two elements of the array
	void recoverTree(TreeNode* root)
	{
		TreeNode* current = root;
		TreeNode* parent = NULL;
		TreeNode* mistakeNode1 = NULL, *mistakeNode2 = NULL;
		bool found = false;
		while (current != NULL)
		{
			if (current->left == NULL)
			{
				if (parent != NULL && parent->val > current->val)
				{
					if (!found)
					{
						// found the fist mistake node.
						mistakeNode1 = parent;
						found = true;
					}
					// the second mistake node.
					mistakeNode2 = current;
				}
				// left tree is empty, visit the root and then right
				parent = current;
				current = current->right;
			}
			else
			{
				// visit the left tree, but we need get the predecessor of the current node first.
				// then we could visit back to the current node.
				TreeNode* predecessor = current->left;
				for (; predecessor->right != NULL && predecessor->right != current; predecessor = predecessor->right);

				if (predecessor->right == NULL)
				{
					// record the ancestor to be current
					predecessor->right = current;
					current = current->left;
				}
				else
				{
					if (parent != NULL && parent->val > current->val)
					{
						if (!found)
						{
							mistakeNode1 = parent;
							found = true;
						}
						mistakeNode2 = current;
					}
					// revisit the current again, then the left tree has been visited over
					// then to visit the current node and the right tree
					// restore the binary tree
					assert(predecessor->right == current);
					predecessor->right = NULL;
					parent = current;
					current = current->right;
				}
			}
		}
		if (mistakeNode1 != NULL && mistakeNode2 != NULL)
		{
			swap(mistakeNode1->val, mistakeNode2->val);
		}
	}

	bool Test()
	{
		TreeNode t1(1);
		TreeNode t2(2);
		t1.left = &t2;
		TreeNode* root = &t1;
		recoverTree(root);
		assert((root->val == 2) && (root->left->val == 1));
		return true;
	}
};