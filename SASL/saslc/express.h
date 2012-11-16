/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

    CTool Library
    Copyright (C) 1998-2001	Shaun Flisakowski

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 1, or (at your option)
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
    o+
    o+     File:         express.h
    o+
    o+     Programmer:   Shaun Flisakowski
    o+     Date:         Aug 9, 1998
    o+
    o+     A high-level view of expressions.
    o+
    o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

#ifndef    EXPRESS_H
#define    EXPRESS_H

#include <cstdlib>
#include <iostream>
#include <vector>

#include <ctool/symbol.h>
#include <ctool/decl.h>
#include <ctool/callback.h>
#include <ctool/location.h>
#include <ctool/utype.h>

#include <ctool/dup.h>
#include <ctool/Traversal.h>

class Decl;
class Type;

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

typedef void (*fnExprCallback)(Expression *expr);

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
enum ExpressionType
{
    ET_VoidExpr=0,           // No value

    ET_Constant,
    ET_Variable,
    ET_FunctionCall,

    ET_AssignExpr,
    ET_RelExpr,

    ET_UnaryExpr,
    ET_BinaryExpr,
    ET_TrinaryExpr,          // x ? y : z

    ET_CastExpr,             // (type) x
    ET_IndexExpr             // x[y]...[]
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
enum ConstantType
{
    CT_Char,
    CT_Int,
    CT_UInt,
    CT_Float,

    CT_String,
    CT_Array,           // For an array initializer
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
enum AssignOp
{
    AO_Equal,          //  =

    AO_PlusEql,        // +=
    AO_MinusEql,       // -=
    AO_MultEql,        // *=
    AO_DivEql,         // /=
    AO_ModEql,         // %=

    AO_ShlEql,         // <<=
    AO_ShrEql,         // >>=

    AO_BitAndEql,      // &=
    AO_BitXorEql,      // ^=
    AO_BitOrEql        // |=
};

enum RelOp
{
    RO_Equal,          // ==
    RO_NotEqual,       // !=

    RO_Less,           // <
    RO_LessEql,        // <=
    RO_Grtr,           // >
    RO_GrtrEql         // >=
};

enum UnaryOp
{
    UO_Plus=0,         // +
    UO_Minus,          // -
    UO_BitNot,         // ~
    UO_Not,            // !

    UO_PreInc,         // ++x
    UO_PreDec,         // --x
    UO_PostInc,        // x++
    UO_PostDec,        // x--

    UO_AddrOf,         // &
    UO_Deref           // *
};

enum BinaryOp
{
    BO_Plus,        // +
    BO_Minus,       // -
    BO_Mult,        // *
    BO_Div,         // /
    BO_Mod,         // %

    BO_Shl,         // <<
    BO_Shr,         // >>
    BO_BitAnd,      // &
    BO_BitXor,      // ^
    BO_BitOr,       // |

    BO_And,         // &&
    BO_Or,          // ||

    BO_Comma,       // x,y

    BO_Member,      // x.y
    BO_PtrMember,   // x->y

    BO_Assign,      // An AssignExpr
    BO_Rel          // A RelExpr
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

class Expression;
typedef Dup<Expression> DupableExpression;

class Expression : public DupableExpression
{
  public:
    Expression( ExpressionType et, const Location& l );
    virtual ~Expression();

    virtual void accept(Traversal *) = 0;

    virtual int precedence() const { return 16; }

    virtual Expression *dup0() const = 0;

    virtual void print(std::ostream& out) const;

    virtual void findExpr( fnExprCallback cb ) { (cb)(this); }

    ExpressionType    etype;
    Location          location;

    // For type-checking.
    Type             *type;

    // For constructing a list of expressions (in parser).
    Expression       *next;

  friend std::ostream& operator<< ( std::ostream& out, const Expression& expr );
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

typedef    std::vector<Expression*>    ExprVector;

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class Constant : public Expression
{
  public:
    Constant( ConstantType ct, const Location& l );
    virtual ~Constant();

    virtual Expression *dup0() const = 0;
    virtual void print(std::ostream& out) const = 0;

    ConstantType    ctype;

    std::string original_rep;
};
// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class IntConstant : public Constant
{
  public:
    IntConstant( long val, bool b, const Location& l );
    virtual ~IntConstant();

    virtual void accept(Traversal *t) { t->traverse_int(this);}

    Expression *dup0() const;
    void print(std::ostream& out) const;

    long    lng;
    bool    L;
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class UIntConstant : public Constant
{
  public:
    UIntConstant( ulong val, bool b, const Location& l );
    virtual ~UIntConstant();

    virtual void accept(Traversal *t) { t->traverse_uint(this);}

    Expression *dup0() const;
    void print(std::ostream& out) const;

    ulong    ulng;
    bool     L;
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class FloatConstant : public Constant
{
  public:
    FloatConstant(const std::string& val, const Location& l );
    virtual ~FloatConstant();

    virtual void accept(Traversal *t) { t->traverse_float(this);}

    Expression *dup0() const;
    void print(std::ostream& out) const;

    std::string value;
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class CharConstant : public Constant
{
  public:
    CharConstant(char chr, const Location& l, bool isWide=false );
   ~CharConstant();

    virtual void accept(Traversal *t) { t->traverse_char(this);}

    Expression *dup0() const;
    void print(std::ostream& out) const;

    char    ch;       // the character
    bool    wide;     // wide char?
};
// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class StringConstant : public Constant
{
  public:
    StringConstant(const std::string &str, const Location& l,
                   bool isWide=false );
   ~StringConstant();

    virtual void accept(Traversal *t) { t->traverse_string(this);}

    int length() const;

    Expression *dup0() const;
    void print(std::ostream& out) const;

    std::string buff; // dynamic string storage
    bool    wide;     // wide string?
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class ArrayConstant : public Constant
{
  public:
    ArrayConstant(const Location& l );
   ~ArrayConstant();

    virtual void accept(Traversal *t) { t->traverse_array(this);}

    void addElement( Expression *expr);

    Expression *dup0() const;
    void print(std::ostream& out) const;

    void findExpr( fnExprCallback cb );

    ExprVector    items;    // Array of whatever, including another array.
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class EnumConstant : public Constant
{
  public:
    EnumConstant(Symbol *nme, Expression* val, const Location& l );
   ~EnumConstant();

    virtual void accept(Traversal *t) { t->traverse_enum(this);}

    Expression *dup0() const;
    void print(std::ostream& out) const;

    Symbol        *name;    // The constant itself.
    Expression    *value;   // It's value.
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class Variable : public Expression
{
  public:
    Variable(Symbol *varname, const Location& l );
   ~Variable();

    virtual void accept(Traversal *t) { t->traverse_variable(this);}

    Expression *dup0() const;
    void print(std::ostream& out) const;

    Symbol    *name;
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class FunctionCall : public Expression
{
  public:
    FunctionCall(Expression *func, const Location& l );
   ~FunctionCall();

    virtual void accept(Traversal *t) { t->traverse_call(this);}

    int  nArgs() const { return args.size(); }

    void addArg( Expression *arg );
    void addArgs( Expression *argList );

    Expression *dup0() const;
    void print(std::ostream& out) const;

    void findExpr( fnExprCallback cb );

    Expression   *function;
    ExprVector    args;
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class UnaryExpr : public Expression
{
  public:
    UnaryExpr( UnaryOp op, Expression *expr, const Location& l );
   ~UnaryExpr();

    virtual void accept(Traversal *t) { t->traverse_unary(this);}

    int precedence() const;

    Expression *operand() const { return _operand; }

    UnaryOp op() const { return uOp; }

    Expression *dup0() const;
    void print(std::ostream& out) const;

    void findExpr( fnExprCallback cb );

    UnaryOp    uOp;
    Expression *_operand;
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class BinaryExpr : public Expression
{
  public:
    BinaryExpr( BinaryOp op, Expression *lExpr, Expression *rExpr,
		const Location& l );
   ~BinaryExpr();

    virtual void accept(Traversal *t) { t->traverse_binary(this);}

    Expression *leftExpr() const { return _leftExpr; }
    Expression *rightExpr() const { return _rightExpr; }

    virtual int precedence() const;

    BinaryOp op() const { return bOp; }

    virtual Expression *dup0() const;
    virtual void print(std::ostream& out) const;

    void findExpr( fnExprCallback cb );

    BinaryOp    bOp;

    Expression *_leftExpr;
    Expression *_rightExpr;
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class TrinaryExpr : public Expression
{
  public:
    TrinaryExpr( Expression *cExpr, Expression *tExpr, Expression *fExpr,
		 const Location& l );
   ~TrinaryExpr();

    virtual void accept(Traversal *t) { t->traverse_trinary(this);}

    Expression *condExpr() const { return _condExpr; }
    Expression *trueExpr() const { return _trueExpr; }
    Expression *falseExpr() const { return _falseExpr; }

    int precedence() const { return 3; }

    Expression *dup0() const;
    void print(std::ostream& out) const;

    void findExpr( fnExprCallback cb );

    Expression *_condExpr;
    Expression *_trueExpr;
    Expression *_falseExpr;
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class AssignExpr : public BinaryExpr
{
  public:
    AssignExpr( AssignOp op, Expression *lExpr, Expression *rExpr,
		const Location& l );
   ~AssignExpr();

    virtual void accept(Traversal *t) { t->traverse_assign(this);}

    Expression *lValue() const { return leftExpr(); }
    Expression *rValue() const { return rightExpr(); }

    AssignOp op() const { return aOp; }

    int precedence() const { return 2; }

    Expression *dup0() const;
    void print(std::ostream& out) const;

    AssignOp    aOp;
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class RelExpr : public BinaryExpr
{
  public:
    RelExpr( RelOp op, Expression *lExpr, Expression *rExpr,
	     const Location& l );
   ~RelExpr();

    virtual void accept(Traversal *t) { t->traverse_rel(this);}

    int precedence() const;

    RelOp op() const { return rOp; }

    Expression *dup0() const;
    void print(std::ostream& out) const;

    RelOp    rOp;
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class CastExpr : public Expression
{
  public:
    CastExpr( Type *typeExpr, Expression *operand,
	      const Location& l );
   ~CastExpr();

    virtual void accept(Traversal *t) { t->traverse_cast(this);}

    Type *castType() { return castTo; }

    int precedence() const { return 14; }

    Expression *dup0() const;
    void print(std::ostream& out) const;

    void findExpr( fnExprCallback cb );

    Type        *castTo;
    Expression  *expr;    // The expression being cast.
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class SizeofExpr : public Expression
{
  public:
    SizeofExpr( Expression *operand, const Location& l );
    SizeofExpr( Type *operand, const Location& l );
   ~SizeofExpr();

    virtual void accept(Traversal *t) { t->traverse_sizeof(this);}

    int precedence() const { return 15; }

    Expression *dup0() const;
    void print(std::ostream& out) const;

    void findExpr( fnExprCallback cb );

    Type        *sizeofType;    // want the size of this type.
    Expression  *expr;          // want the size of this expression.
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class IndexExpr : public Expression
{
  // I should extend this to be able to handle
  // multi-dimensional arrays directly.

  public:
    IndexExpr( Expression *_array, Expression *sub,
               const Location& l );
   ~IndexExpr();

    virtual void accept(Traversal *t) { t->traverse_index(this);}

    //addSubscript( Expression *sub );
    Expression *subscript(int i);

    Expression *dup0() const;
    void print(std::ostream& out) const;

    void findExpr( fnExprCallback cb );

    Expression   *array;
    Expression   *_subscript;
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

Expression    *ReverseList( Expression* eList );

// For debugging, show the enumerated name.
char *nameOfExpressionType(ExpressionType type);
char *nameOfConstantType(ConstantType type);
char *nameOfAssignOp(AssignOp op);
char *nameOfRelOp(RelOp op);
char *nameOfUnaryOp(UnaryOp op);
char *nameOfBinaryOp(BinaryOp op);

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

void PrintRelOp(std::ostream& out, RelOp op);
void PrintBinaryOp(std::ostream& out, BinaryOp op);
void PrintUnaryOp(std::ostream& out, UnaryOp op);
void PrintAssignOp(std::ostream& out, AssignOp op);

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

#endif  /* EXPRESS_H */

