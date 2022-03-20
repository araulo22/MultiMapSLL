#include "SortedBag.h"
#include "SortedBagIterator.h"

//T(1)
SortedBag::SortedBag(Relation r) {
	this->relation = r;
	this->max_length = 8;
	this->length = 0;
	this->bag_array = new bag_element[this->max_length];
	this->nr_elems = 0;
}

//best: T(1)
//worst: T(length)
//total: O(length)
void SortedBag::add(TComp e) {
    //empty bag case
    if(this->isEmpty()) {
        this->bag_array[0].value = e;
        this->bag_array[0].frequency = 1;
        this->nr_elems++;
        this->length++;
        return;
    }
    //element already in bag case
	int index = this->index_search(e);
	if(index != -1) {
	    this->bag_array[index].frequency++;
        this->nr_elems++;
        return;
    //element not in bag case
	} else {
	    if(this->length == this->max_length)
	        resize();
	    //searching position for the element according to the relation
	    index = 0;
        while (index < this->length && this->relation(this->bag_array[index].value, e))
            index++;
        //moving all other elements
        for(int i = this->length; i > index; i--)
            this->bag_array[i] = this->bag_array[i-1];
        //placing the element
        this->bag_array[index].value = e;
        this->bag_array[index].frequency = 1;
        this->nr_elems++;
        this->length++;
        return;
	}
}

//best: T(1)
//worst: T(length)
//total: O(length)
bool SortedBag::remove(TComp e) {
	int index = this->index_search(e);
	if(index == -1)
        return false;
	else {
	    this->bag_array[index].frequency--;
	    this->nr_elems--;
	    if(this->bag_array[index].frequency == 0) {
	        for(int i = index; i < this->length - 1; i++)
	            this->bag_array[i] = this->bag_array[i+1];
	        this->length--;
	    }
        return true;
	}
}

//best: T(1)
//worst: T(length)
//total: O(length)
bool SortedBag::search(TComp elem) const {
	for(int i = 0; i < this->length; i++)
	    if(this->bag_array[i].value == elem)
            return true;
	return false;
}

//best: T(1)
//worst: T(length)
//total: O(length)
int SortedBag::nrOccurrences(TComp elem) const {
	int index = this->index_search(elem);
	if(index != -1)
        return bag_array[index].frequency;
    return 0;
}

//T(1)
int SortedBag::size() const {
    return this->nr_elems;
}

//T(1)
bool SortedBag::isEmpty() const {
    return this->length == 0;
}

//T(1)
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

//T(1)
SortedBag::~SortedBag() {
	delete[] this->bag_array;
}

//T(length)
void SortedBag::resize() {
    this->max_length *= 2;
    auto *new_array = new bag_element[this->max_length];
    for(int i = 0; i < this->length; i++) {
        new_array[i] = this->bag_array[i];
    }
    delete[] this->bag_array;
    this->bag_array = new_array;
}

//best: T(1)
//worst: T(length)
//total: O(length)
int SortedBag::index_search(TComp elem) const {
    for(int i = 0; i < this->length; i++)
        if(this->bag_array[i].value == elem)
            return i;
    return -1;
}
