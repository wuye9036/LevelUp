/**
该文件保存了Lex和Yacc中需要的辅助函数的定义。
**/

#include "YYParser.h"
#include "YYLexer.h"
#include "Lex.h"

int yyerror(const char* err){
	return 0;
}

int yylex(YYSTYPE *lvalp, void* pLexer)
{
	((Lexer*)pLexer)->SetTokenValue(lvalp);
	return ((Lexer*)pLexer)->yylex();
}
