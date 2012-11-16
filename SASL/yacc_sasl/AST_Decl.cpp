#include "AST_Decl.h"

decl::decl() : name(NULL)
{
	clear();
}

decl::decl( h_type_base type, symbol_entry* name): form(type), name(NULL)
{
    clear();
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
decl::~decl()
{
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
void decl::clear()
{
    storage = ST_None;
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
decl* decl::dup() const
{
    decl *ret = this ? dup0() : NULL;
    return ret;
}

decl* decl::dup0() const
{

    //decl *ret = new decl();
    //ret->storage    = storage;
    //ret->form = form->dup();//do copy so that cpu implementation can be above

    //ret->name     = name;
    //ret->initializer = initializer->dup();
    //ret->next = next->dup();

    return NULL;
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
void decl::copy(const decl& decl)
{
    storage     = decl.storage;
    name        = decl.name;
    form        = decl.form;
}

void decl::output(std::ostream& os)
{
	if (this->form){
		form->output(os);
	}

	os << StorageTypeToString(storage) << name << ";";
}

