/*
 * Trie.h
 *
 *  Created on: May 6, 2014
 *      Author: Yury Kherimyan
 */

#ifndef TRIE_H_
#define TRIE_H_
#define N 4
#define DICT 26

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

class TrieNode;

class TrieLeaf {
private:
	TrieNode *parent;
	int freq;
public:
	TrieLeaf(TrieNode *);
	virtual ~TrieLeaf();

	void add_freq();
	int get_freq();
	string* find_word(TrieNode*);
};

class TrieNode {
public:
	TrieNode *index[DICT];
	TrieNode *parent;
	TrieLeaf *common[N];
	TrieLeaf *word;
	char label;

	TrieNode(TrieNode *, char);
	virtual ~TrieNode();

	void print(string, ofstream &);
	void update_common(TrieLeaf *);
};

class Trie {
private:
	TrieNode *root;
	TrieNode *cur_node;
	string cur_prefix;
public:
	Trie();
	virtual ~Trie();

	bool insert(string);
	void print(ofstream &);
	string** suggestions();
	void add_prefix(char);
	void clear_prefix();
	void clean_prefix();
	void backspace();
	string get_prefix();
};
#endif /* TRIE_H_ */
