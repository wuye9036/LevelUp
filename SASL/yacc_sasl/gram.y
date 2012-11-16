%{
#include "Lex.h"

#include "Semantic.h"
#include "TypeCode.h"
#include "AST_Type.h"
#include "AST_Decl.h"
#include "Symbol.h"

#include "cstrext.h"
#include <string>
#include <iostream>
#include <stdio.h>

#undef YY_DECL
#define YY_DECL int yylex(YYSTYLE* lvalp, void* pLexer)

int yyerror(const char*);

using namespace std;
%}

/***************************/
/*        Terminals        */
/***************************/

/* Literal Constants */
%token<ival>	INUM;
%token<uival>	UINUM;
%token<dval>	DNUM;
%token<fval>	FNUM;
%token<semantic> SEMANTIC;

/* Operations and Symbols */
%token			PLUS_EQ MINUS_EQ STAR_EQ DIV_EQ MOD_EQ
%token			B_AND_EQ B_OR_EQ B_XOR_EQ
%token			L_SHIFT_EQ R_SHIFT_EQ
%token			EQUAL LESS_EQ GRTR_EQ NOT_EQ

%token			RPAREN RBRCKT LBRACE RBRACE
%token			SEMICOLON COMMA ELLIPSIS

%token			LB_SIGN DOUB_LB_SIGN
%token			BACKQUOTE AT
%left			COMMA_OP
%right			EQ ASSIGN
%right			QUESTMARK COLON COMMA_SEP
%left			OR
%left			AND
%left			B_OR
%left			B_XOR
%left			B_AND
%left			COMP_EQ
%left			COMP_ARITH COMP_LESS COMP_GRTR LESS GRTR
%left			L_SHIFT R_SHIFT
%left			PLUS MINUS
%left			STAR DIV MOD
%right			CAST
%right			UNARY NOT B_NOT INDEXOF INCR DECR
%left			HYPERUNARY
%left			ARROW DOT LPAREN LBRCKT

/* Keywords */
%token<keywordType> IF ELSE FOR WHILE DO CONTINUE BREAK RETURN

/* Identifiers */
%token<idenfitier>	IDENTIFIER

/* Keywords And ReserveWorlds */
%token				MATRIX VECTOR STRUCT

/* Buildin Types */
%token<type> 		INT UINT FLOAT DOUBLE BOOL HALF VOID BUILDIN_VEC_TYPE BUILDIN_MAT_TYPE

/* Storage Type */
%token<storage>		EXTERN STATIC

/* Type Qual */
%token<typeQual> 	CONST UNIFORM VOLATILE
%type<typeQual>		T_TypeQual

%type<type>			T_SingleCompType

/******************/
/* None Terminals */
/******************/
%type<type>			NT_BuildinType NT_StructSpecifier

%type<decl>			NT_BlockDeclaration

%type<decl>			NT_InitializedDeclaratorList NT_InitializedDeclarator NT_InitializationList NT_InitializationClause
%type<decl>			NT_ParameterDeclaration

%type<expr>			NT_Initializer

%type<expr>			NT_Expression
%type<expr>			NT_ExpressionList

%type<expr>			NT_AssignmentExpression
%type<expr>			NT_ConditionExpression
%type<expr>			NT_OrExpression
%type<expr>			NT_AndExpression
%type<expr>			NT_BitOrExpression
%type<expr>			NT_BitXorExpression
%type<expr>			NT_BitAndExpression
%type<expr>			NT_EqualExpression
%type<expr>			NT_RelationExpression
%type<expr>			NT_ShiftExpression
%type<expr>			NT_AddExpression
%type<expr>			NT_MulExpression
%type<expr>			NT_CastExpression
%type<expr>			NT_UnaryExpression
%type<expr>			NT_PostfixExpression
%type<expr>			NT_PrimaryExpression
%type<expr>			NT_VariableExpression
%type<expr>			NT_ConstantExpression

%type<exprType>		T_AssignmentOperators T_EqualOperators T_AddOperators T_MulOperators T_ShiftOperators T_RelationOperators

%type<stmt>			NT_Statement NT_JumpStatement NT_DeclStatement NT_IterationStatement NT_ForInitializeStatement
%type<stmt>			NT_SelectionStatement NT_Condition NT_ExpressionStatement NT_CompoundStatement

/********************/
/*     Syntax	    */
/********************/
%type<type> Program

%start Program

%pure_parser

%%
Program:
	/* empty */
	{}
	;

T_AssignmentOperators:
	EQ
	{}
	;

T_EqualOperators:
	COMP_EQ
	{}
	;

T_AddOperators:
	PLUS
	{}
	;

T_MulOperators:
	STAR
	{}
	;

T_ShiftOperators:
	L_SHIFT
	{}
	;

T_RelationOperators:
	COMP_LESS
	{}
	;

T_SingleCompType:
	INT
	| UINT
	| HALF
	| FLOAT
	| DOUBLE
	| BOOL
	| VOID
	{ $$ = $1; }
	;

NT_BuildinType:
	T_SingleCompType
		{ $$ = $1; }
	| BUILDIN_VEC_TYPE
		{ $$ = $1; }
	| BUILDIN_MAT_TYPE
		{ $$ = $1; }
	| MATRIX COMP_LESS T_SingleCompType COMMA INUM COMMA INUM COMP_GRTR
		{
			BuildinTypeSpec typeSpec = ((BuildinType*)($3.get()))->typeCode;

			if ( (1 <= $5 && $5 <= 4 )
				&& ( 1 <= $7 && $7 <= 4))
			{
				$$ = HType(new BuildinType(GenMatType(typeSpec, $5, $7)));
			} else {
				$$ = HType(new BuildinType(BT_NoType));
			}
		}
	| VECTOR COMP_LESS T_SingleCompType COMMA INUM COMP_GRTR
		{
			BuildinTypeSpec typeSpec = ((BuildinType*)($3.get()))->typeCode;

			if ( 1 <= $5 && $5 <= 4 ) {
				$$ = HType(new BuildinType(GenVecType(typeSpec, $5)));
			} else {
				$$ = HType(new BuildinType(BT_NoType));
			}
		}
		;

T_TypeQual:
	CONST
	| UNIFORM
	| VOLATILE
	{ $$ = $1; }
	;

NT_InitializationClause:
	NT_AssignmentExpression
	{}
	| LBRACE RBRACE
	{}
	| LBRACE NT_InitializationList RBRACE
	{}
	;

NT_InitializationList:
	NT_InitializationClause
	{}
	| NT_InitializationList COMMA NT_InitializationClause
	{}
	;

NT_Initializer:
	EQ NT_InitializationClause
	{}
	| LPAREN NT_ExpressionList RPAREN
	{}
	;

NT_InitializedDeclarator:
	NT_Declarator
	{}
	| NT_Declarator NT_Initializer
	{}
	;

NT_InitializedDeclaratorList:
	NT_InitializedDeclarator
	{}
	| NT_InitializedDeclaratorList COMMA NT_InitializedDeclarator
	{}
	;

NT_Declarator:
	NT_DirectDeclarator
	{}
	;

NT_BlockDeclaration:
	NT_DeclarationSpecifierList NT_InitializedDeclaratorList
	{}
	;

NT_DeclarationSpecifier:
	NT_BuildinType
	{}
	| NT_StructSpecifier
	{}
	| T_TypeQual
	{}
	| IDENTIFIER
	{}
	;

NT_DeclarationSpecifierList:
	NT_DeclarationSpecifier
	{}
	| NT_DeclarationSpecifierList NT_DeclarationSpecifier
	{}
	;

NT_Declaration:
	NT_BlockDeclaration
	{}
	| NT_FunctionDefinition
	{}
	;

NT_DirectDeclarator:
	IDENTIFIER
	{}
	| NT_DirectDeclarator LPAREN NT_ParameterDeclarationClause RPAREN
	{}
	| NT_DirectDeclarator LBRCKT NT_Expression RBRCKT
	{}
	| NT_DirectDeclarator LBRCKT RBRCKT
	{}
	| LPAREN NT_Declarator RPAREN
	{}
	;

NT_DeclarationSequence:
	NT_DeclarationSequence NT_Declaration
	{}
	;

NT_ParameterDeclaration:
	NT_DeclarationSpecifier NT_Declarator
	{}
	| NT_DeclarationSpecifier NT_Declarator EQ NT_AssignmentExpression
	{}
	;

NT_ParameterDeclarationClause:
	/* EMPTY */
	{}
	| NT_ParameterDeclarationList
	{}
	;

NT_ParameterDeclarationList:
	NT_ParameterDeclaration
	{}
	| NT_ParameterDeclarationList COMMA NT_ParameterDeclaration
	{}
	;

NT_FunctionDefinition:
	NT_DeclarationSpecifierList NT_Declarator NT_CompoundStatement
	{}
	;

NT_MemberDeclarator:
	IDENTIFIER
	{}
	;

NT_MemberDeclaratorList:
	NT_MemberDeclarator
	{}
	| NT_MemberDeclaratorList NT_MemberDeclarator
	{}
	;

NT_MemberDeclaration:
	NT_DeclarationSpecifierList NT_MemberDeclaratorList COLON
	{}
	;

NT_MemberSpecification:
	NT_MemberDeclaration
	{}
	| NT_MemberSpecification NT_MemberDeclaration
	{}
	;

NT_StructSpecifier:
	STRUCT IDENTIFIER LBRACE NT_MemberSpecification RBRACE
	{
		$$ = HType(new StructType());
		StructType* pStructType = (StructType*)($$.get());
		pStructType->SetComponentList($3);
		pStructType->typeName = HSymbolEntry(new SymbolEntry());
		pStructType->typeName->pType = $$.get();
		pStructType->typeName->symbolName = $2;
		pStructType->typeName->symType = SYMT_UserType;
	}
	;

NT_VariableExpression:
	IDENTIFIER
	{
		VariableExpression* varExpr = new VariableExpression());
		varExpr->varSymbol = HSymbolEntry(new SymbolEntry());
		varExpr->expType = ET_Variable;
		$$ = HExpression(varExpr);
	}
	;

NT_ConstantExpression:
	INUM
	{
		ConstantExpressionT<int64_t>* constExpr = new ConstantExpressionT<int64_t>();
		constExpr->value = ival;
		constExpr->expType = ET_ConstInt;
		$$ = HExpression(constExpr);
	}
	| UINUM
	{
		ConstantExpressionT<int64_t>* constExpr = new ConstantExpressionT<int64_t>();
		constExpr->value = uival;
		constExpr->expType = ET_ConstUInt;
		$$ = HExpression(constExpr);
	}
	| DNUM
	{
		ConstantExpressionT<int64_t>* constExpr = new ConstantExpressionT<int64_t>();
		constExpr->value = dval;
		constExpr->expType = ET_ConstFloat;
		$$ = HExpression(constExpr);
	}
	| FNUM
	{
		ConstantExpressionT<int64_t>* constExpr = new ConstantExpressionT<int64_t>();
		constExpr->value = dval;
		constExpr->expType = ET_ConstFloat;
		$$ = HExpression(constExpr);
	}
	;

NT_PrimaryExpression:
	NT_ConstantExpression
	| NT_VariableExpression
	| LBRACE NT_Expression RBRACE
	;

NT_PostfixExpression:
	NT_PrimaryExpression
	| NT_PostfixExpression LBRCKT NT_Expression RBRCKT
	{ //exp[exp1], Array Operation
	}
	| NT_PostfixExpression LPAREN NT_Expression RPAREN
	{ //exp(exp1)
	}
	| NT_PostfixExpression LPAREN RPAREN
	{ //exp()
	}
	| NT_PostfixExpression LPAREN NT_ExpressionList RPAREN
	{ //exp( param1, param2, ... )
	}
	| NT_PostfixExpression DOT NT_VariableExpression
	{ //obj.member
	}
	| NT_PostfixExpression INCR
	{ //exp++
	}
	| NT_PostfixExpression DECR
	{ //exp--
	}
;

NT_UnaryExpression:
	NT_PostfixExpression
	{
	}
	| INCR NT_CastExpression
	{ //++exp
	}
	| DECR NT_CastExpression
	{ //--exp
	}
	| PLUS NT_CastExpression
	{ //+exp
	}
	| MINUS NT_CastExpression
	{ //-exp
	}
	;

NT_CastExpression:
	NT_UnaryExpression
	{
	}
	| LPAREN NT_DeclarationSpecifier RPAREN NT_Expression
	{ //(const int)exp
	}
	;

NT_MulExpression:
	NT_CastExpression
	{
	}
	| NT_MulExpression T_MulOperators NT_CastExpression
	{
	}
;

NT_AddExpression:
	NT_MulExpression
	{
	}
	| NT_AddExpression T_AddOperators NT_MulExpression
	{
	}
;

NT_ShiftExpression:
	NT_AddExpression
	{
	}
	| NT_ShiftExpression T_ShiftOperators NT_AddExpression
	{
	}
;

NT_RelationExpression:
	NT_ShiftExpression
	{
	}
	| NT_RelationExpression T_RelationOperators NT_ShiftExpression
	{
	}
;

NT_EqualExpression:
	NT_RelationExpression
	{
	}
	| NT_EqualExpression T_EqualOperators NT_RelationExpression
	{
	}
;

NT_BitAndExpression:
	NT_RelationExpression
	{
	}
	| NT_BitAndExpression B_AND NT_EqualExpression
	{
	}
	;

NT_BitXorExpression:
	NT_AndExpression
	{
	}
	| NT_BitXorExpression B_XOR NT_BitAndExpression
	{
	}
	;

NT_BitOrExpression:
	NT_BitOrExpression
	{
	}
	| NT_BitOrExpression B_OR NT_BitXorExpression
	{
	}
	;

NT_AndExpression:
	NT_BitOrExpression
	{
	}
	| NT_AndExpression AND NT_BitOrExpression
	{
	}
	;

NT_OrExpression:
	NT_AndExpression
	{
	}
	| NT_OrExpression OR NT_AndExpression
	{
	}
;

NT_ConditionExpression:
	NT_OrExpression
	{
	}
	| NT_OrExpression QUESTMARK NT_Expression COLON NT_AssignmentExpression
	{
	}
	;

NT_AssignmentExpression:
	NT_ConditionExpression
	{
	}
	| NT_OrExpression T_AssignmentOperators NT_AssignmentExpression
	{
	}
	;

NT_ExpressionList:
	NT_Expression
	| NT_ExpressionList COMMA NT_Expression
;

NT_Expression:
	NT_AssignmentExpression
	{
	}
;

NT_CompoundStatement:
	LBRACE RBRACE
	{}
	| LBRACE NT_StatementList RBRACE
	{}
;

NT_ExpressionStatement:
	SEMICOLON
	{}
	| NT_Expression SEMICOLON
	{}
	;

NT_Condition:
	NT_Expression
	{}
	| NT_DeclarationSpecifier NT_Declarator EQ NT_AssignmentExpression
	{}
	;

NT_SelectionStatement:
	IF LPAREN NT_Condition RPAREN NT_Statement
	{}
	| IF LPAREN NT_Condition RPAREN NT_Statement ELSE NT_Statement
	{}
	;

NT_ForInitializeStatement:
	NT_ExpressionStatement
	{}
	| NT_DeclStatement
	{}
	;

NT_IterationStatement:
	WHILE LPAREN NT_Condition RPAREN NT_Statement
	{}
	| DO NT_Statement WHILE LPAREN NT_Expression RPAREN SEMICOLON
	{}
	| FOR LPAREN NT_ForInitializeStatement NT_Condition SEMICOLON NT_Expression RPAREN NT_Statement
	{}
	;

NT_DeclStatement:
	NT_BlockDeclaration
	{}
	;

NT_JumpStatement:
	CONTINUE SEMICOLON
	{}
	| BREAK SEMICOLON
	{}
	| RETURN SEMICOLON
	{}
	| RETURN NT_Expression SEMICOLON
	{}
	;

NT_StatementList:
	NT_Statement
	{}
	| NT_StatementList NT_Statement
	{}
;

NT_Statement:
	NT_CompoundStatement
	{}
	| NT_ExpressionStatement
	{}
	| NT_SelectionStatement
	{}
	| NT_IterationStatement
	{}
	| NT_DeclStatement
	{}
	| NT_JumpStatement
	{}
;
%%
