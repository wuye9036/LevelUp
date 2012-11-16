#ifndef CSTREXT_H_INCLUDED
#define CSTREXT_H_INCLUDED

#include <string>
#include <sstream>
#include <cstdarg>

template <class T>
std::string to_string(T t, std::ios_base & (*f)(std::ios_base&))
{
  std::ostringstream oss;
  oss << f << t;
  return oss.str();
}

inline std::string format(const char * format, ...)
{
	va_list argList;
	va_start( argList, format );

	std::string retStr;

	char retStrBuf[4096];

	int len = _vsnprintf(retStrBuf, 4095, format, argList);

	char* pStrBuf = NULL;
	int strSize = 4096;

	while (len == -1)
	{
		strSize <<= 1;
		delete [] pStrBuf;
		pStrBuf = new char[strSize];
		if( !pStrBuf ){	break; }
		len = _vsnprintf(pStrBuf, strSize - 1, format, argList);
	}

	va_end( argList );

	if(len == -1){
		return retStr;
	}

	retStr.resize(len);

	if(pStrBuf){
		retStr.assign(pStrBuf);
		delete [] pStrBuf;
	} else {
		retStr.assign(retStrBuf);
	}

	return retStr;
}
#endif // CSTREXT_H_INCLUDED
