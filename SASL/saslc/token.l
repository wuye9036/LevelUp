%{
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

#undef yywrap
extern "C" int yywrap(void);

#define  YY_BUFFER_STATE_DEFD

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cerrno>

#include "config.h"
#include "gram.h"
#include "lexer.h"
#include "token.h"
#include "symbol.h"
#include "express.h"
#include "stemnt.h"
#include "project.h"

#ifdef   WINDOWS
#	ifndef  __STDC__
#	define  __STDC__    1
#endif

int isatty(int) {
    return 1;
}

#endif  /* WINDOWS */

int   err_top_level =0;
int   err_cnt = 0;
int   err_tok = 0;
bool  possibleType = true;
bool  possibleTag = false;

char  tokn_buff[MAX_TOKN_LEN];
char *tokn_end = &tokn_buff[MAX_TOKN_LEN-1];
char *tokn_ptr=tokn_buff;

int cnt_nl(char *txt, int len);

bool  isWide;

#undef YY_INPUT

/* Scan input from a file pointer (default) */

std::string line, last_line;
std::istream *yyinstream;

#define YY_INPUT(buf,result,max_size) \
    do { \
        last_line=line; \
        for(result=0; result<max_size; result++) \
         { \
          char ch; \
          if(!yyinstream->read(&ch, 1)) \
           { \
            if(result==0) result=YY_NULL; \
            break; \
           } \
          if(result==0) line=""; \
          line+=ch; \
          buf[result]=ch; \
          if(ch=='\n') { result++; break; } \
         } \
    } while(0)

#define YY_USER_ACTION \
    { \
        gProject->Parse_TOS->yycolno = gProject->Parse_TOS->yynxtcol; \
        gProject->Parse_TOS->yynxtcol += yyleng; \
    }


#undef HERE
#define HERE Location(gProject->Parse_TOS->yylineno, \
       gProject->Parse_TOS->yycolno, gProject->Parse_TOS->transUnit->filename )

#undef SETPOS_TOKEN
#define SETPOS_TOKEN(TOKEN) \
	do { \
          lvalp->loc = new Location( \
                gProject->Parse_TOS->yylineno, \
                gProject->Parse_TOS->yycolno,  \
                gProject->Parse_TOS->transUnit->filename ); \
	} while(0)

#undef  LAST_STATE
#define LAST_STATE() do { BEGIN(INITIAL); } while (0)

YYSTYPE my_var;

EXTERN int yylex (YYSTYPE *lvalp);

/*  To give some args to yylex */
#undef YY_DECL
#define YY_DECL int yylex (YYSTYPE *lvalp);

%x Start CMMT CC
%a 9000
%o 9000

DOT			"."
DIGIT		[0-9]
DIGITSEQ	{DIGIT}+
ALPHA		[a-zA-Z_]
ALPHANUM	{ALPHA}| {DIGIT}

EXPONENT	[Ee][+-]? {DIGITSEQ}
FRACTION	{DIGIT}* {DOT} {DIGITSEQ} | {DIGITSEQ} {DOT} {DIGITSEQ}?

WHITESPACE	[ \t\f\v]
ALLWHITE	[ \t\f\b\v\r\n]

IDENT		{ALPHA} {ALPHANUM}*

%%

/************/
/* Comments */
/************/
<INITIAL>"/*" { BEGIN(CMMT); }
<INITIAL>"//*"      { // Ambiguous C++ style comment, must parse as
    //    '/' '/*' to be Ansi compliant
    yywarn(
        "Ambiguous C++ comment, use '/ /*' -or- '// *'");
    yyless(2);
    SETPOS_TOKEN(DIV);
    return(DIV);
}
<INITIAL>"//"[^*].*$ { /* C++ style comment */ }

/*******************/
/*  Storage Types  */
/*******************/
<INITIAL>"extern"	{
	lvalp->typeQual = TQ_Extern;
	return (err_tok = TQ_Extern);
}

/**************
 * Base Types *
 **************/
<INITIAL>"const"    {
    lvalp->typeQual = TQ_Const;
    return(err_tok = CONST);
}
<INITIAL>"uniform"	{
	lvalp->typeQual = TQ_Uniform;
	return(err_tok = UNIFORM);
}

<INITIAL>"void"		{
	lvalp->base = new BaseType(BT_Void);
	return (err_tok = BASETYPE);
}
<INITIAL>"int"      {
    lvalp->base = new BaseType(BT_Int);
    return(err_tok = BASETYPE);
}
<INITIAL>"uint"		{
	lvalp->base = new BaseType(BT_UInt);
	return (err_tok = BASETYPE)
}
<INITIAL>"float"    {
    lvalp->base = new BaseType(BT_Float);
    return(err_tok = BASETYPE);
}
<INITIAL>"half"		{
    lvalp->base = new BaseType(BT_Half);
    return(err_tok = BASETYPE);
}
<INITIAL>"double"		{
    lvalp->base = new BaseType(BT_Double);
    return(err_tok = BASETYPE);
}
<INITIAL>"bool"		{
	lval->base = new BaseType(BT_Boolean);
	return(err_tok = BASETYPE);
}

/*************/
/*  Vectors  */
/*************/
<INITIAL>"int"[2-4]		{
	int n = yytext[yyleng - 1] - '1';
	lvalp->base = new BaseType(VectorType(BT_Int, n));
	return(err_tok = BASETYPE);
}

<INITIAL>"uint"[2-4]	{
	int n = yytext[yyleng - 1] - '1';
	lvalp->base = new BaseType(VectorType(BT_UInt, n));
	return(err_tok = BASETYPE);
}

<INITIAL>"half"[2-4]	{
    int n = yytext[yyleng - 1] - '1';
	lvalp->base = new BaseType(VectorType(BT_Half, n));
	return(err_tok = BASETYPE);
}

<INITIAL>"float"[2-4]	{
    int n = yytext[yyleng -1] - '1';
	lvalp->base = new BaseType(VectorType(BT_Float, n));
	return(err_tok = BASETYPE);
}

<INITIAL>"double"[2-4]	{
    int n = yytext[yyleng -1] - '1';
	lvalp->base = new BaseType(VectorType(BT_Double, n));
	return(err_tok = BASETYPE);
}

<INITIAL>"bool"[2-4]	{
    int n = yytext[yyleng -1] - '1';
	lvalp->base = new BaseType(VectorType(BT_Boolean, n));
	return(err_tok = BASETYPE);
}

/************/
/*  Matrix  */
/************/
<INITIAL>"int"[1-4]"x"[1-4]		{
	int n1 = yytext[yyleng - 3] - '1';
	int n2 = yytext[yyleng - 1] - '1';

	lvalp->base = new BaseType(MatrixType(BT_Int, n1, n2));
	return(err_tok = BASETYPE);
}

<INITIAL>"uint"[1-4]"x"[1-4]		{
	int n1 = yytext[yyleng - 3] - '1';
	int n2 = yytext[yyleng - 1] - '1';

	lvalp->base = new BaseType(MatrixType(BT_UInt, n1, n2));
	return(err_tok = BASETYPE);
}

<INITIAL>"half"[1-4]"x"[1-4]		{
	int n1 = yytext[yyleng - 3] - '1';
	int n2 = yytext[yyleng - 1] - '1';

	lvalp->base = new BaseType(MatrixType(BT_Half, n1, n2));
	return(err_tok = BASETYPE);
}

<INITIAL>"float"[1-4]"x"[1-4]		{
	int n1 = yytext[yyleng - 3] - '1';
	int n2 = yytext[yyleng - 1] - '1';

	lvalp->base = new BaseType(MatrixType(BT_Float, n1, n2));
	return(err_tok = BASETYPE);
}

<INITIAL>"double"[1-4]"x"[1-4]		{
	int n1 = yytext[yyleng - 3] - '1';
	int n2 = yytext[yyleng - 1] - '1';

	lvalp->base = new BaseType(MatrixType(BT_Double, n1, n2));
	return(err_tok = BASETYPE);
}

<INITIAL>"boolean"[1-4]"x"[1-4]		{
	int n1 = yytext[yyleng - 3] - '1';
	int n2 = yytext[yyleng - 1] - '1';

	lvalp->base = new BaseType(MatrixType(BT_Boolean, n1, n2));
	return(err_tok = BASETYPE);
}

/***************/
/*  Type Defs  */
/***************/
<INITIAL>"struct"   {
    lvalp->typeSpec = BT_Struct;
    possibleTag = true;
    return(err_tok = STRUCT);
}

/****************************/
/*  Flow Control Attibutes  */
/****************************/
<INITIAL>"flatten"	{
	lvalp->fca = FCA_Flatten;
	return (err_rok = FLATTEN);
}

<INITIAL>"branch"	{
	lvalp->fca = FCA_Branch;
	return (err_tok = BRANCH);
}

<INITIAL>"unroll"	{
	lvalp->fca = FCA_Unroll;
	return (err_tok = UNROLL);
}

<INITIAL>"loop"		{
	lvalp->fca = FCA_Loop;
	return (err_tok = LOOP);
}

<INITIAL>"call"		{
	lvalp->fca = FCA_Call;
	return (err_tok = CALL);
}

<INITIAL>"forcase"	{
	lvalp->fca = FCA_Forcase;
	return (err_tok = FORCASE);
}

/****************/
/*  Statements  */
/****************/
<INITIAL>"break"    { SETPOS_TOKEN(BREAK);
                      return(BREAK);
                    }
<INITIAL>"case"     { SETPOS_TOKEN(CASE);
                      return(CASE);
                    }
<INITIAL>"continue" { SETPOS_TOKEN(CONT);
                      return(CONT);
                    }
<INITIAL>"default"  { SETPOS_TOKEN(DEFLT);
                      return(DEFLT);
                    }
<INITIAL>"do"       { SETPOS_TOKEN(DO);
                      return(DO);
                    }
<INITIAL>"else"     { SETPOS_TOKEN(ELSE);
                      return(ELSE);
                    }
<INITIAL>"for"      { SETPOS_TOKEN(FOR);
                      return(FOR);
                    }

<INITIAL>"if"       { SETPOS_TOKEN(IF);
                      return(IF);
                    }
<INITIAL>"return"   { SETPOS_TOKEN(RETURN);
                      return(RETURN);
                    }
<INITIAL>"switch"   { SETPOS_TOKEN(SWITCH);
                      return(SWITCH);
                    }
<INITIAL>"while"    { SETPOS_TOKEN(WHILE);
                      return(WHILE);
                    }
<INITIAL>"discard"	{ SETPOS_TOKEN(DISCARD);
					  return(DISCARD);
					}
<INITIAL>"stop"		{ SETPOS_TOKEN(STOP);
					  return(STOP);
					}

/****************/
/*  Operations  */
/****************/
<INITIAL>"+"        { lvalp->binOp = BO_Plus;
                      return(PLUS);
                    }
<INITIAL>"-"        { lvalp->binOp = BO_Minus;
                      return(MINUS);
                    }
<INITIAL>"*"        { lvalp->binOp = BO_Mult;
                      return(STAR);
                    }
<INITIAL>"/"        { lvalp->binOp = BO_Div;
                      return(DIV);
                    }
<INITIAL>"%"        { lvalp->binOp = BO_Mod;
                      return(MOD);
                    }

<INITIAL>"+="       { lvalp->assignOp = AO_PlusEql;
                      return(ASSIGN);
                    }
<INITIAL>"-="       { lvalp->assignOp = AO_MinusEql;
                      return(ASSIGN);
                    }
<INITIAL>"*="       { lvalp->assignOp = AO_MultEql;
                      return(ASSIGN);
                    }
<INITIAL>"/="       { lvalp->assignOp = AO_DivEql;
                      return(ASSIGN);
                    }
<INITIAL>"%="       { lvalp->assignOp = AO_ModEql;
                      return(ASSIGN);
                    }

<INITIAL>"!"        { SETPOS_TOKEN(NOT);
                      return(NOT);
                    }
<INITIAL>"&&"       { SETPOS_TOKEN(AND);
                      return(AND);
                    }
<INITIAL>"||"       { SETPOS_TOKEN(OR);
                      return(OR);
                    }

<INITIAL>"~"        { SETPOS_TOKEN(B_NOT);
                      return(B_NOT);
                    }
<INITIAL>"&"        { SETPOS_TOKEN(B_AND);
                      return(B_AND);
                    }
<INITIAL>"|"        { SETPOS_TOKEN(B_OR);
                      return(B_OR);
                    }
<INITIAL>"^"        { SETPOS_TOKEN(B_XOR);
                      return(B_XOR);
                    }

<INITIAL>"&="       { lvalp->assignOp = AO_BitAndEql;
                      return(ASSIGN);
                    }
<INITIAL>"|="       { lvalp->assignOp = AO_BitOrEql;
                      return(ASSIGN);
                    }
<INITIAL>"^="       { lvalp->assignOp = AO_BitXorEql;
                      return(ASSIGN);
                    }

<INITIAL>"<<"       { lvalp->binOp = BO_Shl;
                      return(L_SHIFT);
                    }
<INITIAL>">>"       { lvalp->binOp = BO_Shr;
                      return(R_SHIFT);
                    }
<INITIAL>"<<="      { lvalp->assignOp = AO_ShlEql;
                      return(ASSIGN);
                    }
<INITIAL>">>="      { lvalp->assignOp = AO_ShrEql;
                      return(ASSIGN);
                    }

<INITIAL>"=="       { lvalp->relOp = RO_Equal;
                      return(COMP_EQ);
                    }
<INITIAL>"<"        { lvalp->relOp = RO_Less;
                      return(COMP_LESS);
                    }
<INITIAL>"<="       { lvalp->relOp = RO_LessEql;
                      return(COMP_ARITH);
                    }
<INITIAL>">"        { lvalp->relOp = RO_Grtr;
                      return(COMP_GRTR);
                    }
<INITIAL>">="       { lvalp->relOp = RO_GrtrEql;
                      return(COMP_ARITH);
                    }
<INITIAL>"!="       { lvalp->relOp = RO_NotEqual;
                      return(COMP_EQ);
                    }

<INITIAL>"="        { lvalp->assignOp = AO_Equal;
                      return(EQ);
                    }
<INITIAL>"++"       { SETPOS_TOKEN(INCR);
                      return(INCR);
                    }
<INITIAL>"--"       { SETPOS_TOKEN(DECR);
                      return(DECR);
                    }

<INITIAL>"("        { SETPOS_TOKEN(LPAREN);
                      possibleType = true;
                      return(LPAREN);
                    }
<INITIAL>")"        { SETPOS_TOKEN(RPAREN);
                      return(RPAREN);
                    }
<INITIAL>"["        { SETPOS_TOKEN(LBRCKT);
                      return(LBRCKT);
                    }
<INITIAL>"]"        { SETPOS_TOKEN(RBRCKT);
                      return(RBRCKT);
                    }
<INITIAL>"{"        { SETPOS_TOKEN(LBRACE);
                      possibleTag = false;
                      return(LBRACE);
                    }
<INITIAL>"}"        { SETPOS_TOKEN(RBRACE);
                      return(RBRACE);
                    }

<INITIAL>"."        { SETPOS_TOKEN(DOT);
                      return(DOT);
                    }

<INITIAL>"?"        { SETPOS_TOKEN(QUESTMARK);
                      return(QUESTMARK);
                    }
<INITIAL>":"        { SETPOS_TOKEN(COLON);
                      return(COLON);
                    }
<INITIAL>";"        { SETPOS_TOKEN(SEMICOLON);
                      return(SEMICOLON);
                    }
<INITIAL>","        { SETPOS_TOKEN(COMMA);
                      return(COMMA);
                    }

<INITIAL> {INDENT}  {
    /* Identifier */
    lvalp->symbol = new Symbol();
    lvalp->symbol->name = yytext;

    if (possibleTag) {
        /* Check the tag table and insert a  */
        /* ptr back to the definition.  */
        SymEntry *se
        = gProject->Parse_TOS->transUnit->contxt.tags->Lookup(
              lvalp->symbol->name);
        lvalp->symbol->entry = se;
        possibleTag = false;
        return(err_tok = TAG_NAME);
    } else {
        /* Check the symbol table and insert a  */
        /* ptr back to the definition.  */
        SymEntry *se = gProject->Parse_TOS->transUnit->contxt.syms->Lookup(
                           lvalp->symbol->name);
        lvalp->symbol->entry = se;

        if (possibleType) {
            if (se && se->IsTypeDef()) {
                return(err_tok = TYPEDEF_NAME);
            }
        }
    }

    return(err_tok = IDENT);
}

/***************/
/*  Semantics  */
/***************/

//VS Inout
<INITIAL>"BINORMAL"{DIGITSEQ}		{
	int semanticUsage = atoi(yytext[8]);
	lvalp->semanticType = GetSemanticType(SBT_Binormal, semanticUsage);
	return(err_tok = SEMANTIC)
}

<INITIAL>"BLENDINDICES"{DIGITSEQ}	{
	int semanticUsage = atoi(yytext[12]);
	lvalp->semanticType = GetSemanticType(SBT_BlendIndices, semanticUsage);
	return(err_tok = SEMANTIC)
}

<INITIAL>"BLENDWEIGHT"{DIGITSEQ}	{
	int semanticUsage = atoi(yytext[11]);
	lvalp->semanticType = GetSemanticType(SBT_BlendWeight, semanticUsage);
	return(err_tok = SEMANTIC)
}

<INITIAL>"COLOR"{DIGITSEQ}			{
	int semanticUsage = atoi(yytext[5]);
	lvalp->semanticType = GetSemanticType(SBT_Color, semanticUsage);
	return(err_tok = SEMANTIC)
}

<INITIAL>"NORMAL" {DIGITSEQ}		{
	int semanticUsage = atoi(yytext[6]);
	lvalp->semanticType = GetSemanticType(SBT_Normal, semanticUsage);
	return(err_tok = SEMANTIC)
}

<INITIAL>"POSITION"{DIGITSEQ}		{
	int semanticUsage = atoi(yytext[8]);
	lvalp->semanticType = GetSemanticType(SBT_Position, semanticUsage);
	return(err_tok = SEMANTIC)
}

<INITIAL>"POSITIONT"				{
	lvalp->semanticType = GetSemanticType(SBT_PositionT, 0);
	return(err_tok = SEMANTIC)
}

<INITIAL>"PSIZE"					{
	lvalp->semanticType = GetSemanticType(SBT_PSize, 0);
	return(err_tok = SEMANTIC)
}

<INITIAL>"TANGENT"{DIGITSEQ}		{
	int semanticUsage = atoi(yytext[7]);
	lvalp->semanticType = GetSemanticType(SBT_Tangent, semanticUsage);
	return(err_tok = SEMANTIC)
}

<INITIAL>"TEXCOORD"{DIGITSEQ}		{
	int semanticUsage = atoi(yytext[8]);
	lvalp->semanticType = GetSemanticType(SBT_Texcoord, semanticUsage);
	return(err_tok = SEMANTIC)
}

//VS Output
<INITIAL>"FOG"						{
	lvalp->semanticType = GetSemanticType(SBT_BlendIndices, 0);
	return(err_tok = SEMANTIC)
}

<INITIAL>"TESSFACTOR"{DIGITSEQ}		{
	int semanticUsage = atoi(yytext[10]);
	lvalp->semanticType = GetSemanticType(SBT_TessFactor, semanticUsage);
	return(err_tok = SEMANTIC)
}

//PS Input
<INITIAL>"VFACE"					{
	lvalp->semanticType = GetSemanticType(SBT_VFace, 0);
	return(err_tok = SEMANTIC)
}

<INITIAL>"VPOS"						{
	lvalp->semanticType = GetSemanticType(SBT_BlendIndices, 0);
	return(err_tok = SEMANTIC)
}

//PS Output
<INITIAL>"DEPTH"{DIGITSEQ}			{
	int semanticUsage = atoi(yytext[5]);
	lvalp->semanticType = GetSemanticType(SBT_Depth, semanticUsage);
	return(err_tok = SEMANTIC)
}

//DX10
<INITIAL>"SV_ClipDistance"{DIGITSEQ}{
	int semanticUsage = atoi(yytext[15]);
	lvalp->semanticType = GetSemanticType(SBT_SV_ClipDistance, semanticUsage);
	return(err_tok = SEMANTIC)
}

<INITIAL>"SV_CullDistance"{DIGITSEQ}{
	int semanticUsage = atoi(yytext[15]);
	lvalp->semanticType = GetSemanticType(SBT_SV_CullDistance, semanticUsage);
	return(err_tok = SEMANTIC)
}

<INITIAL>"SV_Coverage"				{
	lvalp->semanticType = GetSemanticType(0);
	return(err_tok = SEMANTIC)
}

<INITIAL>"SV_Depth"					{
	lvalp->semanticType = GetSemanticType(SBT_SV_Depth, 0);
	return(err_tok = SEMANTIC)
}

<INITIAL>"SV_IsFrontFace"			{
	lvalp->semanticType = GetSemanticType(SBT_SV_IsFrontFace, 0);
	return(err_tok = SEMANTIC)
}

<INITIAL>"SV_Position"				{
	lvalp->semanticType = GetSemanticType(SBT_SV_Position, 0);
	return(err_tok = SEMANTIC)
}

<INITIAL>"SV_RenderTargetArrayIndex"{
	lvalp->semanticType = GetSemanticType(SBT_SV_RenderTargetArrayIndex, 0);
	return(err_tok = SEMANTIC)
}

<INITIAL>"SV_SampleIndex"			{
	lvalp->semanticType = GetSemanticType(SBT_SV_SampleIndex, 0);
	return(err_tok = SEMANTIC)
}

<INITIAL>"SV_Target"[0-7]			{
	int semanticUsage = atoi(yytext[8]);
	lvalp->semanticType = GetSemanticType(SBT_SV_Target, semanticUsage);
	return(err_tok = SEMANTIC)
}

<INITIAL>"SV_ViewPortArrayIndex"	{
	lvalp->semanticType = GetSemanticType(SBT_SV_ViewPortArrayIndex, 0);
	return(err_tok = SEMANTIC)
}

<INITIAL>"SV_InstanceID"			{
	lvalp->semanticType = GetSemanticType(SBT_SV_InstanceID, 0);
	return(err_tok = SEMANTIC)
}

<INITIAL>"SV_PrimitiveID"			{
	lvalp->semanticType = GetSemanticType(SBT_SV_PrimitiveID, 0);
	return(err_tok = SEMANTIC)
}

<INITIAL>"SV_VertexID"				{
	lvalp->semanticType = GetSemanticType(SV_VertexID, 0);
	return(err_tok = SEMANTIC)
}

/*************/
/*  Literal  */
/*************/

<INITIAL> {DIGITSEQ}	{ /* An integer */
    long i = strtol(yytext, (char**) NULL, 0);

    if (errno == ERANGE) {
        unsigned long ui;
        ui = strtoul(yytext, (char**) NULL, 0);
        lvalp->consValue = new UIntConstant(ui,HERE);
    } else {
        lvalp->consValue = new IntConstant(i,HERE);
    }

    return(err_tok = INUM);
}

<INITIAL> {DIGITSEQ} {DOT} {DIGITSEQ} {EXPONENT}?	|
<INITIAL> {DIGITSEQ} {DOT} {EXPONENT}?				|
<INITIAL> {DOT} {DIGITSEQ} {EXPONENT}?				|
<INITIAL> {DIGITSEQ} {EXPONENT} {
    /*
    ** Note: The floatsuffix, if any, will be
    ** ignored by atof().
    */
    lvalp->consValue = new FloatConstant(atof(yytext),HERE);
    return(err_tok = RNUM);
}

/******************/
/*  Comment Ends  */
/******************/
<CMMT>[^*\n/\\]*       {   /* Inside C-style comment */ }

<CMMT>[^*\n/\\]*\n     {
    gProject->Parse_TOS->yylineno++;
    gProject->Parse_TOS->yynxtcol = 0;
}
<CMMT>"/"[^*\n]        { }
<CMMT>\\\n             {
    gProject->Parse_TOS->yylineno++;
    gProject->Parse_TOS->yynxtcol = 0;
}
<CMMT>\\[^\n]          {
}
<CMMT>"/"\n            {
    gProject->Parse_TOS->yylineno++;
    gProject->Parse_TOS->yynxtcol = 0;
}
<CMMT>"/*"             { yywarn("/* inside comment"); }
<CMMT>"*"+[^*/\n\\]*   {   /* Stars */ }
<CMMT>"*"+[^*/\n\\]*\n {
    gProject->Parse_TOS->yylineno++;
    gProject->Parse_TOS->yynxtcol = 0;
}
<CMMT>"*"+"/"          {
    LAST_STATE();
}

/***********/
/*  Miscs  */
/***********/
<INITIAL> {whitespace}+ {  /* space/tab/formfeed/vertical tab (ignore) */ }
<INITIAL,CMMT>\n|\r    {
    gProject->Parse_TOS->yylineno++;
    gProject->Parse_TOS->yynxtcol = 0;
    in_preprocess = 0;
}

/************/
/*  Errors  */
/************/
<CMMT><<EOF>>          {
    yyerr("EOF reached inside comment");
    in_preprocess = 0;
    return(0);
}

.                      { /* Any unknown char is an error */
							*gProject->Parse_TOS->yyerrstream << "Error: Line " << gProject->Parse_TOS->yylineno << ": Illegal Character";
							if ((yytext[0] >= ' ') && (yytext[0] <= '~')) {
								*gProject->Parse_TOS->yyerrstream << ": '" << yytext[0] << "'\n";
							} else {
								*gProject->Parse_TOS->yyerrstream << ", ASCII: " << std::hex << (int)(yytext[0]) << " (hex)\n" << std::dec;
							}
						}
%%

/***********************************************************************/

void print_caret(const std::string &s, int pos) {
    const char *str;
    int i = 0;

    for (str=s.c_str(); *str && (i<pos); i++, str++) {
        if (*str=='\t') {
            *gProject->Parse_TOS->yyerrstream << "\t";
        }       else {
            *gProject->Parse_TOS->yyerrstream << " ";
        }
    }
    *gProject->Parse_TOS->yyerrstream << "^\n";
}

/***********************************************************************/

void yywarn(char *s) {
    std::ostream& errstream = *gProject->Parse_TOS->yyerrstream;
    errstream << gProject->Parse_TOS->transUnit->filename << ":" << gProject->Parse_TOS->yylineno << ": Warning - " << s << ":\n" << line;
    print_caret(line, gProject->Parse_TOS->yycolno);
}

/***********************************************************************/

int yyerr(char *s, std::string & str) {
    std::ostream& errstream = *gProject->Parse_TOS->yyerrstream;
    errstream << gProject->Parse_TOS->filename << ":" << gProject->Parse_TOS->yylineno << ": " << s << str << ":\n" << line;
    print_caret(line, gProject->Parse_TOS->yycolno);

    ++err_top_level;
    if (++err_cnt >= 10) {
        *gProject->Parse_TOS->yyerrstream
        << "Too many errors (" << err_cnt << " detected) - quitting.\n";
        return(1);
    }
    return(0);
}

/***********************************************************************/

int yyerr(char *s) {
    *gProject->Parse_TOS->yyerrstream
    << gProject->Parse_TOS->filename << ":" << gProject->Parse_TOS->yylineno
    << ": " << s << ":\n" << line;
    print_caret(line, gProject->Parse_TOS->yycolno);

    ++err_top_level;
    if (++err_cnt >= 10) {
        *gProject->Parse_TOS->yyerrstream
        << "Too many errors (" << err_cnt << " detected) - quitting.\n";
        return(1);
    }
    return(0);
}

/***********************************************************************/

int yyerror(char *s) {
    *gProject->Parse_TOS->yyerrstream
    << gProject->Parse_TOS->transUnit->filename << ":" << gProject->Parse_TOS->yylineno
    << ": Error (" << s << ") before '"
    << toksym(err_tok,0) << "'\n" << line;
    print_caret(line, gProject->Parse_TOS->yycolno);

    /*
     * This does _NOTHING_.  Bison, at least, ignores the return value of
     * yyerror().  I don't know why cTool does this.  --Jeremy.
     */
    if (++err_cnt >= 10) {
        *gProject->Parse_TOS->yyerrstream << "Too many errors (" << err_cnt << " detected) - quitting.\n";
        return(1);
    }
    return(0);
}
