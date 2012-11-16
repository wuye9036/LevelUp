#ifndef SYMBOL_H_INCLUDED
#define SYMBOL_H_INCLUDED

#include "Common.h"

#include <string>
#include <vector>
#include <boost/function.hpp>
#include <boost/unordered_map.hpp>

/***
***/
enum symbol_type
{
	SYMT_Decl = 0,
	SYMT_Label,
	SYMT_UserType
};

class scope{
};

/************
Symbol分三种：
	usertype的Symbol
	decl的Symbol
	lable的Symbol
************/
class symbol_table
{
public:
	symbol_table(symbol_table* parent);


	symbol_entry* LocalLookup(const std::string& symbolName);
	symbol_entry* LookupDown(const std::string& symbolName);
	symbol_entry* LookupUp(const std::string& symbolName);

	void Visit(boost::function<void (symbol_entry*) > callbackFunc, bool isDeep);

	void AddSymbolEntryToList(const std::string& entryName, h_symbol_entry symEntry);

	static h_symbol_table Root(){
		return root_;
	}

private:
	static h_symbol_table root_;

	symbol_table* parent_;
	std::vector<h_symbol_table> children_;

	boost::unordered_map<std::string, h_symbol_entry> entries_;
};

class symbol_entry
{
public:
	std::string		symbol_name;

	scope*			pscope;

	decl*			pdecl;		//int x;
	Label*			plable;		//goto LBL;
	type*			ptype;		//struct x{};

	symbol_type		type;
};


#endif // SYMBOL_H_INCLUDED
