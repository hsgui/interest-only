#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>

#include "001-TwoSum.h"
#include "005-LongestPalindromicSubstring.h"
#include "034-SearchForARange.h"
#include "075-SortColors.h"
#include "094-BinaryTreeInorderTraversal.h"
#include "100-SameTree.h"
#include "101-SymmetricTree.h"
#include "102-BinaryTreeLevelOrderTraversal.h"
#include "103-BinaryTreeZigzagLevelOrderTraversal.h"
#include "104-MaximumDepthOfBinaryTree.h"
#include "105-ConstructBinaryTreeFromPreorderInorderTraveral.h"
#include "106-ConstructBinaryTreeFromInorderPostorderTraversal.h"
#include "107-BinaryTreeLevelOrderTraversalII.h"
#include "110-BalancedBinaryTree.h"
#include "111-MinimumDepthOfBinaryTree.h"
#include "114-FlattenBinaryTreeToLinkedList.h"
#include "124-BinaryTreeMaximumPathSum.h"
#include "128-LongestConsecutiveSequence.h"
#include "143-ReorderList.h"
#include "144-BinaryTreePreorderTraversal.h"
#include "145-BinaryTreePostorderTraversal.h"
#include "146-LRUCache.h"
#include "199-BinaryTreeRightSideView.h"

using namespace std;

typedef std::function<bool ()> Tester;

// class std::_Bind<1,bool,struct std::_Pmf_wrap<bool (__thiscall ClassName::*)(void),bool,class ClassName>,class ClassName &>
void parseClassName(const string& typeName, string& className)
{
	unsigned found = typeName.rfind("class");
	if (found)
	{
		className = typeName.substr(found + 6, typeName.length() - 3 - found - 6);
	}
	else
	{
		className = typeName;
	}
}

void setupTest(shared_ptr<vector<Tester>>& tests)
{
	shared_ptr<TwoSum> s001 = make_shared<TwoSum>();
	Tester fn = bind(&TwoSum::Test, *s001);
	tests->push_back(fn);

	shared_ptr<ReorderList> s143 = make_shared<ReorderList>();
	fn = bind(&ReorderList::Test, *s143);
	tests->push_back(fn);

	shared_ptr<LRUCache> s146 = make_shared<LRUCache>(10);
	fn = bind(&LRUCache::Test, *s146);
	tests->push_back(fn);

	shared_ptr<LongestPalindromicSubstring> s005 = make_shared<LongestPalindromicSubstring>();
	fn = bind(&LongestPalindromicSubstring::Test, *s005);
	tests->push_back(fn);

	shared_ptr<SortColors> s075 = make_shared<SortColors>();
	fn = bind(&SortColors::Test, *s075);
	tests->push_back(fn);

	shared_ptr<LongestConsecutiveSequence> s128 = make_shared<LongestConsecutiveSequence>();
	fn = bind(&LongestConsecutiveSequence::Test, *s128);
	tests->push_back(fn);

	shared_ptr<SearchForARange> s034 = make_shared<SearchForARange>();
	fn = bind(&SearchForARange::Test, *s034);
	tests->push_back(fn);

	shared_ptr<BinaryTreeLevelOrderTraversal> s102 = make_shared<BinaryTreeLevelOrderTraversal>();
	fn = bind(&BinaryTreeLevelOrderTraversal::Test, *s102);
	tests->push_back(fn);

	shared_ptr<BinaryTreeLevelOrderTraversalII> s107 = make_shared<BinaryTreeLevelOrderTraversalII>();
	fn = bind(&BinaryTreeLevelOrderTraversalII::Test, *s107);
	tests->push_back(fn);

	shared_ptr<BinaryTreeZigzagLevelOrderTraversal> s103 = make_shared<BinaryTreeZigzagLevelOrderTraversal>();
	fn = bind(&BinaryTreeZigzagLevelOrderTraversal::Test, *s103);
	tests->push_back(fn);

	shared_ptr<MaximumDepthOfBinaryTree> s104 = make_shared<MaximumDepthOfBinaryTree>();
	fn = bind(&MaximumDepthOfBinaryTree::Test, *s104);
	tests->push_back(fn);

	shared_ptr<SameTree> s100 = make_shared<SameTree>();
	fn = bind(&SameTree::Test, *s100);
	tests->push_back(fn);

	shared_ptr<ConstructBinaryTreeFromPreorderInorderTraversal> s105 = make_shared<ConstructBinaryTreeFromPreorderInorderTraversal>();
	fn = bind(&ConstructBinaryTreeFromPreorderInorderTraversal::Test, *s105);
	tests->push_back(fn);

	shared_ptr<ConstructBinaryTreeFromInorderPostorderTraversal> s106 = make_shared<ConstructBinaryTreeFromInorderPostorderTraversal>();
	fn = bind(&ConstructBinaryTreeFromInorderPostorderTraversal::Test, *s106);
	tests->push_back(fn);

	shared_ptr<SymmetricTree> s101 = make_shared<SymmetricTree>();
	fn = bind(&SymmetricTree::Test, *s101);
	tests->push_back(fn);

	shared_ptr<BalancedBinaryTree> s110 = make_shared<BalancedBinaryTree>();
	fn = bind(&BalancedBinaryTree::Test, *s110);
	tests->push_back(fn);

	shared_ptr<MinimumDepthOfBinaryTree> s111 = make_shared<MinimumDepthOfBinaryTree>();
	fn = bind(&MinimumDepthOfBinaryTree::Test, *s111);
	tests->push_back(fn);

	shared_ptr<BinaryTreeInorderTraversal> s094 = make_shared<BinaryTreeInorderTraversal>();
	fn = bind(&BinaryTreeInorderTraversal::Test, *s094);
	tests->push_back(fn);

	shared_ptr<BinaryTreePreorderTraversal> s144 = make_shared<BinaryTreePreorderTraversal>();
	fn = bind(&BinaryTreePreorderTraversal::Test, *s144);
	tests->push_back(fn);

	shared_ptr<BinaryTreePostorderTraversal> s145 = make_shared<BinaryTreePostorderTraversal>();
	fn = bind(&BinaryTreePostorderTraversal::Test, *s145);
	tests->push_back(fn);

	shared_ptr<BinaryTreeRightSideView> s199 = make_shared<BinaryTreeRightSideView>();
	fn = bind(&BinaryTreeRightSideView::Test, *s199);
	tests->push_back(fn);

	shared_ptr<FlattenBinaryTreeToLinkedList> s114 = make_shared<FlattenBinaryTreeToLinkedList>();
	fn = bind(&FlattenBinaryTreeToLinkedList::Test, *s114);
	tests->push_back(fn);

	shared_ptr<BinaryTreeMaximumPathSum> s124 = make_shared<BinaryTreeMaximumPathSum>();
	fn = bind(&BinaryTreeMaximumPathSum::Test, *s124);
	tests->push_back(fn);
}

void runTest(shared_ptr<vector<Tester>>& tests)
{
	for (auto it = tests->begin(); it != tests->end(); ++it)
	{
		Tester tester = (*it);
		tester();
		const type_info& type = tester.target_type();
		string typeName(type.name());
		string className;
		parseClassName(typeName, className);
		cout << className << " test successful" << endl;
	}
}

int main()
{
	shared_ptr<vector<Tester>> allTests = make_shared<vector<Tester>>();
	
	setupTest(allTests);
	runTest(allTests);
	
	printf("I have solved %d problems!\n", allTests->size());

	system("pause");
	return 0;
}