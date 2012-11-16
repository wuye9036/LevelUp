#include "AST_Type.h"

using namespace std;

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
FunctionType::FunctionType(const vector<HDecl>& args_list)
  : Type(TT_Function), nArgs(0),
    size(0), args(NULL)
{
   addArgs (args_list);
}

FunctionType::~FunctionType()
{
    for (unsigned int j=0; j < nArgs; j++)
    {
        delete args[j];
    }

    delete [] args;

    // Handled by deleting the global type list
    // delete subType;
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
Type*
FunctionType::dup0() const
{
    FunctionType *ret = new FunctionType();
    ret->storage = storage;
    ret->size    = size;
    ret->args = new Decl* [size];

    for (unsigned int j=0; j < nArgs; j++)
        ret->addArg(args[j]->dup());

    ret->subType = subType->dup();

    return ret;
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
Type*
FunctionType::extend(Type *extension)
{
    if (subType)
        return subType->extend(extension);

    subType = extension;
    return this;
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
void
FunctionType::addArg(Decl *arg)
{
    if (size == nArgs)
    {
        if (size == 0)
            size = 4;
        else
            size += size;

        Decl   **oldArgs = args;

        args = new Decl* [size];

        for (unsigned int j=0; j < nArgs; j++)
        {
            args[j] = oldArgs[j];
        }

        delete [] oldArgs;
    }

    args[nArgs] = arg;
    nArgs++;
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
void
FunctionType::addArgs(Decl *args)
{
    Decl *arg = args;

    while (args != NULL)
    {
        args = args->next;
        arg->next = NULL;
        addArg(arg);
        arg = args;
    }
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
void
FunctionType::findExpr( fnExprCallback cb )
{
    if (subType)
        subType->findExpr(cb);

    for (unsigned int j=0; j < nArgs; j++)
    {
        args[j]->findExpr(cb);
    }
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
bool
FunctionType::lookup( Symbol* sym ) const
{
    if (subType)
        return subType->lookup(sym);
    else
        return false;
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
TypeQual
FunctionType::getQualifiers( void ) const
{
   return subType->getQualifiers();
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
BaseType *
FunctionType::getBase( void )
{
   return subType->getBase();
}
