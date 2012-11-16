#include "AST_Type.h"

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
type_base::type_base(type_type _type /* =TT_Base */)
{
    typecode = _type;
    storage = ST_None;

    // Add us into the global list for destruction later.
    //link = gProject->typeList;
    //gProject->typeList = this;
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
type_base::~type_base()
{
    // assert(false);
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
