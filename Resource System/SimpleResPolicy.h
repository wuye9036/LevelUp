#pragma once
#include <windows.h>
#include "MemAllocator.h"
/*
模版参数：
	StoragePolicy	存储策略
	ResType			资源类型
	Allocator		资源的分配器
	ThreadingModel	线程模型

该类没有提供线程安全，它将由它的调用者保证，它为线程安全提供类型定义支持。
*/
template 
<
	typename StoragePolicy,
	typename ResType,
	template <typename> class Allocator,
	class ThreadingModel
>
class SimpleResPolicy
{
protected:
	//第一步，需要定义实际的存储结构
	typedef typename ThreadingModel::Volatile<int>::Type VolatileInt;
	typedef VolatileInt Storage;

	Storage	m_storage;
	//分配器与构造器
	Allocator<ResType> m_resAllocator;
	Construct<Allocator<ResType>, ResType> m_construct;
	//以下为必须实现的函数

public:
	//初始化，负责针对Storage进行一些初始化操作
	BOOL Initialize() {
		m_storage = 0;
		return TRUE;
	}

	//更新，对Storage进行更新操作
	BOOL Update() {
		return TRUE;
	}

	/*获取资源，返回指向资源类型的指针
	参数：
		[in ]resstr		资源字符串，用于指示资源，管理器中唯一
		[out]h			句柄（键），用于查找对应的值用，保存在HResource<T>中，这里为TCHAR*
		[out]ppRefCount	引用计数的指针的指针，用于返回引用计数的指针，供HResource<T>计算引用计数用，如果资源分配策略没有保存该指针，则应当返回NULL
	*/
	ResType* GetResource(LPCTSTR resstr, size_t* h, VolatileInt** ppRefCount) {
		ThreadingModel::Inc(&m_storage);
		*ppRefCount = NULL;
		ResType* p = m_resAllocator.allocate(1);
		*h = (size_t)((void*)p);
		m_construct(m_resAllocator, p);
		return p;		
	}
	template <typename P1>
	ResType* GetResource(LPCTSTR resstr, size_t* h, VolatileInt** ppRefCount, const P1& param1) {
		ThreadingModel::Inc(&m_storage);
		*ppRefCount = NULL;
		ResType* p = m_resAllocator.allocate(1);
		*h = (size_t)((void*)p);
		m_construct(m_resAllocator, p, p1, p2);
		return p;		
	}
	template <typename P1, typename P2>
	ResType* GetResource(LPCTSTR resstr, size_t* h, VolatileInt** ppRefCount, const P1& param1, const P2& param2)
	{
		ThreadingModel::Inc(&m_storage);
		*ppRefCount = NULL;
		ResType* p = m_resAllocator.allocate(1);
		*h = (size_t)((void*)p);
		m_construct(m_resAllocator, p, p1, p2);
		return p;		
	}

	BOOL ReleaseResource(size_t h) {
		if(h != 0) {
			ThreadingModel::Dec(&m_storage);
			m_resAllocator.destroy((ResType*)h);
			m_resAllocator.deallocate((ResType*)h, 1);
		}
		return TRUE;
	}
	void Clear() {
		if(m_storage) {
			__asm { int 3 }
		}
	}
};

