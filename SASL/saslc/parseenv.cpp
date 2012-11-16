
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
    o+     File:         parseenv.cpp
    o+
    o+     Programmer:   Shaun Flisakowski
    o+     Date:         Apr 7, 1995
    o+
    o+     The parse envirornment.
    o+
    o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

#include <iostream>

#include <ctool/parseenv.h>
#include <ctool/project.h>
/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */

extern int yyparse(void);

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
ParseEnv::ParseEnv(std::istream *instream, std::ostream *errstream, const std::string& fname )
{
    yyinstream = instream;
    yyerrstream = errstream;

    yylineno = 1;
    yycolno  = 0;
    yynxtcol = 0;

    transUnit = new TransUnit(fname);
    realfile = transUnit->filename;
    in_realfile = 1;
    filename = transUnit->filename;
    
    parseCtxt = new ParseCtxt;

    err_top_level =0;
    err_cnt = 0;
    err_tok = 0;
    possibleType = true;
    possibleTag = false;
    possibleLabel = false;

    file_ppln=false;
    in_preprocess = 0;
    in_charconst = 0;

    gcc2_paren_cnt = 0;

    tokn_end = &tokn_buff[MAX_TOKN_LEN-1];
}

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
ParseEnv::~ParseEnv()
{
    delete parseCtxt;
}

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
