#ifndef LEX_H_INCLUDED
#define LEX_H_INCLUDED

#include "AST_Type.h"
#include "AST_Expr.h"
#include "Keywords.h"
#include "Project.h"
#include "Context.h"

#include <boost/smart_ptr.hpp>
#include <string>

/***************
Redefine YYSTYPE
***************/
#undef YYSTYPE
#define YYSTYPE TokenValue
typedef struct {
	//base type_base
	int				ival;
	unsigned int	uival;
	double			dval;
	float			fval;

	BuildinTypeSpec	typeSpec;
	h_type_base			type_base;
	h_decl			decl;
	h_expression		expr;
	HStatement		stmt;

	type_qualifier		typeQual;
	storage_type		storage;

	std::string		idenfitier;
	Semantic		semantic;
	ExpressionType	exprType;
	KeywordType		keywordType;
} TokenValue;

int yylex(YYSTYPE *lvalp, void* pLexer);

#define YYPARSE_PARAM param
#define YYLEX_PARAM param

#define TOKEN_VALUE (((Lexer*)this)->GetTokenValue())

#endif // LEX_H_INCLUDED
