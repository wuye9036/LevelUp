#pragma once
#include <hash_map>

/*
_STD_BEGIN
template<>
struct less{
	bool operator () (LPCTSTR lhs, LPCTSTR rhs) const {
		return _tcscmp(lhs, rhs) < 0;
	}
};
_STD_END
*/
using namespace stdext;

//空存储，不存储任何信息
template <typename T, template <typename> class Allocator>
class NullStorage
{
public:
	template <class Other>
		struct Rebind {
			typedef NullStorage<Other, Allocator> OtherStorage; 
		};
	typedef T ResType;
};

//它是不管线程安全的。但是Allocator需要保证线程安全。
template <typename T, template <typename> class Allocator>
class HashMapStorage
{
public:
	template <class Other>
	struct Rebind {
		typedef HashMapStorage<Other, Allocator> OtherStorage; 
	};
	typedef T ResType;
	typedef typename hash_map<LPCTSTR, T*>::value_type value_type;
	typedef 
		typename hash_map <	LPCTSTR, T*, 
							hash_compare<LPCTSTR, std::less<LPCTSTR> >, 
							Allocator<value_type> >		
		CustomAllocHashMap;
	typedef typename CustomAllocHashMap::iterator iterator;

	CustomAllocHashMap m_resmap;

	T* Find(LPCTSTR pstr, size_t* h)
	{
		iterator it = m_resmap.find(pstr);
		if(it != m_resmap.end()) {
			*h = size_t(it->first);
			return it->second;
		}
		return NULL;
	}
	size_t Insert(LPCTSTR pstr, T* pT)
	{
		iterator it = m_resmap.find(pstr);
		if(it != m_resmap.end()) {
			return size_t(it->first);
		}
		//拷贝名称内存
		TCHAR* pNewStr = new TCHAR[_tcslen(pstr) + 1];
		_tcscpy(pNewStr, pstr);
		m_resmap.insert(value_type(pNewStr, pT));
		return size_t(pNewStr);
	}
	T* Erase(size_t h) {
		iterator it = m_resmap.find((LPCTSTR)(h));
		if(it == m_resmap.end()) return FALSE;
		delete [] it->first;
		T* rv = it->second;
		m_resmap.erase(it);
		return rv;
	}
	BOOL Empty(){
		return m_resmap.empty();
	}
};
