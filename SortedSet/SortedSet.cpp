#include "SortedSet.h"
#include "SortedSetIterator.h"

//T(max_length)
SortedSet::SortedSet(Relation r) {
    this->relation = r;
    this->list.max_length = 8;
    this->list.head = -1;
    this->list.tail = -1;
    this->list.length = 0;
    this->list.firstEmpty = 0;
    this->list.nodes = new DLLANode[list.max_length];

    for(int i = 0; i < list.max_length - 1; i++)
        this->list.nodes[i].next = i + 1;
    this->list.nodes[list.max_length - 1].next = -1;

    for(int i = 1; i < list.max_length; i++)
        this->list.nodes[i].prev = i - 1;
    this->list.nodes[0].prev = -1;
}

//O(n)
bool SortedSet::add(TComp elem) {
    if(search(elem))
        return false;
    int current = list.head;
    int current_pos = 0;
    while (current != -1 && current_pos < this->size() && list.nodes[current].value != elem && relation(list.nodes[current].value, elem)) {
        current = list.nodes[current].next;
        current_pos++;
    }
    insertPos(elem, current_pos);
    list.length++;
    return true;
}

//O(n)
bool SortedSet::remove(TComp elem) {
	int current = list.head;
	int prev = -1;
    while (current != -1 && (list.nodes[current].value == elem || relation(list.nodes[current].value, elem))) {
        if(list.nodes[current].value == elem) {
            //removing head
            if(current == list.head)
                list.head = list.nodes[current].next;
            //removing tail
            if(current == list.tail)
                list.tail = list.nodes[current].prev;
            //re-linking
            if(list.nodes[current].next != -1)
                list.nodes[prev].next = list.nodes[current].prev;
            if(list.nodes[current].prev != -1)
                list.nodes[prev].next= list.nodes[current].next;
/*            if(list.nodes[current].prev != -1)
                list.nodes[prev].prev = list.nodes[current].prev;
            if(list.nodes[current].next != -1)
                list.nodes[prev].next = list.nodes[current].next;*/
            this->free_node(current);
            list.length--;
            return true;
        }
        prev = current;
        current = list.nodes[current].next;
    }
    return false;
}

//O(n)
bool SortedSet::search(TComp elem) const {
	int current = list.head;
	while(current != -1 && (list.nodes[current].value == elem || relation(list.nodes[current].value, elem))) {
	    if(list.nodes[current].value == elem)
            return true;
	    current = list.nodes[current].next;
	}
    return false;
}

//T(1)
int SortedSet::size() const {
    return list.length;
}

//T(1)
bool SortedSet::isEmpty() const {
    return list.length == 0;
}

//T(1)
SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}

//T(1)
SortedSet::~SortedSet() {
	//delete[] list.nodes;
}

//O(n)
void SortedSet::insertPos(TComp elem, int pos) {
    int new_pos = allocate();
    if(new_pos == -1) {
        resize();
        new_pos = allocate();
    }
    list.nodes[new_pos].value = elem;
    //special case for first pos
    if(pos == 0) {
        //empty list case
        if(list.head == -1) {
            list.head = new_pos;
            list.tail = new_pos;
        } else {
            //insert as head case
            list.nodes[new_pos].next = list.head;
            list.nodes[list.head].prev = new_pos;
            list.head = new_pos;
        }
    } else {
        //searching where to insert
        int current_node = list.head;
        int current_pos = 0;
        while(current_node != -1 && current_pos < pos - 1) {
            current_node = list.nodes[current_node].next;
            current_pos++;
        }
        if(current_node != -1) {
            //adding node at pos
            int next_node = list.nodes[current_node].next;
            list.nodes[new_pos].next = next_node;
            list.nodes[new_pos].prev = current_node;
            list.nodes[current_node].next = new_pos;
            if(next_node == -1) {
                //if node is last
                list.tail = new_pos;
            } else {
                //if node is not last
                list.nodes[next_node].prev = new_pos;
            }
        }
    }
}

//O(n)
void SortedSet::resize() {
    DLLANode* new_nodes = new DLLANode[list.max_length*2];
    //copy elements already in list
    for(int i = 0; i < list.max_length; i++)
        new_nodes[i] = list.nodes[i];
    //init second half
    for(int i = list.max_length; i < 2*list.max_length-1; i++)
        new_nodes[i].next = i + 1;
    new_nodes[list.max_length*2 - 1].next = -1;
    for(int i = list.max_length + 1; i < 2*list.max_length; i++)
        new_nodes->prev = i - 1;
    new_nodes[list.max_length].prev = -1;
    //copy data to our list
    list.firstEmpty = list.max_length;
    list.max_length *= 2;
    //delete[] list.nodes;
    list.nodes = new_nodes;
}

//T(1)
int SortedSet::allocate() {
    int new_pos = list.firstEmpty;
    if(new_pos != -1) {
        list.nodes[list.firstEmpty].prev = -1;
        list.firstEmpty = list.nodes[list.firstEmpty].next;
        list.nodes[new_pos].next = -1;
        list.nodes[new_pos].prev = -1;
    }
    return new_pos;
}

//T(1)
void SortedSet::free_node(int pos) {
    list.nodes[pos].next = list.firstEmpty;
    list.nodes[pos].prev = -1;
    list.nodes[list.firstEmpty].prev = pos;
    list.firstEmpty = pos;
}

