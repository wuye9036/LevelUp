
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
    o+     File:         decl.h
    o+
    o+     Programmer:   Shaun Flisakowski
    o+     Date:         Aug 9, 1998
    o+
    o+     A high-level view of types / declarations.
    o+
    o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

#ifndef    DECL_H
#define    DECL_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>

#include "symbol.h"
#include "callback.h"
#include "location.h"

#include "dup.h"

class Constant;
class Expression;
class EnumConstant;
class SplitTreeBuilder;

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

typedef unsigned long BaseTypeSpec;

//Regularation of Type Value Definition
//31-24 bits:Base Type Name
//23-20 bits: Template Name
//21-16 bits:  Sign Indicator
//15-8 bits: First Dimension of Vector(Matrix), Zero Start
//7-0 bits: Second Dimension of Matrix, Zero Start

const BaseTypeSpec BT_NoType	= 0x00000000;  // no type provided

const BaseTypeSpec BT_Void		= 0x01000000;
const BaseTypeSpec BT_Half		= 0x02000000;
const BaseTypeSpec BT_Float		= 0x03000000;
const BaseTypeSpec BT_Double	= 0x04000000;
const BaseTypeSpec BT_Int		= 0x05000000;
const BaseTypeSpec BT_UInt		= 0x06000000;
const BaseTypeSpec BT_Boolean	= 0x07000000;

const BaseTypeSpec BT_Struct	= 0x10000000;
const BaseTypeSpec BT_UserType  = 0xF0000000;

const BaseTypeSpec BT_Vector	= 0x00100000;
const BaseTypeSpec BT_Matrix	= 0x00200000;

const BaseTypeSpec BT_Signed	= 0x00010000;
const BaseTypeSpec BT_Unsigned	= 0x00020000;

const BaseTypeSpec BT_1D0		= 0x00000000;
const BaseTypeSpec BT_1D1		= 0x00000100;
const BaseTypeSpec BT_1D2		= 0x00000200;
const BaseTypeSpec BT_1D3		= 0x00000300;

const BaseTypeSpec BT_2D0		= 0x00000000;
const BaseTypeSpec BT_2D1		= 0x00000001;
const BaseTypeSpec BT_2D2		= 0x00000002;
const BaseTypeSpec BT_2D3		= 0x00000003;

const BaseTypeSpec BT_BaseMask		= 0xFF000000;
const BaseTypeSpec BT_TemplateMask	= 0x00F00000;
const BaseTypeSpec BT_SignMask		= 0x000F0000;
const BaseTypeSpec BT_1stDimMask	= 0x0000FF00;
const BaseTypeSpec BT_2ndDimMask	= 0x000000FF;

const BaseTypeSpec BT_Float2       = BT_Float | BT_1D1;
const BaseTypeSpec BT_Float3       = BT_Float | BT_1D2;
const BaseTypeSpec BT_Float4       = BT_Float | BT_1D3;

const BaseTypeSpec BT_TypeError    = 0xFFFFFFFF;

BaseTypeSpec GetBaseType(BaseTypeSpec type){
	return type & BT_BaseMask;
}

BaseTypeSpec VectorType(BaseTypeSpec base, unsigned int len){
	return base | ((len-1) << 16) | BT_Vector;
}

BaseTypeSpec MatrixType(BaseTypeSpec base, unsigned int len1, unsigned int len2){
	return base | ((len1-1) << 16)) | (len2-1) | BT_Matrix;
}

bool IsVectorType(BaseTypeSpec type)
{
	return (type & BT_TemplateMask) == BT_Vector;
}

bool IsMatrxiType(BaseTypeSpec type)
{
	return (type & BT_TemplateMask) == BT_Matrix;
}

int VectorSize(BaseTypeSpec typeSpec) {
	return ((typeSpec & BT_1stDimMask) >> 16) + 1;
}

void MatrixSize(BaseTypeSpec typeSpec,int& size1d, int& size2d)
{
	size1d = ((typeSpec & BT_1stDimMask) >> 16) + 1;
	size2d = (typeSpec & BT_2ndDimMask) + 1;
}

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
struct TypeQual{
   unsigned short tq;
   Expression * vout;
   bool operator == (unsigned int x)const {return x==tq;}
   bool operator == (const TypeQual &x)const {return x.tq==tq;}
   bool operator !=(const TypeQual &x)const {return tq!=x.tq;}
   bool operator !=(const unsigned int x) const {return tq!=x;}

   void init (unsigned short t){tq=t;vout=NULL;}
   void init (unsigned short t,Expression * e){tq=t;vout=e;}
   TypeQual operator &(unsigned int x)const {TypeQual ret(*this);ret&=x;return ret;}
   TypeQual operator |(unsigned int x)const {TypeQual ret(*this);ret|=x;return ret;}
   TypeQual operator &(const TypeQual &x)const {TypeQual ret(*this);ret&=x;return ret;}
   TypeQual operator |(const TypeQual &x)const {TypeQual ret(*this);ret|=x;return ret;}
   TypeQual& operator |=(unsigned int x){tq|=x;return *this;}
   TypeQual& operator &=(unsigned int x){tq&=x;return *this;}
   TypeQual operator ~()const {
      TypeQual ret(*this);
      ret.tq=~ret.tq;
      return ret;
   }
   TypeQual& operator |=(const TypeQual &x){
      tq|=x.tq;
      if (x.vout&&!vout) {
         vout=x.vout;
      }
      return *this;
   }
   TypeQual& operator &=(const TypeQual &x){
      tq&=x.tq;
      return *this;
   }

   static TypeQual ReturnNone() {TypeQual ret;ret.init(0x0000);return ret;}
   static TypeQual ReturnConst() {TypeQual ret;ret.init(0x0001);return ret;}
   static TypeQual ReturnVolatile() {TypeQual ret;ret.init(0x0002);return ret;}
   static TypeQual ReturnUniform() {TypeQual ret;ret.init(0x004);return ret;}
   static TypeQual ReturnShared() {TypeQual ret; ret.init(0x008); return ret;}
   static TypeQual ReturnNoInteroperation() {TypeQual ret; ret.init(0x010); return ret;}
};

const TypeQual TQ_None=TypeQual::ReturnNone();
const TypeQual TQ_Const=TypeQual::ReturnConst();
const TypeQual TQ_Volatile=TypeQual::ReturnVolatile();
const TypeQual TQ_Uniform=TypeQual::ReturnUniform();
const TypeQual TQ_Shared=TypeQual::ReturnShared();
const TypeQual TQ_NoInteroperation=TypeQual::ReturnNoInteroperation();

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
enum StorageType
{
    ST_None  = 0,
    ST_Static,
    ST_Typedef,
    ST_Extern
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
enum FlowControlAttribute
{
	FCA_None = 0,
	FCA_Flatten,
	FCA_Branch,
	FCA_Unroll,
	FCA_Loop,
	FCA_Call,
	FCA_Forcase
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
enum SemanticBaseType
{
	SBT_None = 0,
	//VS Input
	SBT_Binormal,
	SBT_BlendIndices,
	SBT_BlendWeight,
	SBT_Color,			//VS Input, VS Output, PS Input, PS Output
	SBT_Normal,
	SBT_Position,		//VS Input, VS Output
	SBT_PositionT,
	SBT_PSize,			//VS Output
	SBT_Tangent,
	SBT_Texcoord,		//VS Input, VS Output, PS Input

	//VS Output
	SBT_Fog,
	SBT_TessFactor,

	//PS Input
	SBT_VFace,
	SBT_VPos,

	//PS Output
	SBT_Depth,

	//DX10
	SBT_SV_ClipDistance,
	SBT_SV_CullDistance,
	SBT_SV_Coverage,
	SBT_SV_IsFrontFace,
	SBT_SV_Position,
	SBT_SV_RenderTargetArrayIndex,
	SBT_SV_SampleIndex,
	SBT_SV_Target,
	SBT_SV_ViewPortArrayIndex,
	SBT_SV_InstanceID,
	SBT_SV_PrimitiveID,
	SBT_SV_VertexID
};

typedef unsigned int SemanticType;

SemanticBaseType BaseSemanticType(SemanticType smt)
{
	return static_cast<SemanticBaseType>(smt & 0x0000FFFF);
}

bool IsBaseSemantic(SemanticType smt, SemanticBaseType sbt){
	return sbt == BaseSemanticType(smt);
}

int SemanticUsage(SemanticType smt)
{
	return static_cast<int>( (smt & 0xFFFF0000) >> 16);
}

SemanticType GetSemanticType(SemanticBaseType sbt, int usage)
{
	if (usage < 0) return 0;
	return static_cast<SemanticType>(sbt | (usage << 16));
}

struct RegisterName
{
	char regName;
	char regUsage;
};

struct Packoffset
{
	char regName;
	char regUsage;
	char components;
};
// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
enum TypeKind
{
    TK_Base = 0,
    TK_TypeDef,
    TK_UserType
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
enum TypeType
{
    TT_Base,        // a simple base type, T
    TT_Array,       // an array of T
    TT_Function,    // <args> -> <result>
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

class Decl;

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class StructDef
{
  public:
    StructDef( bool _is_union = false );
    ~StructDef();

    bool    isUnion() const { return _isUnion; }

    StructDef*   dup0() const;
    StructDef*   dup() const;    // deep-copy

    void    print(std::ostream& out, Symbol *name, int level) const;

    void    findExpr( fnExprCallback cb );

    void    addComponent(Decl *comp);

    void    registerComponents();

    // Lookup this symbol in this struct/union and set its entry
    // if its a component of it.
    bool    lookup( Symbol* sym ) const;

    bool            _isUnion;
    Symbol         *tag;

    int             size;          // size of the array.
    int             nComponents;
    Decl          **components;

  private:
    Decl   *lastDecl();
};
// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

class Type;
typedef Dup<Type> DupableType;

class Type : public DupableType
{
  public:
    Type(TypeType _type=TT_Base);
    virtual ~Type();
    virtual Type ** getSubType() {return NULL;}
    virtual int     precedence() const { return 16; }
    virtual Type*   dup0() const =0;    // deep-copy

    virtual Type*   extend(Type *extension) { assert(0); return NULL; }

    // This function handles the complexity of printing a type.
    virtual void printType( std::ostream& out, Symbol *name,
			    bool showBase, int level, bool rawType=false/*prevents cpu-specific transforms*/ ) const;

    virtual void printBase( std::ostream& out, int level ) const {}
    virtual void printRawBase( std::ostream& out, int level ) const {printBase(out,level);}
    virtual void printBefore( std::ostream& out, Symbol *name, int level) const {}
    virtual void printAfter( std::ostream& out ) const {}

    virtual void printForm(std::ostream& out) const { out << "-[ABT]"; }

    virtual void registerComponents() {}

    virtual void findExpr( fnExprCallback cb ) {}

    virtual bool lookup( Symbol* sym ) const { return false; }

    virtual TypeQual getQualifiers( void ) const = 0;
    virtual BaseType *getBase( void ) = 0;

    bool    isBaseType() const { return (type == TT_Base); }
    bool    isFunction() const { return (type == TT_Function); }
    bool    isArray() const { return (type == TT_Array); }

    // Delete all types stored in this list.
    static void    DeleteTypeList(Type* typelist);

    TypeType        type;

    // Temporary - is moved into the declaration (Decl).
    StorageType     storage;

  private:
    Type*           link;    // For linking all type classes togather.
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class BaseType : public Type
{
  public:
    BaseType( BaseTypeSpec = BT_NoType );
    BaseType( StructDef *sd );
    BaseType( EnumDef *ed );
    ~BaseType();

    Type* dup0() const;    // deep-copy

    Type* extend(Type *extension) { assert(0); return NULL; }

    void printBase( std::ostream& out, int level ) const;
    void printBefore( std::ostream& out, Symbol *name, int level) const;
    void printAfter( std::ostream& out ) const;

    void printForm(std::ostream& out) const;

    void registerComponents();

    bool lookup( Symbol* sym ) const;

    TypeQual getQualifiers( void ) const;

    BaseType *getBase( void );
    BaseType& operator = (const BaseType &b);

    BaseTypeSpec    typemask;

    TypeQual        qualifier;

    Symbol          *tag;        // tag for struct/union/enum
    Symbol          *typeName;   // typedef name for a UserType

    StructDef       *stDefn;     // optional definition of struct/union

};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class ArrayType : public Type
{
  public:
    ArrayType(TypeType t, Expression *s)
          : Type(t), subType(NULL), size(s)
          { assert(t == TT_Stream || t == TT_Array); };

    ~ArrayType();

    Type* dup0() const;    // deep-copy

    Type* extend(Type *extension);
    virtual Type ** getSubType() {return &subType;}
    bool printStructureStreamHelperType( std::ostream& out, const std::string& name, bool raw ) const {
      return false;
    }

    void printBase( std::ostream& out, int level ) const;
    void printBefore( std::ostream& out, Symbol *name, int level) const;
    void printAfter( std::ostream& out ) const;

    void printForm(std::ostream& out) const;

    void registerComponents() { if (subType) subType->registerComponents(); }

    void findExpr( fnExprCallback cb );

    bool lookup( Symbol* sym ) const;

    TypeQual getQualifiers( void ) const;
    BaseType *getBase( void );

    Type           *subType;

    Expression     *size;
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class FunctionType : public Type
{
  public:
    FunctionType(Decl *args_list = NULL);
    ~FunctionType();

    Type* dup0() const;    // deep-copy

    Type* extend(Type *extension);
    virtual Type ** getSubType() {return &subType;}

    bool printStructureStreamHelperType( std::ostream& out,
                                         const std::string& name,
                                         bool raw) const {
      return false;
    }

    void printBase( std::ostream& out, int level ) const;
    void printBefore( std::ostream& out, Symbol *name, int level) const;
    void printAfter( std::ostream& out ) const;

    void printForm(std::ostream& out) const;

    void registerComponents() { if (subType) subType->registerComponents(); }

    void addArg(Decl *arg);
    void addArgs(Decl *args);

    void findExpr( fnExprCallback cb );

    bool lookup( Symbol* sym ) const;

    TypeQual getQualifiers( void ) const;
    SemanticBaseType getSemantic( void ) const;
    BaseType *getBase( void );

    unsigned int    nArgs;
    unsigned int    size;
    Decl          **args;

    Type           *subType;    // The return type
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class Decl
{
  public:
    Decl( Symbol* sym = (Symbol*) NULL );
    Decl( Type* type );
    virtual ~Decl();

    Type*   extend( Type* type );

    bool    isTypedef() const { return (storage == ST_Typedef); }
    bool    isStatic() const { return (storage == ST_Static); }
    bool    isArray() const { return (form->type == TT_Array); }

    void    clear();

    Decl*   dup0() const;
    Decl*   dup() const;        // deep-copy

    void    copy(const Decl& decl);    // shallow copy

    void print(std::ostream& out, bool showBase, int level=0) const;
    void printBase(std::ostream& out, Symbol *name, bool showBase, int level) const;

    void    findExpr( fnExprCallback cb );

    // TIM: adding DAG-building for kernel splitting support
    virtual void buildSplitTree( SplitTreeBuilder& ioBuilder );

    bool lookup( Symbol* sym ) const;

    StorageType     storage;

	SemanticQual	semantic; //ie: NORMAL0

	RegisterName	reg;

	Packoffset		pack;

    Type            *form;    // i.e., int *x[5]

    Symbol          *name;    // The symbol being declared.

    Expression      *initializer;

    Decl            *next;    // For linking into lists
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

typedef    std::vector<Decl*>    DeclVector;

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

Decl*	ReverseList( Decl* dList );

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

#endif  /* DECL_H */

