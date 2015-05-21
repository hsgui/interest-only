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
		shared_ptr<vector<TreeNode*>> trees = generateTrees(1, n);

		return (*trees);
	}

	shared_ptr<vector<TreeNode*>> generateTrees(int start, int end)
	{
		shared_ptr<vector<TreeNode*>> tree = make_shared<vector<TreeNode*>>();
		if (start > end)
		{
			(*tree).push_back(NULL);
		}
		else if (start == end)
		{
			TreeNode* node = new TreeNode(start);
			(*tree).push_back(node);
		}
		else if (start < end)
		{
			for (int root = start; root <= end; ++root)
			{
				shared_ptr<vector<TreeNode*>> leftTrees = generateTrees(1, root - 1);
				shared_ptr<vector<TreeNode*>> rightTrees = generateTrees(root + 1, end);
				for (int i = 0; i < leftTrees->size(); ++i)
				{
					for (int j = 0; j < rightTrees->size(); ++j)
					{
						TreeNode* rootNode = new TreeNode(root);
						rootNode->left = leftTrees->at(i);
						rootNode->right = rightTrees->at(j);
						tree->push_back(rootNode);
					}
				}
			}
		}

		return tree;
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