#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"
#include "100-SameTree.h"

using namespace std;

class UniqueBinarySearchTreesII{
public:
	vector<TreeNode*> generateTrees(int n)
	{
		vector<vector<TreeNode*>> trees;
		generateTreesV2(trees, n);

		return trees[n];
	}

	// this algorithm will time out
	void generateTrees(vector<TreeNode*>& tree, int start, int end)
	{
		if (start > end)
		{
			tree.push_back(NULL);
		}
		else if (start == end)
		{
			TreeNode* node = new TreeNode(start);
			tree.push_back(node);
		}
		else if (start < end)
		{
			for (int root = start; root <= end; ++root)
			{
				vector<TreeNode*> leftTrees;
				vector<TreeNode*> rightTrees;
				generateTrees(leftTrees, 1, root - 1);
				generateTrees(rightTrees, root + 1, end);
				for (int i = 0; i < leftTrees.size(); ++i)
				{
					for (int j = 0; j < rightTrees.size(); ++j)
					{
						TreeNode* rootNode = new TreeNode(root);
						rootNode->left = leftTrees[i];
						rootNode->right = rightTrees[j];
						tree.push_back(rootNode);
					}
				}
			}
		}
		return;
	}

	// this algorithm will cost memory
	void generateTreesV2(vector<vector<TreeNode*>>& trees, int n)
	{
		if (n >= 0)
		{
			vector<TreeNode*> tree;
			tree.push_back(NULL);
			trees.push_back(tree);
		}
		if (n >= 1)
		{
			vector<TreeNode*> tree;
			TreeNode* node = new TreeNode(1);
			tree.push_back(node);
			trees.push_back(tree);
		}
		if (n >= 2)
		{
			for (int subN = 2; subN <= n; ++subN)
			{
				vector<TreeNode*> tree;
				for (int root = 1; root <= subN; ++root)
				{
					int leftN = root - 1;
					int rightN = subN - root;
					for (int i = 0; i < trees[leftN].size(); ++i)
					{
						for (int j = 0; j < trees[rightN].size(); ++j)
						{
							TreeNode* node = new TreeNode(root);
							DeepCopyAndUpdate(trees[leftN][i], node->left, 0);
							DeepCopyAndUpdate(trees[rightN][j], node->right, root);
							tree.push_back(node);
						}
					}
				}
				trees.push_back(tree);
			}
		}
	}

	void DeepCopyAndUpdate(const TreeNode* source, TreeNode* & dest, int delta)
	{
		if (source == NULL)
		{
			dest = NULL;
			return;
		}
		if (source != NULL)
		{
			dest = new TreeNode(source->val + delta);
			DeepCopyAndUpdate(source->left, dest->left, delta);
			DeepCopyAndUpdate(source->right, dest->right, delta);
		}
	}

	bool Test()
	{
		TreeNode t1(1);

		vector<TreeNode*> trees = generateTrees(1);
		generateTrees(6);
		assert(trees.size() == 1);
		assert(trees[0]->val == 1);
		return true;
	}
};