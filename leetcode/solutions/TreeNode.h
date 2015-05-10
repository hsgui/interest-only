#ifndef _TREE_NODE_H_
#define _TREE_NODE_H_

#include <algorithm>

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

#endif