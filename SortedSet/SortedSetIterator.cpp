#include "SortedSetIterator.h"
#include <exception>

using namespace std;

//T(1)
SortedSetIterator::SortedSetIterator(const SortedSet& m) : set(m)
{
	this->list = m.list;
	this->current = m.list.head;
}

//T(1)
void SortedSetIterator::first() {
	this->current = set.list.head;
}


void SortedSetIterator::next() {
	if(!this->valid())
	    throw std::exception();
	this->current = this->list.nodes[this->current].next;
}


TElem SortedSetIterator::getCurrent()
{
	if(!this->valid())
        throw std::exception();
    return this->list.nodes[this->current].value;
}

bool SortedSetIterator::valid() const {
    return this->current != -1;
}

