#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
	this->root = nullptr;
	this->tsize = 0;
	this->rel = r;
}

BSTKey *SortedMultiMap::insert(TKey key, TValue elem, BSTKey *node) {
    if(node == nullptr) {
        node = create_key(key);
        this->add_to_key(node, elem);
    } else if(!this->rel(node->key, key)) {
        node->left = insert(key, elem, node->left);
        return node;
    } else {
        node->right = insert(key, elem, node->right);
        return node;
    }
}

void SortedMultiMap::add(TKey c, TValue v) {
	//empty BST case
    if(isEmpty()) {
	    this->root = create_key(c);
	    this->add_to_key(this->root, v);
	    this->tsize++;
        return;
	}
    //key already in BST case
    BSTKey* found = search_key(c);
    if(found != nullptr) {
        this->add_to_key(found, v);
        this->tsize++;
        return;
    }
    //key not in BST case
    this->insert(c, v, this->root);
    this->tsize++;
}

vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> result;
	BSTKey* found = search_key(c);
	if(found != nullptr)
        for(int i = 0; i < found->size; i++)
            result.push_back(found->values[i]);
    return result;
}

BSTKey *SortedMultiMap::find_min(BSTKey *key) {
    if(key == nullptr)
        return nullptr;
    else if(key->left == nullptr)
        return key;
    else
        return find_min(key->left);
}

BSTKey *SortedMultiMap::find_max(BSTKey *key) {
    if(key == nullptr)
        return nullptr;
    else if(key->right == nullptr)
        return key;
    else
        return find_max(key->right);
}

BSTKey* SortedMultiMap::remove_key(TKey key, BSTKey* node) {
    BSTKey* temp;
    //stopping condition
    if(node == nullptr)
        return nullptr;
    if(node->key == key) {
        //no children case
        if(node->left == nullptr && node->right == nullptr)
            return nullptr;
        //one child case RIGHT
        else if(node->left == nullptr)
            return node->right;
        //one child case LEFT
        else if(node->right == nullptr)
            return node->left;
        //two children case
        else {
            temp = find_min(node->right);
            node->key = temp->key;
            delete[] node->values;
            node->values = temp->values;
            node->size = temp->size;
            node->max_size = temp->size;
            node->right = remove_key(node->key, node->right);
            return node;
        }
    }
    else if(!this->rel(node->key, key)) {
        node->left = remove_key(key, node->left);
        return node;
    }
    else {
        node->right = remove_key(key, node->right);
        return node;
    }
}

bool SortedMultiMap::remove(TKey c, TValue v) {
    BSTKey* found = search_key(c);
	if(found != nullptr) {
	    if(this->remove_from_key(found, v)) {
            this->tsize--;
            //if the dynamic list of the key is empty after this remove, we have to remove the key node
            if(found->size == 0) {
                this->remove_key(c, found);
            }
            return true;
	    }
	}
    return false;
}


int SortedMultiMap::size() const {
    return this->tsize;
}

bool SortedMultiMap::isEmpty() const {
    return this->tsize == 0;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	//delete[] this->root->values;
}

void SortedMultiMap::resize_key(BSTKey* key) {
    key->max_size *= 2;
    TValue *new_values = new TValue[key->max_size];
    for(int i = 0; i < key->size; i++) {
        new_values[i] = key->values[i];
    }
    delete[] key->values;
    key->values = new_values;
}

void SortedMultiMap::add_to_key(BSTKey* key, TValue elem) {
    if(key->size == key->max_size)
        resize_key(key);
    key->values[key->size] = elem;
    key->size++;
}

BSTKey* SortedMultiMap::create_key(TKey key) {
    BSTKey* added_key = new BSTKey;
    added_key->left = nullptr;
    added_key->right = nullptr;
    added_key->key = key;
    added_key->max_size = 8;
    added_key->size = 0;
    added_key->values = new TValue[added_key->max_size];
    return added_key;
}

BSTKey * SortedMultiMap::search_key(TKey key) const {
    BSTKey* current = this->root;
    while(current != nullptr) {
        if(current->key == key)
            return current;
        if(!this->rel(current->key, key))
            current = current->left;
        else
            current = current->right;
    }
    return nullptr;
}

bool SortedMultiMap::remove_from_key(BSTKey *key, TValue elem) {
    for(int i = 0; i < key->size; i++) {
        if(key->values[i] == elem) {
            for(; i < key->size - 1; i++) {
                key->values[i] = key->values[i+1];
            }
            key->size--;
            return true;
        }
    }
    return false;
}


