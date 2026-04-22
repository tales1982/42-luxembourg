#ifndef SET_HPP
#define SET_HPP
#include "searchable_bag.hpp"

class set {

searchable_bag *bag;

public:

set() : bag(0){}
set (searchable_bag &b) : bag(&b) {}
set(const set &o) {bag = o.bag ? o.bag : 0;}

~set () {}

set &operator=(const set &o) {
if(this != &o)
	bag = o.bag ? o.bag : 0;
return *this;
}

void insert (int item) {if(bag && !has(item)) bag->insert(item);}
void insert (int *items, int s) {
for (int i=0; i<s; i++)
	if(bag && !has(items[i]))
		bag->insert(items[i]);
		}
		
void print() const {bag-> print();}
void clear() {bag->clear();}

bool has (int item) const {return bag->has(item);}
searchable_bag &get_bag () const {return *bag;}
};
#endif
