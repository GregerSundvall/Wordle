
#include <string>
#include <iostream>
#define CHARS_MAX 26
//#define KEY_LENGTH 5


class Trie {
public:
	bool isLeaf;
	Trie* character[CHARS_MAX];

	Trie() {
		this->isLeaf = false;

		for (int i = 0; i < CHARS_MAX; ++i) {
			this->character[i] = nullptr;
		}
	}

	void insert(std::string);
	bool remove(Trie*&, std::string);
	bool search(std::string);
	bool hasChildren(Trie const*);
};


void Trie::insert(std::string key) {
	Trie* current = this;
	for (int i = 0; i < key.length(); ++i) {
		if (current->character[key[i]] == nullptr) {
			current->character[key[i]] = new Trie();
		}
		current = current->character[key[i]];
	}
	current->isLeaf = true;
}

bool Trie::search(std::string key) {
	if (this == nullptr) { return false; }

	Trie* current = this;
	for (int i = 0; i < key.length(); ++i) {
		current = current->character[key[i]];

		if (current == nullptr) {return false;}
	}

	return current->isLeaf;
}

bool Trie::hasChildren(Trie const* current) {
	for (int i = 0; i < CHARS_MAX; ++i) {
		if (current->character[i]) {
			return true;
		}
	}
	return false;
}


bool Trie::remove(Trie*& current, std::string key) {
	if (current == nullptr) { return false;	}

	if (key.length()) {
		if (current != nullptr && 
			current->character[key[0]] != nullptr &&
			remove(current->character[key[0]], key.substr(1)) &&
			current->isLeaf == false) 
			{
				if (!hasChildren(current)) {
					delete current;
					current = nullptr;
					return true;
				}
				else {
					return false;
				}
		}
	}

	if (key.length() == 0 && current->isLeaf) {
		if (!hasChildren(current)) {
			delete current;
			current = nullptr;
			return true;
		}
		else {
			current->isLeaf = false;
			return false;
		}
	}

}



