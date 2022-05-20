#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	BSTKey* node = map.root;
	this->pos_in_key = 0;
	while(node != nullptr) {
	    this->stack.push(node);
	    node = node->left;
	}
	if(!this->stack.empty())
	    this->current_node = stack.top();
	else
	    this->current_node = nullptr;
}

void SMMIterator::first(){
    //clean stack
    while (!this->stack.empty())
        this->stack.pop();
    //re-init
    BSTKey* node = map.root;
    this->pos_in_key = 0;
    while(node != nullptr) {
        this->stack.push(node);
        node = node->left;
    }
    if(!this->stack.empty())
        this->current_node = stack.top();
    else
        this->current_node = nullptr;
}

void SMMIterator::next(){
    if(!valid()) {
        throw std::exception();
    }
    if(pos_in_key < this->current_node->size)
        pos_in_key++;
    if(pos_in_key == this->current_node->size) {
        pos_in_key = 0;
        BSTKey* node = this->stack.top();
        this->stack.pop();
        if(node->right != nullptr) {
            node = node->right;
            while(node != nullptr) {
                this->stack.push(node);
                node = node->left;
            }
        }
        if(!this->stack.empty())
            this->current_node = this->stack.top();
        else
            this->current_node = nullptr;
    }
}

bool SMMIterator::valid() const{
	if(map.isEmpty())
        return false;
    return this->current_node != nullptr;
}

TElem SMMIterator::getCurrent() const{
	if(!valid()) {
        throw std::exception();
    }
    return std::make_pair(this->current_node->key, this->current_node->values[this->pos_in_key]);
}


