#ifndef FCE_UTILITY_H
#define FCE_UTILITY_H

#include <stddef.h>

template <typename T>
void FCE_SafeRelease( T*& ptr ){
	if ( ptr ){
		ptr->Release();
		ptr = NULL;
	}
}

template <typename T>
void FCE_SafeDelete( T*& ptr ){
	if ( ptr ){
		delete ptr;
		ptr = NULL;
	}
}

#endif