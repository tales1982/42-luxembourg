#ifndef SEARCHABLE_TREE_BAG_HPP
#define SEARCHABLE_TREE_BAG_HPP

#include "tree_bag.hpp"
#include "searchable_bag.hpp"

class searchable_tree_bag : public tree_bag, public searchable_bag {

public:

searchable_tree_bag () : tree_bag(){}
searchable_tree_bag (const searchable_tree_bag &o) : tree_bag(o){}
~searchable_tree_bag () {}

searchable_tree_bag &operator=(const searchable_tree_bag &o) {
if(this!=  &o)
	tree_bag::operator=(o);
return *this;
}

bool has (int item) const {
node *c =tree;
while(c){
	if(item < c->value)
		c= c->l;
	else if (item >c->value)
		c= c->r;
	else
		return true;
	}	
	return false;
	}
	};
#endif
	
