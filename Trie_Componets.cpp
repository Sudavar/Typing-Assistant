/*
 * Trie_Componets.cpp
 *
 *  Created on: May 18, 2014
 *      Author: Yury Kherimyan
 */

#include "Trie.h"

/* TrieNode */
TrieNode::TrieNode(TrieNode *parent, char label) {
	for (int i = 0; i < DICT; i++) {
		this->index[i] = NULL;
	}
	for (int i = 0; i < N; i++) {
		this->common[i] = NULL;
	}
	this->word = NULL;
	this->parent = parent;
	this->label = label;
}

TrieNode::~TrieNode() {
	for (int i = 0; i < DICT; i++) {
		if (this->index[i] != NULL) {
			delete this->index[i];
		}
	}
	if (this->word != NULL) {
		delete this->word;
	}
}

void TrieNode::update_common(TrieLeaf *leaf) {
	TrieNode *tmp_node = this;
	TrieLeaf *tmp_leaf;
	int curr_word = leaf->get_freq();

	while(tmp_node->label != ' '){
		tmp_leaf = leaf;
		bool flag = false;
		/* Check if already exists in common */
		for (int i = 0; i < N; i++) {
			if (tmp_node->common[i] == leaf) {
				/* Bring it up like bublle sort */
				for (int j = i; j - 1 >= 0; j--){
					if (tmp_node->common[j-1]->get_freq() < tmp_node->common[j]->get_freq()) {
						tmp_leaf = tmp_node->common[j-1];
						tmp_node->common[j-1] = leaf;
						tmp_node->common[j] = tmp_leaf;
					}
				}
				flag = true;
			}
		}
		if (!flag) {
			/* Otherwise must search and find one to replace */
			for (int i = 0; i < N; i++) {
				if (tmp_node->common[i] == NULL) {
					tmp_node->common[i] = tmp_leaf;
					break;
				}
				if (tmp_node->common[i]->get_freq() < curr_word) {
					for (int j = N-2; j >= i; j--) {
						tmp_node->common[j+1] = tmp_node->common[j];
					}
					tmp_node->common[i] = tmp_leaf;
					break;
				}
				if (tmp_node->common[i]->get_freq() == curr_word) {
					/*
					 * should add alpahabetical order
					 */
				}
			}
		}
		tmp_node = tmp_node->parent;
	}
}

/* TrieLeaf */
TrieLeaf::TrieLeaf(TrieNode *parent) {
	this->freq = 0;
	this->parent = parent;
}

TrieLeaf::~TrieLeaf() {
}

void TrieLeaf::add_freq() {
	this->freq++;
}

int TrieLeaf::get_freq() {
	return this->freq;
}

string* TrieLeaf::find_word(TrieNode *dest) {
	string* word = new string;
	TrieNode *tmp = this->parent;
	/* 
	 * Traverse the Trie from bottom to top until
	 * reach TrieNode given on call of function
	 * and store the characters you come across.
	 */
	while (tmp != dest) {
		*(word) += tmp->label;
		tmp = tmp->parent;
	}
	return word;
}

/* EXTRA */
void TrieNode::print(string word, ofstream &write) {
	bool flag = false;

	for (int i = 0; i < DICT; i++) {
		if (this->index[i] != NULL) {
			this->index[i]->print(word + (char) (i + 'a'), write);
			flag = true;
		}
	}
	if (!flag || this->word != NULL) {
		/*
		 * Maybe add some statistics to different file
		 * cout << word << "\t Frequency: " << this->word->get_freq() << endl;
		 */
		write << word << endl;
	}
}

