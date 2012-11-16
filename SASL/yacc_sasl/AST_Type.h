#ifndef AST_TYPE_H_INCLUDED
#define AST_TYPE_H_INCLUDED

#include "Common.h"

#include "Dup.h"
#include "TypeCode.h"
#include "Semantic.h"

#include <iostream>
#include <vector>

#include <assert.h>

struct decl;

class type_base;
class buidin_type;

typedef duppable<type_base> duppable_type;

class type_base : public duppable_type
{
public:
	type_base(type_type _type=TT_Simple);
	virtual ~type_base();

	virtual type_base* dup0() const =0;	// deep-copy

	virtual type_base*   extend(type_base *extension) { assert(0); return NULL; }

	virtual type_qualifier get_qualifiers( void ) const = 0;

	bool	is_simple_type() const { return (typecode == TT_Simple); }
	bool	is_function() const { return (typecode == TT_Function); }
	bool	is_array() const { return (typecode == TT_Array); }

	type_type		typecode;
	storage_type	storage;
	type_qualifier	qualifier;

	//output type information as text
	virtual void output(std::ostream& os){}
};

/*****
Base Types That SASL support in naive ways
*****/
class buidin_type : public type_base
{
public:
	buidin_type( BuildinTypeSpec = BT_NoType );

	~buidin_type();

	type_base* dup0() const;	// deep-copy

	type_base* extend(type_base *extension) { assert(0); return NULL; }

	type_qualifier get_qualifiers( void ) const;

	buidin_type& operator = (const buidin_type &b);

	virtual void output(std::ostream& os);

	BuildinTypeSpec	typecode;

};

/***
Structure Types
***/
class struct_type : public type_base
{
public:
	struct_type();
	~struct_type();

	type_base* dup0() const;	// deep-copy

	type_qualifier get_qualifiers( void ) const;
	struct_type& operator = (const struct_type &b);

	void add_component(h_decl decl);
	void set_component_list(h_decl decl);

	h_symbol_entry		type_name;   // typedef name for a UserType
	std::vector<h_decl>	components;
};

/***
Array Types
***/
class array_type : public type_base
{
public:
	array_type(h_expression s) {};
	~array_type();

	type_base* dup0() const;	// deep-copy

	type_qualifier get_qualifiers( void ) const;
	virtual h_type_base get_content_type(){return content_type;}

	h_type_base	content_type;
	h_expression	size;
};
//
//// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class function_type : public type_base
{
public:
	function_type(const std::vector<h_decl>& args_list);
	~function_type();

	type_base* dup0() const;	// deep-copy

	void add_arg(h_decl arg);
	void add_arg_list(h_decl args);

	type_qualifier get_qualifiers( void ) const;
	Semantic get_semantic( void ) const;

	unsigned int	arg_count;
	unsigned int	size;

	std::vector<h_decl>	args;
	h_type_base			return_type;	// The return type_base
};

#endif // AST_TYPE_H_INCLUDED
