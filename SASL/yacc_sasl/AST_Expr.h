#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

#include <eflib/include/platform.h>

enum ExpressionType
{
	//啥玩意没有
	ET_Void,

	//大类
	ET_Constant,
	ET_Variable,
	ET_Unary,
	ET_Binary,
	ET_Trinary,

	//Constant
	ET_ConstBool,
	ET_ConstInt,
	ET_ConstUInt,
	ET_ConstFloat,
	ET_ConstDouble,
	ET_ConstArray,

	//Unary
	ET_Positive,
	ET_Negative,
	ET_BitNot,
	ET_Not,
	ET_PreInc,
	ET_PostInc,
	ET_PreDec,
	ET_PostDec,

	//Binary
	ET_Plus,
	ET_Minus,
	ET_Mul,
	ET_Div,
	ET_Mod,

	ET_Shl,
	ET_Shr,
	ET_BitAnd,
	ET_BitOr,
	ET_BitXor,

	ET_And,
	ET_Or,

	ET_Comma,

	ET_Member,

	ET_Assign,
	ET_PlusAssign,
	ET_MinusAssign,
	ET_MulAssign,
	ET_DivAssign,
	ET_ModAssign,

	ET_ShlAssign,
	ET_ShrAssign,

	ET_BitAndAssign,
	ET_BitOrAssign,
	ET_BitXorAssign,

	ET_Equal,
	ET_NotEqual,
	ET_Less,
	ET_LessEqual,
	ET_Great,
	ET_GreatEqual,

	ET_Cast,
	ET_Index
};

template <class T>
struct TypeToConstantType{
	static const ExpressionType type = ET_Void;
};

template<> struct TypeToConstantType<int64_t>{
	static const ExpressionType type = ET_ConstInt;
};

template<> struct TypeToConstantType<uint64_t>{
	static const ExpressionType type = ET_ConstUInt;
};

template<> struct TypeToConstantType<float>{
	static const ExpressionType type = ET_ConstFloat;
};

template<> struct TypeToConstantType<double>{
	static const ExpressionType type = ET_ConstDouble;
};

template<> struct TypeToConstantType<bool>{
	static const ExpressionType type = ET_ConstBool;
};

class expression
{
public:
	virtual void textStreamOutput(std::ostream& os);

	//Location location;
	type_base*	 retType;

	expression*	next; //for expression blocks.
	ExpressionType expType;
};

class VariableExpression : public expression
{
public:
	h_symbol_entry varSymbol;
};

class ConstantExpression : public expression
{
	virtual void textStreamOutput(std::ostream& os);
};

template<class T>
class ConstantExpressionT: public expression
{
	virtual void textStreamOutput(std::ostream& os);

	T value;
	std::string orgStr;
};

class UnaryExpression : public expression
{
	virtual void textStreamOutput(std::ostream& os);
	h_expression operand;
};

class BinaryExpression : public expression
{
	virtual void textStreamOutput(std::ostream& os);
	h_expression lexpr;
	h_expression rexpr;
};

class TrinaryExpression : public expression
{
	virtual void textStreamOutput(std::ostream& os);
	h_expression predictor;
	h_expression trueExpr;
	h_expression falseExpr;
};

class CastExpression: public expression
{
	virtual void textStreamOutput(std::ostream& os);
	h_type_base		type;
	h_expression expr;
};

std::string ExpressionTypeToString(ExpressionType type);
#endif // EXPRESSION_H_INCLUDED
