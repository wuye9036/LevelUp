#ifndef DECL_H_INCLUDED
#define DECL_H_INCLUDED

#include "AST_Type.h"
#include "Common.h"

#include <vector>

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
struct decl
{
  public:
	decl();
	decl( h_type_base type, symbol_entry* pSymEntry = NULL );
	virtual ~decl();

	bool	is_typedef() const { return (storage == ST_Typedef); }
	bool	is_static() const { return (storage == ST_Static); }
	bool	is_array() const { return (form->typecode == TT_Array); }

	void	clear();

	decl*   dup0() const;
	decl*   dup() const;		// deep-copy

	void	copy(const decl& decl);	// shallow copy

	storage_type	storage;	//eg.: extern
	h_type_base		form;		//eg.: int *x[5]

	Semantic		semantic;	//ie: NORMAL0
	symbol_entry*	name;		// The symbol being declared.

	h_decl			next; //保存Decl List，用于将一组decl串起来。

	void output(std::ostream& os);
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

typedef	std::vector<h_decl>	decl_vector;

#endif // DECL_H_INCLUDED
