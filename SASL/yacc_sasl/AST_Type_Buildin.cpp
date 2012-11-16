#include "AST_Type.h"


// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
buidin_type::buidin_type( BuildinTypeSpec bt /* =BT_NoType */ )
        : type_base(TT_Simple)
{
    typecode = bt;
    qualifier = TQ_None;
}

buidin_type::~buidin_type()
{
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
type_base* buidin_type::dup0() const
{
    buidin_type *ret = new buidin_type();

    ret->storage = storage;
    ret->qualifier = qualifier;
    ret->typecode = typecode;

    return ret;
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
type_qualifier buidin_type::get_qualifiers( void ) const
{
   return qualifier;
}

buidin_type& buidin_type::operator = (const buidin_type& b) {
  this->typecode = b.typecode;
  this->qualifier = b.qualifier;
  return *this;
}

void buidin_type::output(std::ostream& os)
{
	os << TypeQualToString(this->qualifier) << BuildinTypeToString(this->typecode);
}
