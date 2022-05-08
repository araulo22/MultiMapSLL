#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
	this->relation = r;
	this->max_length = 8;
	this->length = 0;
	this->nodes = new DLLANode[this->max_length];
	this->head = -1;
    this->tail = -1;
    this->initFreeSpace();
}


bool SortedSet::add(TComp elem) {
	//check if element already in array
	if(this->search(elem))
        return false;
	//find position for the elem
	int current = this->head;
	while(current != this->tail && relation(this->nodes[current].value, elem))
	    current = nodes[current].next;
    //no elements in the DLLA
    if(current == -1) {
        this->nodes[firstFree].value = elem;
        this->nodes[firstFree].next = -1;
        this->nodes[firstFree].prev = -1;
        this->head = 0;
        this->tail = 0;
        return true;
    }
	return false;
}


bool SortedSet::remove(TComp elem) {
	//TODO - Implementation
	return false;
}

//O(n)
bool SortedSet::search(TComp elem) const {
	int current = this->head;
    while (current != -1) {
        if(this->nodes[current].value == elem)
            return true;
        current = this->nodes[current].next;
    }
    return false;
}


int SortedSet::size() const {
	//TODO - Implementation
	return 0;
}



bool SortedSet::isEmpty() const {
	//TODO - Implementation
	return false;
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
	//TODO - Implementation
}

void SortedSet::resize() {
    this->max_length *= 2;
    auto *new_nodes = new DLLANode[this->max_length];
    for(int i = 0; i < this->length; i++) {
        new_nodes[i] = this->nodes[i];
    }
    delete[] this->nodes;
    this->nodes = new_nodes;
}

void SortedSet::initFreeSpace() {
    for(int i = 0; i < max_length; i++) {
        nodes[i].next = i + 1;
        nodes[i].prev = i - 1;
        nodes[i].value = NULL_TELEM;
    }
    nodes[0].prev = -1;
    nodes[max_length - 1].next = -1;
    this->firstFree = 0;
}

int SortedSet::findFree() {
    int freePos = -1;
    for(int i = 0; i < max_length; i++) {
        if(nodes[i].value == NULL_TELEM) {
            freePos = i;
            break;
        }
    }
    if(freePos == -1)
        this->resize();

}


