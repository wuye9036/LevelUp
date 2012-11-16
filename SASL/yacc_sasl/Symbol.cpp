#include "Symbol.h"

h_symbol_table symbol_table::root_;

symbol_table::symbol_table(symbol_table* parent)
{
	if (parent == NULL){
		root_ = h_symbol_table(this);
	}
	parent->children_.push_back(h_symbol_table(this));
}
