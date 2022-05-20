#pragma once
#include <stack>
#include <iostream>

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	BSTKey* current_node;
	std::stack<BSTKey*> stack;
	int pos_in_key;

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};
