
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
    o+     Print an AST
    o+
    o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

#include <ctool/decl.h>
#include <ctool/stemnt.h>
#include <ctool/project.h>
#include <ctool/express.h>
#include <ctool/symbol.h>

#include <ctool/PrintTraversal.h>

PrintTraversal::PrintTraversal(std::ostream &os, bool d)
   : out(os), debug(d), level(0), show_base(true)
{
}

void PrintTraversal::traverse_base(BaseType *type)
{
}

void PrintTraversal::traverse_ptr(PtrType *ptr)
{
}

void PrintTraversal::traverse_array(ArrayType *)
{
}

void PrintTraversal::traverse_bit_field(BitFieldType *)
{
}

void PrintTraversal::traverse_function(FunctionType *)
{
}

void PrintTraversal::traverse_symbol(Symbol *node)
{
  out << *node;
}

void PrintTraversal::traverse_int(IntConstant *node)
{
  out << node->lng;
  if (node->L) out << "L";

#ifdef    SHOW_TYPES
  if (node->type)
  {
    out << "/* ";
    node->type->printType(out, NULL, true, 0);
    out << " */";
  }
#endif
}

void PrintTraversal::traverse_uint(UIntConstant *node)
{
  out << node->ulng;
  if (node->L) out << "L";

#ifdef    SHOW_TYPES
  if (node->type != NULL)
  {
    out << "/* ";
    node->type->printType(out, NULL, true, 0);
    out << " */";
  }
#endif
}

void PrintTraversal::traverse_float(FloatConstant *node)
{
  out << node->value;

#ifdef    SHOW_TYPES
  if (node->type)
  {
    out << "/* ";
    node->type->printType(out, NULL, true, 0);
    out << " */";
  }
#endif
}

void PrintTraversal::traverse_char(CharConstant *node)
{
  if (node->wide) out << 'L';

  out << "'";
  meta_char(node->ch, false);
  out << "'";

#ifdef    SHOW_TYPES
  if (node->type)
  {
    out << "/* ";
    node->type->printType(out, NULL, true, 0);
    out << " */";
  }
#endif
}

void PrintTraversal::traverse_string(StringConstant *node)
{
  if (node->wide) out << 'L';

  out << '"';
  meta_string(node->buff);
  out << '"';

#ifdef    SHOW_TYPES
  if (node->type)
  {
    out << "/* ";
    node->type->printType(out, NULL, true, 0);
    out << " */";
  }
#endif
}

void PrintTraversal::traverse_array(ArrayConstant *node)
{
  out <<  "{ ";

  if (!node->items.empty())
  {
    ExprVector::const_iterator i = node->items.begin();
    (*i)->accept(this);
    for (++i; i != node->items.end(); ++i)
    {
      out << ", ";
      (*i)->accept(this);
    }
  }

  out <<  " }";

#ifdef    SHOW_TYPES
  if (node->type)
  {
    out << "/* ";
    node->type->printType(out, NULL, true, 0);
    out << " */";
  }
#endif
}

void PrintTraversal::traverse_enum(EnumConstant *node)
{
  traverse_symbol(node->name);
  if (node->value)
  {
    out << " = ";
    node->value->accept(this);
  }

#ifdef    SHOW_TYPES
  if (node->type)
  {
    out << "/* ";
    node->type->printType(out, NULL, true, 0);
    out << " */";
  }
#endif
}

void PrintTraversal::traverse_variable(Variable *node)
{
  traverse_symbol(node->name);

#ifdef    SHOW_TYPES
  if (node->type)
  {
    out << "/* ";
    node->type->printType(out, NULL, true, 0);
    out << " */";
  }
#endif
}

void PrintTraversal::traverse_call(FunctionCall *node)
{
  if (node->function->precedence() < node->precedence())
  {
    out << "(";
    node->function->accept(this);
    out << ")";
  }
  else node->function->accept(this);

  out << "(";

  if (!node->args.empty())
  {
    ExprVector::const_iterator i = node->args.begin();
    if (((*i)->etype == ET_BinaryExpr)
	&& ((static_cast<BinaryExpr*>(*i))->op() == BO_Comma))
        {
	  out << "(";
	  (*i)->accept(this);
	  out << ")";
        }
    else
      (*i)->accept(this);

    for (++i; i != node->args.end(); ++i)
    {
      out << ",";

      if (((*i)->etype == ET_BinaryExpr)
	  && ((static_cast<BinaryExpr*>(*i))->op() == BO_Comma))
      {
	out << "(";
	(*i)->accept(this);
	out << ")";
      }
      else (*i)->accept(this);
    }
  }

  out << ")";

#ifdef    SHOW_TYPES
  if (node->type)
  {
    out << "/* ";
    node->type->printType(out, NULL, true, 0);
    out << " */";
  }
#endif
}

void PrintTraversal::traverse_unary(UnaryExpr *node)
{
  node->print(out);
}

void PrintTraversal::traverse_binary(BinaryExpr *node)
{
  node->print(out);
}

void PrintTraversal::traverse_trinary(TrinaryExpr *node)
{
  node->print(out);
}

void PrintTraversal::traverse_assign(AssignExpr *node)
{
  if (node->lValue()->precedence() < node->precedence())
  {
    out << "(";
    node->lValue()->accept(this);
    out << ")";
  }
  else node->lValue()->accept(this);

  out << " ";
  assign_op(node->aOp);
  out << " ";

  if (node->rValue()->precedence() < node->precedence())
  {
    out << "(";
    node->rValue()->accept(this);
    out << ")";
  }
  else node->rValue()->accept(this);

#ifdef    SHOW_TYPES
  if (node->type)
  {
    out << "/* ";
    node->type->printType(out, NULL, true, 0);
    out << " */";
  }
#endif
}

void PrintTraversal::traverse_rel(RelExpr *node)
{
  if (node->leftExpr()->precedence() <= node->precedence())
  {
    out << "(";
    node->leftExpr()->accept(this);
    out << ")";
  }
  else node->leftExpr()->accept(this);

  out << " ";
  rel_op(node->rOp);
  out << " ";

  if (node->rightExpr()->precedence() <= node->precedence())
  {
    out << "(";
    node->rightExpr()->accept(this);
    out << ")";
  }
  else node->rightExpr()->accept(this);

#ifdef    SHOW_TYPES
  if (node->type)
  {
    out << "/* ";
    node->type->printType(out, NULL, true, 0);
    out << " */";
  }
#endif
}

void PrintTraversal::traverse_cast(CastExpr *node)
{
  out << "(";
  node->castTo->printType(out, NULL, true, 0); 
  out << ") ";

  out << "(";
  node->expr->accept(this);
  out << ")";

#ifdef    SHOW_TYPES
  if (node->type)
  {
    out << "/* ";
    node->type->printType(out, NULL, true, 0);
    out << " */";
  }
#endif
}

void PrintTraversal::traverse_sizeof(SizeofExpr *node)
{
  out << "sizeof(";
  if (node->sizeofType)
    node->sizeofType->printType(out, NULL, true, 0); 
  else node->expr->accept(this);
  out << ") ";

#ifdef    SHOW_TYPES
  if (node->type)
  {
    out << "/* ";
    node->type->printType(out, NULL, true, 0);
    out << " */";
  }
#endif
}

void PrintTraversal::traverse_index(IndexExpr *node)
{
  if (node->array->precedence() < node->precedence())
  {
    out << "(";
    node->array->accept(this);
    out << ")";
  }
  else node->array->accept(this);

  out << "[";
  node->_subscript->accept(this);
  out << "]";

#ifdef    SHOW_TYPES
  if (node->type)
  {
    out << "/* ";
    node->type->printType(out, NULL, true, 0);
    out << " */";
  }
#endif
}

void PrintTraversal::traverse_label(Label *node)
{
  decr_indent();
  indent();
  incr_indent();

  switch (node->type)
  {
    case LT_None:
      assert(0);
      break;

    case LT_Default:
      out << "default";
      break;

    case LT_Case:
      assert(node->begin);
      out << "case ";
      node->begin->accept(this);
      break;

    case LT_CaseRange:
      assert(node->begin);
      assert(node->end);
      out << "case ";
      node->begin->accept(this);
      out << " ... ";
      node->end->accept(this);
      break;

    case LT_Goto:
      assert(node->name);
      traverse_symbol(node->name);
      break;
  }
  out << ":\n";
}

void PrintTraversal::traverse_decl(Decl *node)
{
  node->print(out, show_base, level);
}

void PrintTraversal::traverse_statement(Statement *node)
{
  node->print(out, level);
}

void PrintTraversal::traverse_file_line(FileLineStemnt *node)
{
#ifdef PRINT_LOCATION
  out << "$<FileLineStemnt:" ;
  node->location.printLocation(out);
  out << ">$";
#endif
  if (node->linenumber > 0) out << "#line " << node->linenumber;
  else out << "#file";  
  out << " \"" << node->filename << "\"" << std::endl;
}

void PrintTraversal::traverse_include(InclStemnt *node)
{
#ifdef PRINT_LOCATION
  out << "$<InclStemnt:" ;
  node->location.printLocation(out) ;
  out << ">$";
#endif
  out << "#include " << (node->isStandard ? '<' : '"');
  out << node->filename << (node->isStandard ? '>' : '"') << std::endl;
}

void PrintTraversal::traverse_end_include(EndInclStemnt *node)
{
#ifdef PRINT_LOCATION
  out << "$<EndInclStemnt:" ;
  node->location.printLocation(out);
  out << ">$";
#endif
}

void PrintTraversal::traverse_expression(ExpressionStemnt *node)
{
  if (debug)
  {
    out << "/* ExpressionStemnt:";
    node->location.printLocation(out);
    out << " */" << std::endl;
  }

  for (LabelVector::const_iterator i = node->labels.begin();
       i != node->labels.end();
       ++i)
    traverse_label(*i);

  indent();
  assert(node->expression);
  node->expression->accept(this);
}

void PrintTraversal::traverse_if(IfStemnt *node)
{
  if (debug)
  {
    out << "/* IfStemnt:";
    node->location.printLocation(out);
    out << " */" << std::endl;
  }

  for (LabelVector::const_iterator i = node->labels.begin();
       i != node->labels.end();
       ++i)
    traverse_label(*i);

  indent();

  out << "if (";
  node->cond->accept(this);
  out << ")\n";
  block(node->thenBlk);
  
  if (node->elseBlk)
  {
    out << std::endl;
    indent();
    out << "else\n";
    block(node->elseBlk);
  }
}

void PrintTraversal::traverse_switch(SwitchStemnt *node)
{
  if (debug)
  {
    out << "/* SwitchStemnt:";
    node->location.printLocation(out);
    out << " */" << std::endl;
  }
  
  for (LabelVector::const_iterator i = node->labels.begin();
       i != node->labels.end();
       ++i)
    traverse_label(*i);
  
  indent();
  out << "switch (";
  node->cond->accept(this);
  out << ")\n";
  
  block(node->block);
}

void PrintTraversal::traverse_for(ForStemnt *node)
{
  if (debug)
  {
    out << "/* ForStemnt:";
    node->location.printLocation(out);
    out << " */" << std::endl;
  }

  for (LabelVector::const_iterator i = node->labels.begin();
       i != node->labels.end();
       ++i)
    traverse_label(*i);

  indent();
  out << "for (";
  if (node->init) node->init->accept(this);
  out << "; ";

  if (node->cond) node->cond->accept(this);
  out << "; ";

  if (node->incr) node->incr->accept(this);
  out << ")\n";

  block(node->block);
}

void PrintTraversal::traverse_while(WhileStemnt *node)
{
  if (debug)
  {
    out << "/* WhileStemnt:" ;
    node->location.printLocation(out) ;
    out << " */" << std::endl;
  }

  for (LabelVector::const_iterator i = node->labels.begin();
       i != node->labels.end();
       ++i)
    traverse_label(*i);

  indent();
  out << "while (";
  node->cond->accept(this);
  out << ")\n";
  
  block(node->block);
}

void PrintTraversal::traverse_do_while(DoWhileStemnt *node)
{
  if (debug)
  {
    out << "/* DoWhileStemnt:" ;
    node->location.printLocation(out) ;
    out << " */" << std::endl;
  }

  for (LabelVector::const_iterator i = node->labels.begin();
       i != node->labels.end();
       ++i)
    traverse_label(*i);
  
  indent();
  out << "do ";
  
  if (!node->block->isBlock())
    out << std::endl;
  
  block(node->block);
  if (!node->block->isBlock())
    out << std::endl;
  
  indent();
  out << "while (";
  node->cond->accept(this);
  out << ")";
}

void PrintTraversal::traverse_goto(GotoStemnt *node)
{
  if (debug)
  {
    out << "/* GotoStemnt:" ;
    node->location.printLocation(out) ;
    out << " */" << std::endl;
  }

  for (LabelVector::const_iterator i = node->labels.begin();
       i != node->labels.end();
       ++i)
    traverse_label(*i);

    indent();
    out << "goto ";
    traverse_symbol(node->dest);
}

void PrintTraversal::traverse_return(ReturnStemnt *node)
{
  if (debug)
  {
    out << "/* ReturnStemnt:" ;
    node->location.printLocation(out) ;
    out << " */" << std::endl;
  }

  for (LabelVector::const_iterator i = node->labels.begin();
       i != node->labels.end();
       ++i)
    traverse_label(*i);
  
  indent();
  out << "return";
  
  if (node->result)
  {
    out << ' ';
    node->result->accept(this);
  }
}

void PrintTraversal::traverse_declaration(DeclStemnt *node)
{
  if (debug)
  {
    out << "/* DeclStemnt:";
    node->location.printLocation(out);
    out << " */" << std::endl;
  }

  for (LabelVector::const_iterator i = node->labels.begin();
       i != node->labels.end();
       ++i)
    traverse_label(*i);
  
  indent();
  if (!node->decls.empty())
  {
    DeclVector::const_iterator i = node->decls.begin();
    
    traverse_decl(*i);
    show_base = false;
    for (++i; i != node->decls.end(); ++i)
    {
      out << ", ";
      traverse_decl(*i);
    }
    show_base = true;
  }

  out << ";";
}

void PrintTraversal::traverse_typedef(TypedefStemnt *node)
{
  if (debug)
  {
    out << "/* TypedefStemnt:" ;
    node->location.printLocation(out);
    out << " */" << std::endl;
  }

  for (LabelVector::const_iterator i = node->labels.begin();
       i != node->labels.end();
       ++i)
    traverse_label(*i);

  indent();
  
  out << "typedef ";
  
  if (!node->decls.empty())
  {
    DeclVector::const_iterator i = node->decls.begin();
    traverse_decl(*i);
    for (++i; i != node->decls.end(); ++i)
    {
      out << ", ";
      traverse_decl(*i);
    }
  }
  
  out << ";";
}

void PrintTraversal::traverse_block(Block *node)
{
  if (debug)
  {
    out << "/* BlockStemnt:";
    node->location.printLocation(out);
    out << " */" << std::endl;
  }

  for (LabelVector::const_iterator i = node->labels.begin();
       i != node->labels.end();
       ++i)
    traverse_label(*i);

  indent();
  out << "{\n";

  bool isDecl = (node->head != 0) ? node->head->isDeclaration() : false;
  for (Statement *statement = node->head; statement; statement = statement->next)
  {
    if (isDecl && !statement->isDeclaration())
    {
      isDecl = false;
      out << std::endl;
    }

    incr_indent();
    statement->accept(this);
    decr_indent();

    if (statement->needSemicolon()) out << ";";
    out << std::endl;
  }
  indent();
  out << "}\n";
}

void PrintTraversal::traverse_function_definition(FunctionDef *node)
{
  if (debug)
  {
    out << "/* FunctionDef:";
    node->location.printLocation(out);
    out << " */" << std::endl;
  }

  traverse_decl(node->decl);
  out << std::endl;

  traverse_block(node);
}

void PrintTraversal::traverse_unit(TransUnit *unit)
{
  int inInclude = 0;
  for (Statement *statement = unit->head; statement; statement = statement->next)
  {
    if (inInclude > 0)
    {
      if (statement->isEndInclude()) inInclude--;
      else if (statement->isInclude()) inInclude++;
    }
    else
    {
      if (statement->isInclude()) inInclude++;
      statement->accept(this);
      out << std::endl;
    }
  }
}

void PrintTraversal::meta_char(char c, bool in)
{
  switch (c)
  {
    case '\'':
      if (in) out << "'";
      else out << "\\'";
      break;

    case '"':
      if (in) out << "\\\"";
      else out << "\"";
      break;

    case '\0':
      out << "\\0";
      break;
    case '\\':
      out << "\\\\";
      break;
    case '\n':
      out << "\\n";
      break;
    case '\t':
      out << "\\t";
      break;
    case '\r':
      out << "\\r";
      break;
    case '\f':
      out << "\\f";
      break;
    case '\b':
      out << "\\b";
      break;
    case '\v':
      out << "\\v";
      break;
    case '\a':
      out << "\\a";
      break;
    case ESC_VAL:
      out << "\\e";
      break;

    default:
      // Show low and high ascii as octal
      if ((c < ' ') || (c >= 127))
      {
	char octbuf[8];
	sprintf(octbuf, "%03o", (unsigned char) c);
	out << "\\" << octbuf;
      }
      else out << c;
      break;
  }
}

void PrintTraversal::meta_string(const std::string &str)
{
  for(unsigned i = 0; i < str.size(); ++i)
    meta_char(str[i], true);
}

void PrintTraversal::rel_op(RelOp op)
{
  switch (op)
  {
    case RO_Equal:
      out << "==";
      break;

    case RO_NotEqual:
      out << "!=";
      break;

    case RO_Less:
      out << "<";
      break;

    case RO_LessEql:
      out << "<=";
      break;

    case RO_Grtr:
      out << ">";
      break;

    case RO_GrtrEql:
      out << ">=";
      break;
  }
}

void PrintTraversal::binary_op(BinaryOp op)
{
  switch (op)
  {
    case BO_Plus:
      out << "+";
      break;

    case BO_Minus:
      out << "-";
      break;

    case BO_Mult:
      out << "*";
      break;

    case BO_Div:
      out << "/";
      break;

    case BO_Mod:
      out << "%";
      break;

    case BO_Shl:
      out << "<<";
      break;

    case BO_Shr:
      out << ">>";
      break;

    case BO_BitAnd:
      out << "&";
      break;

    case BO_BitXor:
      out << "^";
      break;

    case BO_BitOr:
      out << "|";
      break;

    case BO_And:
      out << "&&";
      break;

    case BO_Or: 
      out << "||";
      break;

    case BO_Comma:
      out << ",";
      break;

    case BO_Member:
      out << ".";
      break;

    case BO_PtrMember:
      out << "->";
      break;

    default:
      //  case BO_Index        // x[y]
    case BO_Assign:
    case BO_Rel:
      break;
  }
}

void PrintTraversal::unary_op(UnaryOp op)
{
  switch (op)
  {
    case UO_Plus:
      out << "+";
      break;

    case UO_Minus:
      out << "-";
      break;

    case UO_BitNot:
      out << "~";
      break;

    case UO_Not:
      out << "!";
      break;

    case UO_PreInc:
    case UO_PostInc:
      out << "++";
      break;

    case UO_PreDec:
    case UO_PostDec:
      out << "--";
      break;

    case UO_AddrOf:
      out << "&";
      break;

    case UO_Deref:
      out << "*";
      break;
  }
}

void PrintTraversal::assign_op(AssignOp op)
{
  switch (op)
  {
    case AO_Equal:
      out << "=";
      break;

    case AO_PlusEql:
      out << "+=";
      break;

    case AO_MinusEql:
      out << "-=";
      break;

    case AO_MultEql:
      out << "*=";
      break;

    case AO_DivEql:
      out << "/=";
      break;

    case AO_ModEql:
      out << "%=";
      break;

    case AO_ShlEql:
      out << "<<=";
      break;

    case AO_ShrEql:
      out << ">>=";
      break;

    case AO_BitAndEql:
      out << "&=";
      break;

    case AO_BitXorEql:
      out << "^=";
      break;

    case AO_BitOrEql:
      out << "|=";
      break;
  }
}

void PrintTraversal::block(Statement *node)
{
  if (!node)
  {
    incr_indent();
    null();
    decr_indent();
  } 
  else if (node->isBlock()) node->accept(this);
  else
  {
    incr_indent();
    node->accept(this);
    decr_indent();

    if (node->needSemicolon())
      out << ";";
  }
}

