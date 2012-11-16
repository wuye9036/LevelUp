#pragma once

#include <string>
using namespace std;

#ifndef _tstring
	#ifdef _UNICODE
		typedef wstring _tstring;
	#else
		typedef string _tstring;
	#endif
#endif

string toAnsiString(const wstring& instr);
string toAnsiString(const string& instr);
bool toAnsiString(string& outstr, const wstring& instr);
bool toAnsiString(string& outstr, const string& instr);

wstring toWideString(const wstring& instr);
wstring toWideString(const string& instr);
bool toWideString(wstring& outstr, const string& instr);
bool toWideString(wstring& outstr, const wstring& instr);

#ifdef _UNICODE
	#define toTString(instr) toWideString(instr)
	#define toTString2(outstr, instr) toWideString(outstr, instr)
#else
	#define toTString(instr) toAnsiString(instr)
	#define toTString2(outstr, instr) toAnsiString(outstr, instr)
#endif

template<class Container>
Container& push_null(Container& ct, size_t num){
	ct.resize(ct.size() + num);
	return ct;
}