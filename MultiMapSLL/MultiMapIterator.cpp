#include <stdexcept>
#include "MultiMapIterator.h"
#include "MultiMap.h"

//Theta(1)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	this->current_key = c.head;
	if(this->current_key != nullptr)
        this->current_node = current_key->head;
	else
	    this->current_node = nullptr;
}

TElem MultiMapIterator::getCurrent() const{
	if(this->current_node == nullptr)
        throw std::runtime_error("Iterator getCurrent error!");
	TElem result = make_pair(this->current_key->key, this->current_node->value);
    return result;
}

bool MultiMapIterator::valid() const {
    return this->current_key != nullptr;
}

void MultiMapIterator::next() {
	if(this->current_key == nullptr)
	    throw std::runtime_error("Iterator next error!");
	this->current_node = this->current_node->next;
	if(this->current_node == nullptr)
        this->nextKey();
//	if(this->current_node->next != nullptr)
//	    this->current_node = this->current_node->next;
//	else {
//	    //moving into another key SLL
//        this->current_key = this->current_key->next;
//        if(this->current_key != nullptr)
//            this->current_node = this->current_key->head;
//    }
}

void MultiMapIterator::first() {
    this->current_key = this->col.head;
    this->current_node = current_key->head;
}

void MultiMapIterator::nextKey() {
    this->current_key = this->current_key->next;
    if(this->current_key != nullptr)
        this->current_node = this->current_key->head;
}

