#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"

using namespace std;

// https://leetcode.com/problems/binary-search-tree-iterator/
class BSTIterator {
public:
	BSTIterator(): 
		m_root(NULL),
		m_current(NULL){}

	BSTIterator(TreeNode *root) 
	{
		m_root = root;
		m_current = root;
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		return m_current != NULL;
	}

	/** @return the next smallest number */
	int next() {
		return 0;
	}

	bool Test()
	{
		TreeNode* root = NULL;
		BSTIterator it = BSTIterator(root);
		while (it.hasNext());

		return true;
	}

private:
	TreeNode* m_root;
	TreeNode* m_current;
};