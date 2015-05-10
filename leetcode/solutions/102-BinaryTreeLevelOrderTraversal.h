#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

using namespace std;

class BinaryTreeLevelOrderTraversal{
public:
	struct TreeNode
	{
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int x) : val(x), left(NULL), right(NULL){}
	};

	// the recursive method is not that efficient
	vector<vector<int>> levelOrder(TreeNode* root)
	{
		vector<vector<int>> levels;
		if (root == NULL)
		{
			return levels;
		}
		vector<int> head;
		head.push_back(root->val);
		levels.push_back(head);

		vector<vector<int>> leftLevel;
		vector<vector<int>> rightLevel;
		if (root->left != NULL)
		{
			leftLevel = levelOrder(root->left);
		}
		if (root->right != NULL)
		{
			rightLevel = levelOrder(root->right);
		}

		int maxChildrenLevel = max(leftLevel.size(), rightLevel.size());
		for (int i = 0; i < maxChildrenLevel; ++i)
		{
			vector<int> levelI;
			if (i < leftLevel.size())
			{
				levelI.insert(levelI.begin(), leftLevel[i].begin(), leftLevel[i].end());
			}
			if (i < rightLevel.size())
			{
				levelI.insert(levelI.end(), rightLevel[i].begin(), rightLevel[i].end());
			}
			levels.push_back(levelI);
		}

		return levels;
	}

	// todo: the non-recursive method
	vector<vector<int>> levelOrderV2(TreeNode* root)
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
			{3},
			{9, 20},
			{15, 7}
		};

		vector<vector<int>> actual = levelOrder(&t3);
		assert(equalVectorVector<int>(expected, actual) == true);
		
		return true;
	}

	template<typename T> bool equalVectorVector(vector<vector<T>> a, vector<vector<T>> b)
	{
		if (a.size() != b.size())
		{
			return false;
		}
		for (int i = 0; i < a.size(); i++)
		{
			if (!equal(a[i].begin(), a[i].end(), b[i].begin()))
			{
				return false;
			}
		}
		return true;
	}
};