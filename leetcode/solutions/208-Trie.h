#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
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
	}

	shared_ptr<TrieNode> appendChildNode(char p_char)
	{
		assert(p_char >= 'a' && p_char <= 'z');
		auto it = m_edges.find(p_char);
		if (it == m_edges.end())
		{
			m_edges[p_char] = make_shared<TrieNode>();
		}

		return m_edges[p_char];
	}

	shared_ptr<TrieNode> getChildNode(char p_char)
	{
		assert(p_char >= 'a' && p_char <= 'z');
		auto it = m_edges.find(p_char);
		if (it == m_edges.end())
		{
			return nullptr;
		}
		else
		{
			return it->second;
		}
	}

	bool isWord() { return m_isWord; }

	bool isPrefix() { return m_isPrefix; }

	void setToBeWord() { m_isWord = true; }

	void setToBePrefix() { m_isPrefix = true; }

private:
	bool m_isWord;
	bool m_isPrefix;
	unordered_map<char, shared_ptr<TrieNode>> m_edges;
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