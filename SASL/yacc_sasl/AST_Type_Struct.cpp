#include "AST_Decl.h"
#include "AST_Type.h"


#include <boost/foreach.hpp>
using namespace std;

struct_type::struct_type(){
}

struct_type::~struct_type(){

}

type_base* struct_type::dup0() const{
	return NULL;
}

type_qualifier struct_type::get_qualifiers() const {
	return qualifier;
}

struct_type& struct_type::operator = (const struct_type& rhs){
	assert(false);
	return *this;
}

void struct_type::add_component(h_decl decl)
{
	//components_.push_back(decl);
	decl->next = h_decl();
}

void struct_type::set_component_list(h_decl decl)
{

	for(h_decl ptr = decl; ptr.get() != NULL; ptr = ptr->next){
		//components_.push_back(ptr);
	}

	h_decl ptr;
//	BOOST_FOREACH(ptr, components_){
//		ptr->next = h_decl();
//	}
}
