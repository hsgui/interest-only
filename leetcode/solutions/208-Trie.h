#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/implement-trie-prefix-tree/
class TrieNode {
public:
	static const int ChildCount = 26;
	// Initialize your data structure here.
	TrieNode() 
	{
		m_isWord = false;
		m_isPrefix = false;
		for (int i = 0; i < ChildCount; ++i)
		{
			edges[i] = nullptr;
		}
	}

	shared_ptr<TrieNode> appendChildNode(char p_char)
	{
		int index = p_char - 'a';
		assert(index >= 0 && index <= 25);
		if (edges[index] == nullptr)
		{
			edges[index] = make_shared<TrieNode>();
		}

		return edges[index];
	}

	shared_ptr<TrieNode>& getChildNode(char p_char)
	{
		int index = p_char - 'a';
		assert(index >= 0 && index <= 25);
		return edges[index];
	}

	bool isWord() { return m_isWord; }

	bool isPrefix() { return m_isPrefix; }

	void setToBeWord() { m_isWord = true; }

	void setToBePrefix() { m_isPrefix = true; }

private:
	bool m_isWord;
	bool m_isPrefix;
	shared_ptr<TrieNode> edges[ChildCount];
};

class Trie
{
public:
	Trie() {
		root = make_shared<TrieNode>();
	}

	// Inserts a word into the trie.
	void insert(string word) {
		shared_ptr<TrieNode> current = root;
		for (int i = 0; i < word.length(); ++i)
		{
			current->setToBePrefix();
			char ch = word[i];
			current = current->appendChildNode(ch);
		}
		current->setToBeWord();
	}

	// Returns if the word is in the trie.
	bool search(string word) {
		shared_ptr<TrieNode> current = root;
		for (int i = 0; i < word.length(); ++i)
		{
			current = current->getChildNode(word[i]);
			if (current == nullptr)
			{
				return false;
			}
		}
		if (!current->isWord())
		{
			return false;
		}
		return true;
	}

	// Returns if there is any word in the trie
	// that starts with the given prefix.
	bool startsWith(string prefix) {
		shared_ptr<TrieNode> current = root;
		for (int i = 0; i < prefix.length(); ++i)
		{
			current = current->getChildNode(prefix[i]);
			if (current == nullptr)
			{
				return false;
			}
		}
		if (!current->isWord() && !current->isPrefix())
		{
			return false;
		}
		return true;
	}

	bool Test()
	{
		Trie trie;
		trie.insert("abcd");
		trie.insert("ab");
		assert(trie.search("abc") == false);
		assert(trie.search("ab") == true);
		assert(trie.search("abcd") == true);
		assert(trie.search("abcde") == false);

		assert(trie.startsWith("a") == true);
		assert(trie.startsWith("b") == false);
		assert(trie.startsWith("ab") == true);
		assert(trie.startsWith("abc") == true);
		assert(trie.startsWith("abce") == false);
		assert(trie.startsWith("abcd") == true);
		assert(trie.startsWith("abcde") == false);
		return true;
	}

private:
	shared_ptr<TrieNode> root;
};