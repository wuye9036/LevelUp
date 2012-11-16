#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include "Common.h"

#include <string>

class context
{
public:
	context(unit* pOwnerUnit)
		: currentUnit_(pOwnerUnit)
	{
	}

	std::string& CurrentLine();

	int CurrentLineNo();
	void CurrentLineNo(int lineIdx);

	symbol_table* 	RootSymbolTable();
	symbol_table*	CurrentSymbolTable();
	symbol_table*	EnterScope();
	symbol_table*	LeaveScope();
private:
	std::string		currentLineString_;
	std::string 	fileName_;
	unit*			currentUnit_;
	h_symbol_table	symTbl_;
};

#endif // CONTEXT_H_INCLUDED
