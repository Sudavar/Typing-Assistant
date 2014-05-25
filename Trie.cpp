/*
 * Trie.cpp
 *
 *  Created on: May 6, 2014
 *      Author: Yury Kherimyan
 */

#include "Trie.h"

Trie::Trie() {
	this->cur_node = NULL;
	this->cur_prefix = "";
	this->root = new TrieNode(NULL, ' ');
}

Trie::~Trie() {
	delete this->root;
	this->root = NULL;
	this->cur_node = NULL;
	this->cur_prefix = "";
}

bool Trie::insert(string word) {
	TrieNode *tmp = this->root;
	if (word == "")
		return false;
	for (unsigned int i = 0; i < word.length(); i++) {
		int ch = tolower(word[i]) - 'a';
		/*
		 * Traversing through the Trie, one character a time.
		 * If the character hadn't come up yet, create a Trie node
		 * and if it was the last character add 1 to frequency,
		 * otherwise continue traversing through the Trie until one of the
		 * above cases are met.
		 */
		if (tmp->index[ch] == NULL) {
			tmp->index[ch] = new TrieNode(tmp, word[i]);
			tmp = tmp->index[ch];
		} else {
			tmp = tmp->index[ch];
		}
	}
	/*
	 * Traversed through the whole word in dictionary,
	 * now must increase frequency and update common links to leaf.
	 */
	if (tmp->word == NULL)
		tmp->word = new TrieLeaf(tmp);
	tmp->word->add_freq();
	tmp->update_common(tmp->word);

	return true;
}

string** Trie::suggestions() {
	string** suggests = new string*[N];

	this->clean_prefix();
	/* Should initialize to NULL, got segmentations sometimes */
	for (int i = 0; i < N; i++)
		suggests[i] = NULL;

	/* Trie traversing */
	this->cur_node = this->root;
	for (unsigned int i = 0; i < this->cur_prefix.length(); i++) {
		int ch = this->cur_prefix[i] - 'a';
		if (this->cur_node->index[ch] != NULL) {
			this->cur_node = this->cur_node->index[ch];
		} else {
			/* Not a word in our dictionary */
			return NULL;
		}
	}

	cerr << endl;
	/* Reached final node, must find the suggestions now */
	for (int i = 0; i < N; i++) {
		if (this->cur_node->common[i] != NULL) {
			suggests[i] = this->cur_node->common[i]->find_word(this->root);
			/* Must reverse the word now */
			cerr << i+1 << ")";
			for (string::reverse_iterator rit=suggests[i]->rbegin(); rit!=suggests[i]->rend(); ++rit)
			    cerr << *rit;
			cerr << " ";
		}
	}
	return suggests;
}

void Trie::add_prefix(char ch) {
	this->cur_prefix += ch;
}

void Trie::clear_prefix() {
	this->cur_prefix.clear();
}

void Trie::backspace() {
	this->cur_prefix = this->cur_prefix.substr(0, this->cur_prefix.size()-1);
}

string Trie::get_prefix() {
	return this->cur_prefix;
}

/*
 * Clean current prefix. If find any unwanted character
 * shift all the rest one position to the left.
 */
void Trie::clean_prefix() {
	for (unsigned int i = 0; i < this->cur_prefix.length(); i++) {
		this->cur_prefix[i] = tolower(this->cur_prefix[i]);
		if (this->cur_prefix[i] == ' ' || this->cur_prefix[i] == '\n' || this->cur_prefix[i] == '\t') {
			for (unsigned int j = i; j <= this->cur_prefix.length(); j++) {
				this->cur_prefix[j] = this->cur_prefix[j+1];
			}
		}
	}
}

void Trie::print(ofstream &write) {
	this->root->print("", write);
}

