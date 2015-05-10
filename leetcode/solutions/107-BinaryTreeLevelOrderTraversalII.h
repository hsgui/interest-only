#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"
#include "Utils.h"

using namespace std;

class BinaryTreeLevelOrderTraversalII
{
public:
	// recursive method
	vector<vector<int>> levelOrderBottom(TreeNode* root) 
	{
		vector<vector<int>> levels;

		if (root == NULL)
		{
			return levels;
		}

		vector<vector<int>> leftLevel;
		vector<vector<int>> rightLevel;
		if (root->left != NULL)
		{
			leftLevel = levelOrderBottom(root->left);
		}
		if (root->right != NULL)
		{
			rightLevel = levelOrderBottom(root->right);
		}

		int maxChildrenLevel = max(leftLevel.size(), rightLevel.size());
		for (int i = maxChildrenLevel; i > 0; --i)
		{
			vector<int> levelI;
			if (leftLevel.size() >= i)
			{
				levelI.insert(levelI.begin(), leftLevel[leftLevel.size() - i].begin(), 
					leftLevel[leftLevel.size() - i].end());
			}
			if (rightLevel.size() >= i)
			{
				levelI.insert(levelI.end(), rightLevel[rightLevel.size() - i].begin(), 
					rightLevel[rightLevel.size() - i].end());
			}
			levels.push_back(levelI);
		}

		vector<int> head;
		head.push_back(root->val);
		levels.push_back(head);

		return levels;
	}

	// not recursive method
	vector<vector<int>> levelOrderBottomV2(TreeNode* root)
	{
		vector<vector<int>> levels;

		return levels;
	}

	bool Test()
	{
		TreeNode t15(15);
		TreeNode t7(7);
		TreeNode t20(20);
		TreeNode t9(9);
		TreeNode t3(3);

		t20.left = &t15, t20.right = &t7;
		t3.left = &t9, t3.right = &t20;

		vector<vector<int>> expected =
		{
			{ 15, 7 },
			{ 9, 20 },
			{ 3 }
		};

		vector<vector<int>> actual = levelOrderBottom(&t3);

		assert(Utils::equalVectorVector<int>(expected, actual) == true);

		return true;
	}
};