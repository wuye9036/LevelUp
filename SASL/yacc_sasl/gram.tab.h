/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INUM = 258,
     UINUM = 259,
     DNUM = 260,
     FNUM = 261,
     SEMANTIC = 262,
     PLUS_EQ = 263,
     MINUS_EQ = 264,
     STAR_EQ = 265,
     DIV_EQ = 266,
     MOD_EQ = 267,
     B_AND_EQ = 268,
     B_OR_EQ = 269,
     B_XOR_EQ = 270,
     L_SHIFT_EQ = 271,
     R_SHIFT_EQ = 272,
     EQUAL = 273,
     LESS_EQ = 274,
     GRTR_EQ = 275,
     NOT_EQ = 276,
     RPAREN = 277,
     RBRCKT = 278,
     LBRACE = 279,
     RBRACE = 280,
     SEMICOLON = 281,
     COMMA = 282,
     ELLIPSIS = 283,
     LB_SIGN = 284,
     DOUB_LB_SIGN = 285,
     BACKQUOTE = 286,
     AT = 287,
     COMMA_OP = 288,
     ASSIGN = 289,
     EQ = 290,
     COMMA_SEP = 291,
     COLON = 292,
     QUESTMARK = 293,
     OR = 294,
     AND = 295,
     B_OR = 296,
     B_XOR = 297,
     B_AND = 298,
     COMP_EQ = 299,
     GRTR = 300,
     LESS = 301,
     COMP_GRTR = 302,
     COMP_LESS = 303,
     COMP_ARITH = 304,
     R_SHIFT = 305,
     L_SHIFT = 306,
     MINUS = 307,
     PLUS = 308,
     MOD = 309,
     DIV = 310,
     STAR = 311,
     CAST = 312,
     DECR = 313,
     INCR = 314,
     INDEXOF = 315,
     B_NOT = 316,
     NOT = 317,
     UNARY = 318,
     HYPERUNARY = 319,
     LBRCKT = 320,
     LPAREN = 321,
     DOT = 322,
     ARROW = 323,
     IF = 324,
     ELSE = 325,
     FOR = 326,
     WHILE = 327,
     DO = 328,
     CONTINUE = 329,
     BREAK = 330,
     RETURN = 331,
     IDENTIFIER = 332,
     MATRIX = 333,
     VECTOR = 334,
     STRUCT = 335,
     INT = 336,
     UINT = 337,
     FLOAT = 338,
     DOUBLE = 339,
     BOOL = 340,
     HALF = 341,
     VOID = 342,
     BUILDIN_VEC_TYPE = 343,
     BUILDIN_MAT_TYPE = 344,
     EXTERN = 345,
     STATIC = 346,
     CONST = 347,
     UNIFORM = 348,
     VOLATILE = 349
   };
#endif
/* Tokens.  */
#define INUM 258
#define UINUM 259
#define DNUM 260
#define FNUM 261
#define SEMANTIC 262
#define PLUS_EQ 263
#define MINUS_EQ 264
#define STAR_EQ 265
#define DIV_EQ 266
#define MOD_EQ 267
#define B_AND_EQ 268
#define B_OR_EQ 269
#define B_XOR_EQ 270
#define L_SHIFT_EQ 271
#define R_SHIFT_EQ 272
#define EQUAL 273
#define LESS_EQ 274
#define GRTR_EQ 275
#define NOT_EQ 276
#define RPAREN 277
#define RBRCKT 278
#define LBRACE 279
#define RBRACE 280
#define SEMICOLON 281
#define COMMA 282
#define ELLIPSIS 283
#define LB_SIGN 284
#define DOUB_LB_SIGN 285
#define BACKQUOTE 286
#define AT 287
#define COMMA_OP 288
#define ASSIGN 289
#define EQ 290
#define COMMA_SEP 291
#define COLON 292
#define QUESTMARK 293
#define OR 294
#define AND 295
#define B_OR 296
#define B_XOR 297
#define B_AND 298
#define COMP_EQ 299
#define GRTR 300
#define LESS 301
#define COMP_GRTR 302
#define COMP_LESS 303
#define COMP_ARITH 304
#define R_SHIFT 305
#define L_SHIFT 306
#define MINUS 307
#define PLUS 308
#define MOD 309
#define DIV 310
#define STAR 311
#define CAST 312
#define DECR 313
#define INCR 314
#define INDEXOF 315
#define B_NOT 316
#define NOT 317
#define UNARY 318
#define HYPERUNARY 319
#define LBRCKT 320
#define LPAREN 321
#define DOT 322
#define ARROW 323
#define IF 324
#define ELSE 325
#define FOR 326
#define WHILE 327
#define DO 328
#define CONTINUE 329
#define BREAK 330
#define RETURN 331
#define IDENTIFIER 332
#define MATRIX 333
#define VECTOR 334
#define STRUCT 335
#define INT 336
#define UINT 337
#define FLOAT 338
#define DOUBLE 339
#define BOOL 340
#define HALF 341
#define VOID 342
#define BUILDIN_VEC_TYPE 343
#define BUILDIN_MAT_TYPE 344
#define EXTERN 345
#define STATIC 346
#define CONST 347
#define UNIFORM 348
#define VOLATILE 349




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



