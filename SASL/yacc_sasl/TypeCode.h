#ifndef TYPECODE_H_INCLUDED
#define TYPECODE_H_INCLUDED

#include <stdlib.h>
#include <string>

/****************************************
BuildinType Specifications
****************************************/
typedef unsigned long BuildinTypeSpec;

//Regularation of Type Value Definition
//31-24 bits:Base Type Name
//23-20 bits: Template Name
//21-16 bits:  Sign Indicator
//15-8 bits: First Dimension of Vector(Matrix), Zero Start
//7-0 bits: Second Dimension of Matrix, Zero Start

const BuildinTypeSpec BT_NoType		= 0x00000000;  // no type provided

const BuildinTypeSpec BT_Void		= 0x01000000;
const BuildinTypeSpec BT_Half		= 0x02000000;
const BuildinTypeSpec BT_Float		= 0x03000000;
const BuildinTypeSpec BT_Double		= 0x04000000;
const BuildinTypeSpec BT_Int		= 0x05000000;
const BuildinTypeSpec BT_UInt		= 0x06000000;
const BuildinTypeSpec BT_Boolean	= 0x07000000;

const BuildinTypeSpec BT_Struct		= 0x10000000;
const BuildinTypeSpec BT_UserType  	= 0xF0000000;

const BuildinTypeSpec BT_Vector		= 0x00100000;
const BuildinTypeSpec BT_Matrix		= 0x00200000;

const BuildinTypeSpec BT_Signed		= 0x00010000;
const BuildinTypeSpec BT_Unsigned	= 0x00020000;

const BuildinTypeSpec BT_1D0		= 0x00000000;
const BuildinTypeSpec BT_1D1		= 0x00000100;
const BuildinTypeSpec BT_1D2		= 0x00000200;
const BuildinTypeSpec BT_1D3		= 0x00000300;

const BuildinTypeSpec BT_2D0		= 0x00000000;
const BuildinTypeSpec BT_2D1		= 0x00000001;
const BuildinTypeSpec BT_2D2		= 0x00000002;
const BuildinTypeSpec BT_2D3		= 0x00000003;

const BuildinTypeSpec BT_BaseMask		= 0xFF000000;
const BuildinTypeSpec BT_TemplateMask	= 0x00F00000;
const BuildinTypeSpec BT_SignMask		= 0x000F0000;
const BuildinTypeSpec BT_1stDimMask		= 0x0000FF00;
const BuildinTypeSpec BT_2ndDimMask		= 0x000000FF;

const BuildinTypeSpec BT_TypeError	= 0xFFFFFFFF;

/*******************************************
BuildinTypeSpec Helper Functions
*******************************************/
BuildinTypeSpec GetComponentType(BuildinTypeSpec type);

BuildinTypeSpec GenVecType(BuildinTypeSpec base, int len);
BuildinTypeSpec GenMatType(BuildinTypeSpec base, int len1, int len2);

bool IsVectorType(BuildinTypeSpec type);
bool IsMatrxiType(BuildinTypeSpec type);

int VectorSize(BuildinTypeSpec typeSpec);
void MatrixSize(BuildinTypeSpec typeSpec,int& size1d, int& size2d);

bool IsStructType(BuildinTypeSpec typeSpec);
bool IsUserType(BuildinTypeSpec typeSpec);
/****************************************
Type Qualifiers
****************************************/
class expression;

struct type_qualifier{
   unsigned short tq;
   expression * vout;
   bool operator == (unsigned int x)const {return x==tq;}
   bool operator == (const type_qualifier &x)const {return x.tq==tq;}
   bool operator !=(const type_qualifier &x)const {return tq!=x.tq;}
   bool operator !=(const unsigned int x) const {return tq!=x;}

   void init (unsigned short t){tq=t;vout=NULL;}
   void init (unsigned short t,expression * e){tq=t;vout=e;}
   type_qualifier operator &(unsigned int x)const {type_qualifier ret(*this);ret&=x;return ret;}
   type_qualifier operator |(unsigned int x)const {type_qualifier ret(*this);ret|=x;return ret;}
   type_qualifier operator &(const type_qualifier &x)const {type_qualifier ret(*this);ret&=x;return ret;}
   type_qualifier operator |(const type_qualifier &x)const {type_qualifier ret(*this);ret|=x;return ret;}
   type_qualifier& operator |=(unsigned int x){tq|=x;return *this;}
   type_qualifier& operator &=(unsigned int x){tq&=x;return *this;}
   type_qualifier operator ~()const {
      type_qualifier ret(*this);
      ret.tq=~ret.tq;
      return ret;
   }
   type_qualifier& operator |=(const type_qualifier &x){
      tq|=x.tq;
      if (x.vout&&!vout) {
         vout=x.vout;
      }
      return *this;
   }
   type_qualifier& operator &=(const type_qualifier &x){
      tq&=x.tq;
      return *this;
   }

   bool HasQual(type_qualifier ref) {
	  return ((*this) & ref) == ref;
   }

   static type_qualifier ReturnNone() {type_qualifier ret;ret.init(0x0000);return ret;}
   static type_qualifier ReturnConst() {type_qualifier ret;ret.init(0x0001);return ret;}
   static type_qualifier ReturnVolatile() {type_qualifier ret;ret.init(0x0002);return ret;}
   static type_qualifier ReturnUniform() {type_qualifier ret;ret.init(0x004);return ret;}
   static type_qualifier ReturnShared() {type_qualifier ret; ret.init(0x008); return ret;}
   static type_qualifier ReturnNoInteroperation() {type_qualifier ret; ret.init(0x010); return ret;}


};

const type_qualifier TQ_None=type_qualifier::ReturnNone();
const type_qualifier TQ_Const=type_qualifier::ReturnConst();
const type_qualifier TQ_Volatile=type_qualifier::ReturnVolatile();
const type_qualifier TQ_Uniform=type_qualifier::ReturnUniform();
const type_qualifier TQ_Shared=type_qualifier::ReturnShared();
const type_qualifier TQ_NoInteroperation=type_qualifier::ReturnNoInteroperation();

//typedef PtrList<type_qualifier> TypeQualList;

/*************************************
Storage Types
*************************************/
enum storage_type
{
    ST_None  = 0,
    ST_Static,
    ST_Typedef,
    ST_Extern
};

/***********************************
Advanced Types Codec
***********************************/
enum TypeKind
{
    TK_Simple = 0,
    TK_TypeDef,
    TK_UserType
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
enum type_type
{
    TT_Simple,        // a simple base type, T
    TT_Array,       // an array of T
    TT_Function,    // <args> -> <result>
};

std::string BuildinTypeToString(BuildinTypeSpec typeSpec);
std::string TypeQualToString(type_qualifier typeQual);
std::string StorageTypeToString(storage_type st);

#endif // TYPECODE_H_INCLUDED
