#pragma once

#include "Property.h"
#include <vector>
#include <map>
#include <string>

using namespace std;
/*******************************
该文件将提供属性集的支持。
*******************************/

//属性集合
class PropertySet
{
	typedef map<wstring, Property> PropertyMap;
	PropertyMap m_properties;
	
	vector<const TCHAR*> m_propertyNames;
	vector<const TCHAR*> m_propertyTypes;
	
public:
	//向属性集中注册属性及其类型
	template <class T> void RegisterProperty(void* pObj, const wstring& key, T* pdata);
	
	//操作属性值
	template <class T>
		bool Get(void* pObj, const wstring& key, T& var);
	template <class T>
		bool Set(void* pObj, const wstring& key, const T& var);
	
	const TCHAR * GetPropertyTypeName(const wstring& key);
	TypeID GetPropertyTypeID(const wstring& key);

	//枚举全部的属性名称及类型
	const vector<const TCHAR*>& EnumProperties();
	const vector<const TCHAR*>& EnumPropertyTypes();
};

template <class T> 
void PropertySet::RegisterProperty(void* pObj, const wstring& key, T* pdata)
{
	unsigned int offset = (unsigned int)((char*)pdata - (char*)pObj);
	Property tmp(TYPETOID(T), offset);
	m_properties.insert(PropertyMap::value_type(key, tmp));
}

template <class T>
bool PropertySet::Get(void* pObj, const wstring& key, T& var)
{
	PropertyMap::iterator it = m_properties.find(key);
	if (it == m_properties.end()) return false;
	(it->second).Get((char*)pObj, var);
	return true;
}

template <class T>
bool PropertySet::Set(void* pObj, const wstring& key, const T& var)
{
	PropertyMap::iterator it = m_properties.find(key);
	if (it == m_properties.end()) return false;
	(it->second).Set((char*)pObj, var);
	return true;
}

const TCHAR * PropertySet::GetPropertyTypeName(const wstring& key)
{
	return TYPEID2STRING(GetPropertyTypeID(key));
}

TypeID PropertySet::GetPropertyTypeID(const wstring& key)
{
	PropertyMap::iterator it = m_properties.find(key);
	if (it == m_properties.end()) return TYPETOID(NullType);
	return (it->second).GetTypeID();
}

const vector<const TCHAR*>& PropertySet::EnumProperties()
{
	if(m_propertyNames.empty())
	{
		for (PropertyMap::iterator it = m_properties.begin(); it != m_properties.end(); ++it)
		{
			m_propertyNames.push_back((it->first).c_str());
		}
	}
	
	return m_propertyNames;
}

const vector<const TCHAR*>& PropertySet::EnumPropertyTypes()
{
	if(m_propertyTypes.empty())
	{
		for (PropertyMap::iterator it = m_properties.begin(); it != m_properties.end(); ++it)
		{
			m_propertyTypes.push_back(TYPEID2STRING((it->second).GetTypeID()));
		}
	}
	
	return m_propertyTypes;
}