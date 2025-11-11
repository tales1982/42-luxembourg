#ifndef SEARCHABLE_ARRAY_BAG_HPP
#define SEARCHABLE_ARRAY_BAG_HPP

#include "array_bag.hpp"
#include "searchable_bag.hpp"


class searchable_array_bag : public array_bag, public searchable_bag {

public:

searchable_array_bag () : array_bag(){}
searchable_array_bag (const searchable_array_bag &o) : array_bag(o){}
~searchable_array_bag () {}

searchable_array_bag &operator=(const searchable_array_bag &o) {
if(this !=&o)
	array_bag::operator=(o);
return *this;
}

bool has (int item) const {
for(int i=0; i<size; i++)
	if(data[i] == item)
		return true;
return false;
	}
};
#endif
