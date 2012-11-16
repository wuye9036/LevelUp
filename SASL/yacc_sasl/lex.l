%{
#include "TypeCode.h"
#include "AST_Decl.h"
#include "AST_Type.h"

#include "YYLexer.h"

#include "gram.tab.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Lex.h"

#undef YY_DECL

int err_tok;

using std::cin;
using std::cout;
%}

%option noyywrap
%option c++

DOT			"."
DIGIT		[0-9]
DIGITSEQ	[0-9]+
ALPHA		[a-zA-Z_]
ALPHANUM	{ALPHA}|{DIGIT}

EXPONENT	[Ee][+-]? {DIGITSEQ}
FRACTION	{DIGIT}* {DOT} {DIGITSEQ} | {DIGITSEQ} {DOT} {DIGITSEQ}?

%%
<INITIAL>{DIGITSEQ} {
    long i = strtol(yytext, (char**) NULL, 0);
	TOKEN_VALUE->ival = i;
    return(err_tok = INUM);
}


<INITIAL>"if" {
	TOKEN_VALUE->keywordType = KT_IF;
	return (err_tok = IF);
}

<INITIAL>"else" {
	TOKEN_VALUE->keywordType = KT_ELSE;
	return (err_tok = ELSE);
}

<INITIAL>"for" {
	TOKEN_VALUE->keywordType = KT_FOR;
	return (err_tok = FOR);
}

<INITIAL>"while" {
	TOKEN_VALUE->keywordType = KT_WHILE;
	return (err_tok = WHILE);
}

<INITIAL>"do" {
	TOKEN_VALUE->keywordType = KT_DO;
	return (err_tok = DO);
}

<INITIAL>"break" {
	TOKEN_VALUE->keywordType = KT_BREAK;
	return (err_tok = BREAK);
}

<INITIAL>"continue" {
	TOKEN_VALUE->keywordType = KT_CONTINUE;
	return (err_tok = CONTINUE);
}

<INITIAL>"return" {
	TOKEN_VALUE->keywordType = KT_RETURN;
	return (err_tok = RETURN);
}

<INITIAL>"extern"	{
	TOKEN_VALUE->storage = ST_Extern;
	return (err_tok = EXTERN);
}

<INITIAL>"static"	{
	TOKEN_VALUE->storage = ST_Static;
	return (err_tok = STATIC);
}

<INITIAL>"const"    {
    TOKEN_VALUE->typeQual = TQ_Const;
    return(err_tok = CONST);
}

<INITIAL>"uniform"	{
	TOKEN_VALUE->typeQual = TQ_Uniform;
	return(err_tok = UNIFORM);
}

<INITIAL>"volatile"	{
	TOKEN_VALUE->typeQual = TQ_Volatile;
	return(err_tok = VOLATILE);
}

<INITIAL>"void"		{
	TOKEN_VALUE->type = HType(new BuildinType(BT_Void));
	return (err_tok = VOID);
}
<INITIAL>"int"      {
    TOKEN_VALUE->type = HType(new BuildinType(BT_Int));
    return(err_tok = INT);
}
<INITIAL>"uint"		{
	TOKEN_VALUE->type = HType(new BuildinType(BT_UInt));
	return (err_tok = UINT);
}
<INITIAL>"float"    {
    TOKEN_VALUE->type = HType(new BuildinType(BT_Float));
    return(err_tok = FLOAT);
}
<INITIAL>"half"		{
    TOKEN_VALUE->type = HType(new BuildinType(BT_Half));
    return(err_tok = HALF);
}
<INITIAL>"double"		{
    TOKEN_VALUE->type = HType(new BuildinType(BT_Double));
    return(err_tok = DOUBLE);
}
<INITIAL>"bool"		{
	TOKEN_VALUE->type = HType(new BuildinType(BT_Boolean));
	return(err_tok = BOOL);
}

<INITIAL>"int"[1-4]		{
	int n = yytext[yyleng - 1] - '0';
	TOKEN_VALUE->type = HType(new BuildinType(GenVecType(BT_Int, n)));
	return(err_tok = BUILDIN_VEC_TYPE);
}

<INITIAL>"uint"[1-4]	{
	int n = yytext[yyleng - 1] - '0';
	TOKEN_VALUE->type = HType(new BuildinType(GenVecType(BT_UInt, n)));
	return(err_tok = BUILDIN_VEC_TYPE);
}

<INITIAL>"half"[1-4]	{
    int n = yytext[yyleng - 1] - '0';
	TOKEN_VALUE->type = HType(new BuildinType(GenVecType(BT_Half, n)));
	return(err_tok = BUILDIN_VEC_TYPE);
}

<INITIAL>"float"[1-4]	{
    int n = yytext[yyleng -1] - '0';
	TOKEN_VALUE->type = HType(new BuildinType(GenVecType(BT_Float, n)));
	return(err_tok = BUILDIN_VEC_TYPE);
}

<INITIAL>"double"[1-4]	{
    int n = yytext[yyleng -1] - '0';
	TOKEN_VALUE->type = HType(new BuildinType(GenVecType(BT_Double, n)));
	return(err_tok = BUILDIN_VEC_TYPE);
}

<INITIAL>"bool"[1-4]	{
    int n = yytext[yyleng -1] - '0';
	TOKEN_VALUE->type = HType(new BuildinType(GenVecType(BT_Boolean, n)));
	return(err_tok = BUILDIN_VEC_TYPE);
}

<INITIAL>"int"[1-4]"x"[1-4]		{
	int n1 = yytext[yyleng - 3] - '0';
	int n2 = yytext[yyleng - 1] - '0';

	TOKEN_VALUE->type = HType(new BuildinType(GenMatType(BT_Int, n1, n2)));
	return(err_tok = BUILDIN_MAT_TYPE);
}

<INITIAL>"uint"[1-4]"x"[1-4]		{
	int n1 = yytext[yyleng - 3] - '0';
	int n2 = yytext[yyleng - 1] - '0';

	TOKEN_VALUE->type = HType(new BuildinType(GenMatType(BT_UInt, n1, n2)));
	return(err_tok = BUILDIN_MAT_TYPE);
}

<INITIAL>"half"[1-4]"x"[1-4]		{
	int n1 = yytext[yyleng - 3] - '0';
	int n2 = yytext[yyleng - 1] - '0';

	TOKEN_VALUE->type = HType(new BuildinType(GenMatType(BT_Half, n1, n2)));
	return(err_tok = BUILDIN_MAT_TYPE);
}

<INITIAL>"float"[1-4]"x"[1-4]		{
	int n1 = yytext[yyleng - 3] - '0';
	int n2 = yytext[yyleng - 1] - '0';

	TOKEN_VALUE->type = HType(new BuildinType(GenMatType(BT_Float, n1, n2)));
	return(err_tok = BUILDIN_MAT_TYPE);
}

<INITIAL>"double"[1-4]"x"[1-4]		{
	int n1 = yytext[yyleng - 3] - '0';
	int n2 = yytext[yyleng - 1] - '0';

	TOKEN_VALUE->type = HType(new BuildinType(GenMatType(BT_Double, n1, n2)));
	return(err_tok = BUILDIN_MAT_TYPE);
}

<INITIAL>"boolean"[1-4]"x"[1-4]		{
	int n1 = yytext[yyleng - 3] - '0';
	int n2 = yytext[yyleng - 1] - '0';

	TOKEN_VALUE->type = HType(new BuildinType(GenMatType(BT_Boolean, n1, n2)));
	return(err_tok = BUILDIN_MAT_TYPE);
}

"matrix"	{return MATRIX;}
"vector"	{return VECTOR;}

<INITIAL>"+"        { return(PLUS); }
<INITIAL>"-"        { return(MINUS); }
<INITIAL>"*"        { return(STAR); }
<INITIAL>"/"        { return(DIV); }
<INITIAL>"%"        { return(MOD); }
<INITIAL>"+="       { return(ASSIGN); }
<INITIAL>"-="       { return(ASSIGN); }
<INITIAL>"*="       { return(ASSIGN); }
<INITIAL>"/="       { return(ASSIGN); }
<INITIAL>"%="       { return(ASSIGN); }

<INITIAL>"!"        { return(NOT); }
<INITIAL>"&&"       { return(AND); }
<INITIAL>"||"       { return(OR); }

<INITIAL>"~"        { return(B_NOT); }
<INITIAL>"&"        { return(B_AND); }
<INITIAL>"|"        { return(B_OR); }
<INITIAL>"^"        { return(B_XOR); }

<INITIAL>"&="       { return(ASSIGN); }
<INITIAL>"|="       { return(ASSIGN); }
<INITIAL>"^="       { return(ASSIGN); }

<INITIAL>"<<"       { return(L_SHIFT); }
<INITIAL>">>"       { return(R_SHIFT); }
<INITIAL>"<<="      { return(ASSIGN); }
<INITIAL>">>="      { return(ASSIGN); }

<INITIAL>"=="       { return(COMP_EQ); }
<INITIAL>"<"        { return(COMP_LESS);
                    }
<INITIAL>"<="       { return(COMP_ARITH);
                    }
<INITIAL>">"        { return(COMP_GRTR);
                    }
<INITIAL>">="       { return(COMP_ARITH);
                    }
<INITIAL>"!="       { return(COMP_EQ);
                    }

<INITIAL>"="        { return(EQ);
                    }
<INITIAL>"++"       { return(INCR);
                    }
<INITIAL>"--"       { return(DECR);
                    }

<INITIAL>"("        { return(LPAREN);
                    }
<INITIAL>")"        { return(RPAREN);
                    }
<INITIAL>"["        { return(LBRCKT);
                    }
<INITIAL>"]"        { return(RBRCKT);
                    }
<INITIAL>"{"        { return(LBRACE);
                    }
<INITIAL>"}"        { return(RBRACE);
                    }

<INITIAL>"."        { return(DOT);
                    }

<INITIAL>"?"        { return(QUESTMARK);
                    }
<INITIAL>":"        { return(COLON);
                    }
<INITIAL>";"        { return(SEMICOLON);
                    }
<INITIAL>","        { return(COMMA);
                    }

<INITIAL>"BINORMAL"{DIGITSEQ}		{
	int semanticUsage = atoi(&(yytext[8]));
	TOKEN_VALUE->semantic = GetSemantic(SMT_Binormal, semanticUsage);
	return(err_tok = SEMANTIC);
}

<INITIAL>"BLENDINDICES"{DIGITSEQ}	{
	int semanticUsage = atoi(&(yytext[12]));
	TOKEN_VALUE->semantic = GetSemantic(SMT_BlendIndices, semanticUsage);
	return(err_tok = SEMANTIC);
}

<INITIAL>"BLENDWEIGHT"{DIGITSEQ}	{
	int semanticUsage = atoi(&(yytext[11]));
	TOKEN_VALUE->semantic = GetSemantic(SMT_BlendWeight, semanticUsage);
	return(err_tok = SEMANTIC);
}

<INITIAL>"COLOR"{DIGITSEQ}			{
	int semanticUsage = atoi(&(yytext[5]));
	TOKEN_VALUE->semantic = GetSemantic(SMT_Color, semanticUsage);
	return(err_tok = SEMANTIC);
}

<INITIAL>"NORMAL"{DIGITSEQ}		{
	int semanticUsage = atoi(&(yytext[6]));
	TOKEN_VALUE->semantic = GetSemantic(SMT_Normal, semanticUsage);
	return(err_tok = SEMANTIC);
}

<INITIAL>"POSITION"{DIGITSEQ}		{
	int semanticUsage = atoi(&(yytext[8]));
	TOKEN_VALUE->semantic = GetSemantic(SMT_Position, semanticUsage);
	return(err_tok = SEMANTIC);
}

<INITIAL>"POSITIONT"				{
	TOKEN_VALUE->semantic = GetSemantic(SMT_PositionT, 0);
	return(err_tok = SEMANTIC);
}

<INITIAL>"PSIZE"					{
	TOKEN_VALUE->semantic = GetSemantic(SMT_PSize, 0);
	return(err_tok = SEMANTIC);
}

<INITIAL>"TANGENT"{DIGITSEQ}		{
	int semanticUsage = atoi(&(yytext[7]));
	TOKEN_VALUE->semantic = GetSemantic(SMT_Tangent, semanticUsage);
	return(err_tok = SEMANTIC);
}

<INITIAL>"TEXCOORD"{DIGITSEQ}		{
	int semanticUsage = atoi(&(yytext[8]));
	TOKEN_VALUE->semantic = GetSemantic(SMT_Texcoord, semanticUsage);
	return(err_tok = SEMANTIC);
}

<INITIAL>"FOG"						{
	TOKEN_VALUE->semantic = GetSemantic(SMT_BlendIndices, 0);
	return(err_tok = SEMANTIC);
}

<INITIAL>"TESSFACTOR"{DIGITSEQ}		{
	int semanticUsage = atoi(&(yytext[10]));
	TOKEN_VALUE->semantic = GetSemantic(SMT_TessFactor, semanticUsage);
	return(err_tok = SEMANTIC);
}

<INITIAL>"VFACE"					{
	TOKEN_VALUE->semantic = GetSemantic(SMT_VFace, 0);
	return(err_tok = SEMANTIC);
}

<INITIAL>"VPOS"						{
	TOKEN_VALUE->semantic = GetSemantic(SMT_BlendIndices, 0);
	return(err_tok = SEMANTIC);
}

<INITIAL>"DEPTH"{DIGITSEQ}			{
	int semanticUsage = atoi(&(yytext[5]));
	TOKEN_VALUE->semantic = GetSemantic(SMT_Depth, semanticUsage);
	return(err_tok = SEMANTIC);
}

<INITIAL>"SV_ClipDistance"{DIGITSEQ}	{
	int semanticUsage = atoi(&(yytext[15]));
	TOKEN_VALUE->semantic = GetSemantic(SMT_SV_ClipDistance, semanticUsage);
	return(err_tok = SEMANTIC);
}

<INITIAL>"SV_CullDistance"{DIGITSEQ}	{
	int semanticUsage = atoi(&(yytext[15]));
	TOKEN_VALUE->semantic = GetSemantic(SMT_SV_CullDistance, semanticUsage);
	return(err_tok = SEMANTIC);
}

<INITIAL>"SV_Coverage"				{
	TOKEN_VALUE->semantic = GetSemantic(SMT_SV_Coverage, 0);
	return(err_tok = SEMANTIC);
}

<INITIAL>"SV_Depth"					{
	TOKEN_VALUE->semantic = GetSemantic(SMT_Depth, 0);
	return(err_tok = SEMANTIC);
}

<INITIAL>"SV_IsFrontFace"			{
	TOKEN_VALUE->semantic = GetSemantic(SMT_SV_IsFrontFace, 0);
	return(err_tok = SEMANTIC);
}

<INITIAL>"SV_Position"				{
	TOKEN_VALUE->semantic = GetSemantic(SMT_SV_Position, 0);
	return(err_tok = SEMANTIC);
}

<INITIAL>"SV_RenderTargetArrayIndex"	{
	TOKEN_VALUE->semantic = GetSemantic(SMT_SV_RenderTargetArrayIndex, 0);
	return(err_tok = SEMANTIC);
}

<INITIAL>"SV_SampleIndex"			{
	TOKEN_VALUE->semantic = GetSemantic(SMT_SV_SampleIndex, 0);
	return(err_tok = SEMANTIC);
}

<INITIAL>"SV_Target"[0-7]			{
	int semanticUsage = yytext[8] - '0';
	TOKEN_VALUE->semantic = GetSemantic(SMT_SV_Target, semanticUsage);
	return(err_tok = SEMANTIC);
}

<INITIAL>"SV_ViewPortArrayIndex"	{
	TOKEN_VALUE->semantic = GetSemantic(SMT_SV_ViewPortArrayIndex, 0);
	return(err_tok = SEMANTIC);
}

<INITIAL>"SV_InstanceID"			{
	TOKEN_VALUE->semantic = GetSemantic(SMT_SV_InstanceID, 0);
	return(err_tok = SEMANTIC);
}

<INITIAL>"SV_PrimitiveID"			{
	TOKEN_VALUE->semantic = GetSemantic(SMT_SV_PrimitiveID, 0);
	return(err_tok = SEMANTIC);
}

<INITIAL>"SV_VertexID"				{
	TOKEN_VALUE->semantic = GetSemantic(SMT_SV_VertexID, 0);
	return(err_tok = SEMANTIC);
}

<INITIAL>{ALPHA}{ALPHANUM}+	{
	//Identifier
	TOKEN_VALUE->idenfitier = yytext;
	return (err_tok = IDENTIFIER);
}
