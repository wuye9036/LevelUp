#ifndef YYLEXER_H_INCLUDED
#define YYLEXER_H_INCLUDED

#include <FlexLexer.h>
#include "Lex.h"

#include <iostream>

class Lexer: public yyFlexLexer
{
public:
	Lexer(std::istream* istr, std::ostream* ostr, unit* pUnit)
		: yyFlexLexer(istr, ostr), pTokenValue_(NULL), pUnit_(pUnit)
	{}

	void SetTokenValue(TokenValue* pTV){
		pTokenValue_ = pTV;
	}

	TokenValue* GetTokenValue(){
		return pTokenValue_;
	}

private:
	TokenValue* pTokenValue_;
	unit*		pUnit_;
};

#endif // YYLEXER_H_INCLUDED
