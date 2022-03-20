#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

//T(1)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->index = 0;
	this->freq_index = 0;
}

//T(1)
TComp SortedBagIterator::getCurrent() {
	if(!this->valid())
        throw exception();
    return this->bag.bag_array[index].value;
}

//T(1)
bool SortedBagIterator::valid() {
    return this->index < this->bag.length;
}

//T(1)
void SortedBagIterator::next() {
	if(!this->valid())
	    throw exception();
	this->freq_index++;
	if(this->bag.bag_array[index].frequency == this->freq_index) {
	    this->index++;
	    this->freq_index = 0;
	}
}

//T(1)
void SortedBagIterator::first() {
	this->index = 0;
	this->freq_index = 0;
}

