#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>

#include "UnitTest-Utils.h"
#include "001-TwoSum.h"
#include "002-AddTwoNumbers.h"
#include "005-LongestPalindromicSubstring.h"
#include "019-RemoveNthNodeFromEndOfList.h"
#include "034-SearchForARange.h"
#include "053-MaximumSubarray.h"
#include "074-Search2DMatrix.h"
#include "075-SortColors.h"
#include "076-MinimumWindowSubstring.h"
#include "081-SearchInRotatedSortedArray.h"
#include "094-BinaryTreeInorderTraversal.h"
#include "095-UniqueBinarySearchTreesII.h"
#include "096-UniqueBinarySearchTrees.h"
#include "098-ValidateBinarySearchTree.h"
#include "099-RecoverBinarySearchTree.h"
#include "100-SameTree.h"
#include "101-SymmetricTree.h"
#include "102-BinaryTreeLevelOrderTraversal.h"
#include "103-BinaryTreeZigzagLevelOrderTraversal.h"
#include "104-MaximumDepthOfBinaryTree.h"
#include "105-ConstructBinaryTreeFromPreorderInorderTraveral.h"
#include "106-ConstructBinaryTreeFromInorderPostorderTraversal.h"
#include "107-BinaryTreeLevelOrderTraversalII.h"
#include "108-ConvertSortedArrayToBinarySearchTree.h"
#include "109-ConvertSortedListToBinarySearchTree.h"
#include "110-BalancedBinaryTree.h"
#include "111-MinimumDepthOfBinaryTree.h"
#include "114-FlattenBinaryTreeToLinkedList.h"
#include "121-BestTimeToBuyAndSellStock1.h"
#include "122-BestTimeToBuyAndSellStock2.h"
#include "124-BinaryTreeMaximumPathSum.h"
#include "128-LongestConsecutiveSequence.h"
#include "133-CloneGraph.h"
#include "138-CopyWithRandomPointer.h"
#include "143-ReorderList.h"
#include "144-BinaryTreePreorderTraversal.h"
#include "145-BinaryTreePostorderTraversal.h"
#include "146-LRUCache.h"
#include "147-InsertionSortList.h"
#include "148-SortList.h"
#include "152-MaximumProductSubarray.h"
#include "153-FindMinimumInRotatedSortedArray.h"
#include "154-FindMinimumInRotatedSortedArrayII.h"
#include "160-IntersectionOfTwoLinkedLists.h"
#include "173-BinarySearchTreeIterator.h"
#include "199-BinaryTreeRightSideView.h"
#include "203-RemoveLinkedListElements.h"
#include "206-ReverseLinkedList.h"
#include "208-Trie.h"
#include "209-MinimumSizeSubarraySum.h"
#include "215-KthLargestElementInArray.h"
#include "221-MaximalSquare.h"
#include "222-CountCompleteTreeNodes.h"
#include "223-RectangleArea.h"
#include "224-BasicCalculator.h"
#include "225-ImplementStackUsingQueues.h"
#include "226-InvertBinaryTree.h"
#include "227-BasicCalculatorII.h"
#include "228-SummaryRanges.h"
#include "230-KthSmallestElementInBST.h"
#include "231-PowerOfTwo.h"
#include "234-PalindromeLinkedList.h"
#include "235-LowestCommonAncestorOfBST.h"
#include "236-LowestCommonAncestorOfBinaryTree.h"
#include "237-DeleteNodeInLinkedList.h"
#include "238-ProductOfArrayExceptSelf.h"
#include "239-SlidingWindowMaximum.h"
#include "240-Search2DMatrixII.h"
#include "242-ValidAnagram.h"

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
	Tester fn;

	shared_ptr<BestTimeToBuyAndSellStock2> s122 = make_shared<BestTimeToBuyAndSellStock2>();
	fn = bind(&BestTimeToBuyAndSellStock2::Test, *s122);
	tests->push_back(fn);

	shared_ptr<BestTimeToBuyAndSellStock1> s121 = make_shared<BestTimeToBuyAndSellStock1>();
	fn = bind(&BestTimeToBuyAndSellStock1::Test, *s121);
	tests->push_back(fn);

	shared_ptr<ValidAnagram> s242 = make_shared<ValidAnagram>();
	fn = bind(&ValidAnagram::Test, *s242);
	tests->push_back(fn);

	shared_ptr<AddTwoNumbers> s002 = make_shared<AddTwoNumbers>();
	fn = bind(&AddTwoNumbers::Test, *s002);
	tests->push_back(fn);

	shared_ptr<Search2DMatrixII> s240 = make_shared<Search2DMatrixII>();
	fn = bind(&Search2DMatrixII::Test, *s240);
	tests->push_back(fn);

	shared_ptr<Search2DMatrix> s074 = make_shared<Search2DMatrix>();
	fn = bind(&Search2DMatrix::Test, *s074);
	tests->push_back(fn);

	shared_ptr<SlidingWindowMaximum> s239 = make_shared<SlidingWindowMaximum>();
	fn = bind(&SlidingWindowMaximum::Test, *s239);
	tests->push_back(fn);

	shared_ptr<CloneGraph> s133 = make_shared<CloneGraph>();
	fn = bind(&CloneGraph::Test, *s133);
	tests->push_back(fn);

	shared_ptr<CopyWithRandomPointer> s138 = make_shared<CopyWithRandomPointer>();
	fn = bind(&CopyWithRandomPointer::Test, *s138);
	tests->push_back(fn);

	shared_ptr<ProductOfArrayExceptSelf> s238 = make_shared<ProductOfArrayExceptSelf>();
	fn = bind(&ProductOfArrayExceptSelf::Test, *s238);
	tests->push_back(fn);

	shared_ptr<DeleteNodeInLinkedList> s237 = make_shared<DeleteNodeInLinkedList>();
	fn = bind(&DeleteNodeInLinkedList::Test, *s237);
	tests->push_back(fn);

	shared_ptr<LowestCommonAncestorOfBinaryTree> s236 = make_shared<LowestCommonAncestorOfBinaryTree>();
	fn = bind(&LowestCommonAncestorOfBinaryTree::Test, *s236);
	tests->push_back(fn);

	shared_ptr<SearchInRotatedSortedArray> s081 = make_shared<SearchInRotatedSortedArray>();
	fn = bind(&SearchInRotatedSortedArray::Test, *s081);
	tests->push_back(fn);

	shared_ptr<FindMinimumInRotatedSortedArrayII> s154 = make_shared<FindMinimumInRotatedSortedArrayII>();
	fn = bind(&FindMinimumInRotatedSortedArrayII::Test, *s154);
	tests->push_back(fn);

	shared_ptr<FindMinimumInRotatedSortedArray> s153 = make_shared<FindMinimumInRotatedSortedArray>();
	fn = bind(&FindMinimumInRotatedSortedArray::Test, *s153);
	tests->push_back(fn);

	shared_ptr<MaximalSquare> s221 = make_shared<MaximalSquare>();
	fn = bind(&MaximalSquare::Test, *s221);
	tests->push_back(fn);

	shared_ptr<PalindromeLinkedList> s234 = make_shared<PalindromeLinkedList>();
	fn = bind(&PalindromeLinkedList::Test, *s234);
	tests->push_back(fn);

	shared_ptr<LowestCommonAncestorOfBST> s235 = make_shared<LowestCommonAncestorOfBST>();
	fn = bind(&LowestCommonAncestorOfBST::Test, *s235);
	tests->push_back(fn);

	shared_ptr<MaximumSubarray> s053 = make_shared<MaximumSubarray>();
	fn = bind(&MaximumSubarray::Test, *s053);
	tests->push_back(fn);

	shared_ptr<MinimumSizeSubarraySum> s209 = make_shared<MinimumSizeSubarraySum>();
	fn = bind(&MinimumSizeSubarraySum::Test, *s209);
	tests->push_back(fn);

	shared_ptr<MinimumWindowSubstring> s076 = make_shared<MinimumWindowSubstring>();
	fn = bind(&MinimumWindowSubstring::Test, *s076);
	tests->push_back(fn);

	shared_ptr<Trie> s208 = make_shared<Trie>();
	fn = bind(&Trie::Test, *s208);
	tests->push_back(fn);

	shared_ptr<PowerOfTwo> s231 = make_shared<PowerOfTwo>();
	fn = bind(&PowerOfTwo::Test, *s231);
	tests->push_back(fn);

	shared_ptr<KthLargestElementInArray> s215 = make_shared<KthLargestElementInArray>();
	fn = bind(&KthLargestElementInArray::Test, *s215);
	tests->push_back(fn);

	shared_ptr<CountCompleteTreeNodes> s222 = make_shared<CountCompleteTreeNodes>();
	fn = bind(&CountCompleteTreeNodes::Test, *s222);
	tests->push_back(fn);

	shared_ptr<KthSmallestElementInBST> s230 = make_shared<KthSmallestElementInBST>();
	fn = bind(&KthSmallestElementInBST::Test, *s230);
	tests->push_back(fn);

	shared_ptr<RectangleArea> s223 = make_shared<RectangleArea>();
	fn = bind(&RectangleArea::Test, *s223);
	tests->push_back(fn);

	shared_ptr<ImplementStackUsingQueues> s225 = make_shared<ImplementStackUsingQueues>();
	fn = bind(&ImplementStackUsingQueues::Test, *s225);
	tests->push_back(fn);

	shared_ptr<BasicCalculatorII> s227 = make_shared<BasicCalculatorII>();
	fn = bind(&BasicCalculatorII::Test, *s227);
	tests->push_back(fn);

	shared_ptr<SummaryRanges> s228 = make_shared<SummaryRanges>();
	fn = bind(&SummaryRanges::Test, *s228);
	tests->push_back(fn);

	shared_ptr<BasicCalculator> s224 = make_shared<BasicCalculator>();
	fn = bind(&BasicCalculator::Test, *s224);
	tests->push_back(fn);

	shared_ptr<InvertBinaryTree> s226 = make_shared<InvertBinaryTree>();
	fn = bind(&InvertBinaryTree::Test, *s226);
	tests->push_back(fn);

	shared_ptr<SortList> s148 = make_shared<SortList>();
	fn = bind(&SortList::Test, *s148);
	tests->push_back(fn);

	shared_ptr<MaximumProductSubarray> s152 = make_shared<MaximumProductSubarray>();
	fn = bind(&MaximumProductSubarray::Test, *s152);
	tests->push_back(fn);

	shared_ptr<InsertionSortList> s147 = make_shared<InsertionSortList>();
	fn = bind(&InsertionSortList::Test, *s147);
	tests->push_back(fn);

	shared_ptr<RemoveNthNodeFromEndOfList> s019 = make_shared<RemoveNthNodeFromEndOfList>();
	fn = bind(&RemoveNthNodeFromEndOfList::Test, *s019);
	tests->push_back(fn);

	shared_ptr<IntersectionOfTwoLinkedList> s160 = make_shared<IntersectionOfTwoLinkedList>();
	fn = bind(&IntersectionOfTwoLinkedList::Test, *s160);
	tests->push_back(fn);

	shared_ptr<RemoveLinkedListElements> s203 = make_shared<RemoveLinkedListElements>();
	fn = bind(&RemoveLinkedListElements::Test, *s203);
	tests->push_back(fn);

	shared_ptr<ReverseLinkedList> s206 = make_shared<ReverseLinkedList>();
	fn = bind(&ReverseLinkedList::Test, *s206);
	tests->push_back(fn);

	shared_ptr<ValidateBinarySearchTree> s098 = make_shared<ValidateBinarySearchTree>();
	fn = bind(&ValidateBinarySearchTree::Test, *s098);
	tests->push_back(fn);

	shared_ptr<BSTIterator> s173 = make_shared<BSTIterator>();
	fn = bind(&BSTIterator::Test, *s173);
	tests->push_back(fn);

	shared_ptr<ConvertSortedListToBinarySearchTree> s109 = make_shared<ConvertSortedListToBinarySearchTree>();
	fn = bind(&ConvertSortedListToBinarySearchTree::Test, *s109);
	tests->push_back(fn);

	shared_ptr<RecoverBinarySearchTree> s099 = make_shared<RecoverBinarySearchTree>();
	fn = bind(&RecoverBinarySearchTree::Test, *s099);
	tests->push_back(fn);

	shared_ptr<ConvertSortedArrayToBinarySearchTree> s108 = make_shared<ConvertSortedArrayToBinarySearchTree>();
	fn = bind(&ConvertSortedArrayToBinarySearchTree::Test, *s108);
	tests->push_back(fn);

	shared_ptr<UniqueBinarySearchTreesII> s095 = make_shared<UniqueBinarySearchTreesII>();
	fn = bind(&UniqueBinarySearchTreesII::Test, *s095);
	tests->push_back(fn);

	shared_ptr<TwoSum> s001 = make_shared<TwoSum>();
	fn = bind(&TwoSum::Test, *s001);
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

	shared_ptr<UniqueBinarySearchTrees> s096 = make_shared<UniqueBinarySearchTrees>();
	fn = bind(&UniqueBinarySearchTrees::Test, *s096);
	tests->push_back(fn);

	shared_ptr<UnitTest_Utils> unitTest_Utils = make_shared<UnitTest_Utils>();
	fn = bind(&UnitTest_Utils::Test, *unitTest_Utils);
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
	
	printf("%d problems have been solved!\n", allTests->size());

	system("pause");
	return 0;
}