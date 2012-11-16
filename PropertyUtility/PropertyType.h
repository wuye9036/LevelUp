#pragma once
/************************************
该文件提供对属性的 类型/类型ID/类型名称 的相关支持。
************************************/	

//auto type register: 提供自动的属性类型注册功能，但是可能会有风险，应当谨慎使用
#define AUTO_TYPE_REGISTER_ENABLED

#include <vector>
#include <cassert>
#if defined(AUTO_TYPE_REGISTER_ENABLED)
	#include <typeinfo.h>	
	#include <cstdlib>
#endif
	
using namespace std;


/*****************************
功能说明：类型识别部分所需要的辅助类型
*****************************/
class NullType{};
class UnknownType{};
typedef size_t TypeID;

//此处集中注册类型
#define DECL_TYPES() \
DeclTypeName<char>(_T("char"));\
DeclTypeName<unsigned char>(_T("uchar"));\
DeclTypeName<short>(_T("short"));\
DeclTypeName<unsigned short>(_T("ushort"));\
DeclTypeName<int>(_T("int32"));\
DeclTypeName<unsigned int>(_T("uint"));\
DeclTypeName<float>(_T("single"));\
DeclTypeName<double>(_T("double"));\
DeclTypeName<std::string>(_T("std::string"));\
DeclTypeName<std::wstring>(_T("std::wstring"));

template <class T> class traits_type_to_id
{
public:
	static TypeID id;
};
template<class T> TypeID traits_type_to_id<T>::id = 0;

class TypeInfoList
{
	std::vector<const TCHAR *> m_typeInfos;
	static TypeInfoList* m_instance;

	template <class T> void AutoRegType();
	template <class T> void DeclTypeName_Nocheck(const TCHAR* str);
	template <class T> void DeclTypeName(const TCHAR* str);
	void InitTypeInfoList();

public:
	TypeInfoList()
	{
		InitTypeInfoList();
		DECL_TYPES();
	}
	
	const TCHAR * GetTypeName(TypeID tid);
	template <class T> TypeID GetTypeID();
	static TypeInfoList& GetInstance();

};

#define TYPETOID(type) (TypeInfoList::GetInstance().GetTypeID<type>())
#define TYPEID2STRING(tid) (TypeInfoList::GetInstance().GetTypeName(tid))
/**************************/

/****************************
Class TypeInfoList Implementation
****************************/
template <class T> TypeID TypeInfoList::GetTypeID() 
{
#if defined(AUTO_TYPE_REGISTER_ENABLED)
	AutoRegType<T>();
#endif
	return traits_type_to_id<T>::id;
}

/*****
在注册变量是不考虑检测，适用于一些特殊类型的注册工作（因为那些类型往往代表无效值，因此可能和类型的判别值冲突）
*****/
template <class T> void TypeInfoList::DeclTypeName_Nocheck(const TCHAR* str)
{
	traits_type_to_id<T>::id = m_typeInfos.size();
	m_typeInfos.push_back(str);
}

/*****
注册常规类型时使用的函数，将类型、名称、ID对应起来。
*****/
template <class T> void TypeInfoList::DeclTypeName(const TCHAR* str)
{
	if(traits_type_to_id<T>::id == 0) {
		m_typeInfos.push_back(str); 
		traits_type_to_id<T>::id = m_typeInfos.size() - 1;
	} else {
		assert(!"Type Register Again!");
	}
}

/*****
用于完成对型别的自动注册
*****/
template <class T> void TypeInfoList::AutoRegType()
{
	static TCHAR typeName[256];
	if(traits_type_to_id<T>::id == 0)
	{
		mbstowcs(typeName, typeid(T).name(), 256);
		m_typeInfos.push_back(typeName); 
		traits_type_to_id<T>::id = m_typeInfos.size() - 1;
	}
}