
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
    o+     Programmer:   Stefan Seefeld
    o+     Date:         2003-07-31
    o+
    o+     AST and Type Visitors
    o+
    o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

#ifndef _Traversal_h
#define _Traversal_h

class BaseType;
class PtrType;
class ArrayType;
class BitFieldType;
class FunctionType;

class Symbol;

class IntConstant;
class UIntConstant;
class FloatConstant;
class CharConstant;
class StringConstant;
class ArrayConstant;
class EnumConstant;
class Variable;
class FunctionCall;

class UnaryExpr;
class BinaryExpr;
class TrinaryExpr;
class AssignExpr;
class RelExpr;
class CastExpr;
class SizeofExpr;
class IndexExpr;

class Label;
class Decl;

class Statement;
class FileLineStemnt;
class InclStemnt;
class EndInclStemnt;
class ExpressionStemnt;
class IfStemnt;
class SwitchStemnt;
class ForStemnt;
class WhileStemnt;
class DoWhileStemnt;
class GotoStemnt;
class ReturnStemnt;
class DeclStemnt;
class TypedefStemnt;
class Block;
class FunctionDef;
class TransUnit;

class Traversal
{
public:
  virtual ~Traversal() {}
  virtual void traverse_base(BaseType *) = 0;
  virtual void traverse_ptr(PtrType *) = 0;
  virtual void traverse_array(ArrayType *) = 0;
  virtual void traverse_bit_field(BitFieldType *) = 0;
  virtual void traverse_function(FunctionType *) = 0;

  virtual void traverse_symbol(Symbol *) = 0;

  virtual void traverse_int(IntConstant *) = 0;
  virtual void traverse_uint(UIntConstant *) = 0;
  virtual void traverse_float(FloatConstant *) = 0;
  virtual void traverse_char(CharConstant *) = 0;
  virtual void traverse_string(StringConstant *) = 0;
  virtual void traverse_array(ArrayConstant *) = 0;
  virtual void traverse_enum(EnumConstant *) = 0;
  virtual void traverse_variable(Variable *) = 0;
  virtual void traverse_call(FunctionCall *) = 0;

  virtual void traverse_unary(UnaryExpr *) = 0;
  virtual void traverse_binary(BinaryExpr *) = 0;
  virtual void traverse_trinary(TrinaryExpr *) = 0;
  virtual void traverse_assign(AssignExpr *) = 0;
  virtual void traverse_rel(RelExpr *) = 0;
  virtual void traverse_cast(CastExpr *) = 0;
  virtual void traverse_sizeof(SizeofExpr *) = 0;
  virtual void traverse_index(IndexExpr *) = 0;

  virtual void traverse_label(Label *) = 0;
  virtual void traverse_decl(Decl *) = 0;

  virtual void traverse_statement(Statement *) = 0;
  virtual void traverse_file_line(FileLineStemnt *) = 0;
  virtual void traverse_include(InclStemnt *) = 0;
  virtual void traverse_end_include(EndInclStemnt *) = 0;
  virtual void traverse_expression(ExpressionStemnt *) = 0;
  virtual void traverse_if(IfStemnt *) = 0;
  virtual void traverse_switch(SwitchStemnt *) = 0;
  virtual void traverse_for(ForStemnt *) = 0;
  virtual void traverse_while(WhileStemnt *) = 0;
  virtual void traverse_do_while(DoWhileStemnt *) = 0;
  virtual void traverse_goto(GotoStemnt *) = 0;
  virtual void traverse_return(ReturnStemnt *) = 0;
  virtual void traverse_declaration(DeclStemnt *) = 0;
  virtual void traverse_typedef(TypedefStemnt *) = 0;
  virtual void traverse_block(Block *) = 0;
  virtual void traverse_function_definition(FunctionDef *) = 0;
  virtual void traverse_unit(TransUnit *) = 0;
};

#endif
