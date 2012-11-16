#include "stdafx.h"
#include "PropertyType.h"

TypeInfoList* TypeInfoList::m_instance = NULL;

TypeInfoList& TypeInfoList::GetInstance()
{
	if(!m_instance){
		m_instance = new TypeInfoList;
	}
	return *m_instance;
}

void TypeInfoList::InitTypeInfoList()
{
#if defined(_DEBUG)
	//∑¿÷π÷ÿ∏¥≥ı ºªØ
	static bool isInitialized = false;
	assert(!isInitialized);
	isInitialized = true;
#endif
	m_typeInfos.clear();

	DeclTypeName_Nocheck<UnknownType>(_T("Unknown Type"));
	DeclTypeName_Nocheck<NullType>(_T("NullType"));
}

const TCHAR * TypeInfoList::GetTypeName(TypeID tid) {
	return m_typeInfos[tid];
}