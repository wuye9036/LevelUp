#include "Util/String.h"
#include <vector>
using namespace std;

vector<char> _string_buf;

string toAnsiString(const wstring& instr){
	//分配空间
	size_t required = wcstombs(NULL, instr.c_str(), 0);
	_string_buf.resize(required + 1);

	//转换
	size_t l = wcstombs(&(_string_buf[0]), instr.c_str(), required+1);
	if(l == size_t(-1)){
		return string();
	} 

	return string((char*)(&_string_buf[0]));
}

string toAnsiString(const string& instr){
	return instr;
}

bool toAnsiString(string& outstr, const wstring& instr){
	//分配空间
	size_t required = wcstombs(NULL, instr.c_str(), 0);
	outstr.resize(required + 1);

	//转换
	size_t l = wcstombs(&(outstr[0]), instr.c_str(), required+1);
	if(l == size_t(-1)){
		return false;
	} 

	outstr.resize(l);
	return true;
}

bool toAnsiString(string& outstr, const string& instr){
	outstr = instr;
	return true;
}

wstring toWideString(const wstring& instr){
	return instr;
}

wstring toWideString(const string& instr){
	//分配空间
	size_t required = mbstowcs(NULL, instr.c_str(), 0);
	_string_buf.resize((required + 1) * 2);

	//转换
	size_t l = mbstowcs((wchar_t*)&(_string_buf[0]), instr.c_str(), required+1);
	if(l == size_t(-1)){
		return wstring();
	} 

	return wstring((wchar_t*)(&_string_buf[0]));
}

bool toWideString(wstring& outstr, const string& instr)
{
	//分配空间
	size_t required = mbstowcs(NULL, instr.c_str(), 0);
	outstr.resize(required + 1);

	//转换
	size_t l = mbstowcs(&(outstr[0]), instr.c_str(), required+1);
	if(l == size_t(-1)){
		return false;
	} 
	
	outstr.resize(l);
	return true;
}

bool toWideString(wstring& outstr, const wstring& instr){
	outstr = instr;
	return true;
}