/*
	资源实际的管理系统，用于管理资源。
*/
#pragma once

#include <hash_map>
#include <windows.h>
#include "NullStorage.h"
#include "SimpleResPolicy.h"

template <typename, typename> class HResource;
using namespace stdext;

//基类，Manager实际的管理者，T为管理器管理的资源类型
template<typename T>
class ResourceManager
{
	friend class HResource;
	
protected:
	virtual BOOL ReleaseResource(size_t handle) = 0;

public:
	virtual BOOL Initialize() = 0;
	virtual BOOL Update() = 0;

	ResourceManager(){};

	virtual ~ResourceManager(void){}
};

/*Manager的一个派生类，提供一种扩展资源管理类的方式。
	模版参数：
		T				资源类型
		Storage			存储策略，约定参见NullStorage.h
		ManagerPolicy	资源管理策略，约定参见SimpleResPolicy.h
		ThreadingModel	线程模型，可以支持多线程
*/
template	<	
			typename T, 
			template <typename ResType, template <typename> class StorageAllocator> class Storage, 
			template <typename Storage, typename ResType, template <typename> class Allocator, typename ThreadingModel> 
				class ManagerPolicy,
			typename ThreadingModel = SingleThreadModel,
			template <class> class StorageAllocator = std::allocator,
			template <class> class ResourceAllocator = std::allocator
			>
class ResourceManagerImpl : public ResourceManager<T>
{
	//可以根据一种管理器类获取其它管理器类
	template <class Other>
	struct Rebind {
		typedef 
			ResourceManagerImpl<Other, Storage, ManagerPolicy, StorageAllocator, ResourceAllocator> 
			other;
	};

	typedef typename ThreadingModel::Volatile<int>::Type VolatileInt;
	typedef ManagerPolicy<Storage<T, StorageAllocator>, T, ResourceAllocator, ThreadingModel> ResPolicy;
	typename ThreadingModel::Mutex m_mutex;

	ResPolicy m_res;
	typedef typename ThreadingModel::Lock Lock;
	
protected:
	virtual BOOL ReleaseResource(size_t handle) {
		Lock lock(m_mutex);
		return m_res.ReleaseResource(handle);
	}

public:
	virtual BOOL Initialize() {
		Lock lock(m_mutex);
		return m_res.Initialize();
	}

	virtual BOOL Update() {
		Lock lock(m_mutex);
		return m_res.Update();
	}

	//利用字符串作为ID创建一个资源，返回句柄，最多支持两个参数
	HResource<T, ThreadingModel> GetResource(LPCTSTR resstr) {
		Lock lock(m_mutex);
		size_t h;
		VolatileInt* pRefCount;
		T* res = m_res.GetResource(resstr, &h, &pRefCount);
		if(pRefCount) {
			return HResource<T, ThreadingModel>(res, this, pRefCount, h, false);
		}
		return HResource<T, ThreadingModel>(res, this, new int(1), h, true);	
	}
	template <typename P1>
	HResource<T, ThreadingModel> GetResource(LPCTSTR resstr, const P1& param1) {
		Lock lock(m_mutex);
		size_t h;
		VolatileInt* pRefCount;
		T* res = m_res.GetResource(resstr, &h, &pRefCount, param1);
		if(pRefCount) {
			return HResource<T, ThreadingModel>(res, this, pRefCount, h, false);
		}
		return HResource<T, ThreadingModel>(res, this, new VolatileInt(1), h, true);	
	}
	template <typename P1, typename P2>
	HResource<T, ThreadingModel> GetResource(LPCTSTR resstr, const P1& param1, const P2& param2) {
		Lock lock(m_mutex);
		size_t h;
		VolatileInt* pRefCount;
		T* res = m_res.GetResource(resstr, &h, &pRefCount, param1, param2);
		if(pRefCount) {
			return HResource<T, ThreadingModel>(res, this, pRefCount, h, false);
		}
		return HResource<T, ThreadingModel>(res, this, new VolatileInt(1), h, true);	
	}

	void ReleaseHResource(HResource<T, ThreadingModel>& hres)
	{
		hres.~HResource();
		hres.m_handleInManager = 0;
		hres.m_isOwnRCMgrment = true;
		hres.m_pManager = NULL;
		hres.m_pRefCount = NULL;
		hres.m_pResource = NULL;
	}

	~ResourceManagerImpl(void) {
		Lock lock(m_mutex);
		m_res.Clear();
	}
};