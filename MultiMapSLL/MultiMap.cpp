#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

//T(1)
MultiMap::MultiMap() {
	this->head = nullptr;
	this->nr_elems = 0;
}

//O(nr_keys) complexity - we need to find the SLL associated to the key before adding
void MultiMap::add(TKey c, TValue v) {
	SLLKey* key_sll = this->getKey(c);
	SLLNode* new_node = new SLLNode[1];
	new_node->value = v;
	new_node->next = nullptr;
	this->nr_elems++;
	//if the key is already in the SLL
	if(key_sll != nullptr) {
	    new_node->next = key_sll->head;
        key_sll->head = new_node;
	//if the key is not in the SLL
	} else {
	    SLLKey* new_key = new SLLKey[1];
	    new_key->key = c;
	    new_key->next = this->head;
	    this->head = new_key;
	    new_key->head = new_node;
	}
}

//O(n) - we iterate through all the SLLs, not only through the keys
bool MultiMap::remove(TKey c, TValue v) {
	SLLKey* key_sll = this->getKey(c);
	//key not in SLL
	if(key_sll == nullptr)
        return false;
	SLLNode* current = key_sll->head;
	SLLNode* prev = nullptr;
	//finding the element to remove
    while (current != nullptr && current->value != v) {
        prev = current;
        current = current->next;
    }
    //case where the element is the first in the SLL
    if(current != nullptr && prev == nullptr) {
        key_sll->head = key_sll->head->next;
        delete current;
        this->nr_elems--;
        //check if key sll is empty
        if(key_sll->head == nullptr)
            removeKey(c);
        return true;
    //case where the element is not the first in the SLL
    } else if (current != nullptr) {
        prev->next = current->next;
        current->next = nullptr;
        delete current;
        this->nr_elems--;
        return true;
    }
    //cleanup and element not found case
    delete current;
    return false;
}

//O(nr_keys)
vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> result{};
	SLLKey* key_sll = this->getKey(c);
	if(key_sll == nullptr)
        return result;
	SLLNode* current = key_sll->head;
    while (current != nullptr) {
        result.push_back(current->value);
        current = current->next;
    }
    return result;
}

//T(1) complexity - we keep track of the number of values in the list
int MultiMap::size() const {
    return this->nr_elems;
}

//T(1) complexity
bool MultiMap::isEmpty() const {
    return this->head == nullptr;
}

//T(1)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
	SLLKey* current_key = this->head;
	SLLNode* current_node = nullptr;
    if(current_key != nullptr)
        current_node = current_key->head;
    while (current_key != nullptr) {
        this->head = current_key->next;
        while (current_node != nullptr) {
            current_key->head = current_node->next;
            delete current_node;
            current_node = current_key->head;
        }
        delete current_key;
        current_key = this->head;
    }
}

//O(nr_keys)
SLLKey * MultiMap::getKey(TKey key) const {
    SLLKey* current = this->head;
    while(current != nullptr) {
        if(current->key == key) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

//O(nr_keys)
void MultiMap::removeKey(TKey key) {
    SLLKey* current = this->head;
    SLLKey* prev = nullptr;
    //searching for the key
    while(current != nullptr && current->key != key) {
        prev = current;
        current = current->next;
    }
    //key was first in list case
    if(current != nullptr && prev == nullptr) {
        this->head = this->head->next;
        delete current;
    } else if(current != nullptr) {
        //key was not first in list case
        prev->next = current->next;
        current->next = nullptr;
        delete current;
    }
}

