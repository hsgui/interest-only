#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"

using namespace std;

// https://leetcode.com/forums/viewtopic.php?f=4&t=215
class CountCompleteTreeNodes
{
public:
	int getTreeDept(TreeNode* root)
	{
		// search if the left-most is empty
		int level = 0;
		while (root != nullptr)
		{
			level++;
			root = root->left;
		}
		return level;
	}

	int countNodes(TreeNode* root) 
	{
		int count = 0;
		int treeLevel = getTreeDept(root);
		int currentLevel = 1;
		TreeNode* currentRoot = root;
		// binary search
		while (currentRoot != nullptr)
		{
			if (getTreeDept(currentRoot->right) + currentLevel == treeLevel)
			{
				// left tree is complete, count of left tree + currentRoot
				count += 1 << (treeLevel - currentLevel);
				currentRoot = currentRoot->right;
			}
			else
			{
				// right tree is complete, but with level of treeLevel - currentLevel -1
				count += 1 << (treeLevel - currentLevel - 1);
				currentRoot = currentRoot->left;
			}
			currentLevel++;
		}
		return count;
	}

	bool Test()
	{
		TreeNode t1(1);
		TreeNode t2(2);
		TreeNode t3(3);
		TreeNode t4(4);
		TreeNode t5(5);

		t1.left = &t2, t1.right = &t3;
		t2.left = &t4, t2.right = &t5;;
		int expected = 5;
		assert(expected == countNodes(&t1));

		expected = 3;
		assert(expected = countNodes(&t2));

		expected = 1;
		assert(expected == countNodes(&t3));

		expected = 0;
		assert(expected == countNodes(nullptr));
		return true;
	}
};