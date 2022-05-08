#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& set;
	SortedSetIterator(const SortedSet& m);

	DLLA list;
	int current;

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};

