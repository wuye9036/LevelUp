#pragma once

#include "PropertyType.h"

//属性，支持基本的读写操作
class Property
{
	const TypeID		tid;
	unsigned int		pDataOffset;
public:
	Property(TypeID id, unsigned int p) : tid(id), pDataOffset(p){}
	
	template <class T> void Get(void* pObj, T& var)
	{
		if (tid != TYPETOID(T))	{
			assert(!"type-error");
		}
#if defined(_DEBUG)
		if(tid == 0) {
		assert(!"Warning!!! Type Conversation Between Two Unregistered Vars!!!\n");
		}
#endif
		var = *(T*)((char*)pObj + pDataOffset);
	}
	
	template <class T> void Set(char* pObj, const T& var)
	{
		if (tid != TYPETOID(T))	{
			assert(!"type-error");
		}
#if defined(_DEBUG)
		if(tid == 0) {
		assert(!"Warning!!! Type Conversation Between Two Unregistered Vars!!!\n");
		}
#endif
		*(T*)((char*)pObj + pDataOffset) = var;
	}
	
	TypeID GetTypeID()
	{
		return tid;
	}
};