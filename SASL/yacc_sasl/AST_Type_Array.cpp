#include "AST_Type.h"

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
ArrayType::~ArrayType(){
    // Handled by deleting the global type list
    // delete subType;
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
Type*
ArrayType::dup0() const{
    ArrayType *ret  = new ArrayType(type, size->dup());

    ret->subType = subType->dup();
    ret->storage = storage;

    return ret;
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
Type*
ArrayType::extend(Type *extension){
    if (subType)
        return subType->extend(extension);
    subType = extension;
    return this ;
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
void
ArrayType::findExpr( fnExprCallback cb ){
    if (subType)
        subType->findExpr(cb);

    if (size) {
       size = (cb)(size);
       size->findExpr(cb);
    }
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
bool ArrayType::lookup( Symbol* sym ) const
{
    if (subType)
        return subType->lookup(sym);
    else
        return false;
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
TypeQual ArrayType::getQualifiers( void ) const{
   return subType->getQualifiers();
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
BaseType* ArrayType::getBase( void ){
   return subType->getBase();
}
