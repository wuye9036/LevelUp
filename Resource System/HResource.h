/*
	支持引用计数
*/
#pragma once
#include <string>
#include "NullClassTraits.h"
#include "ThreadModel.h"

using namespace std;

//资源句柄类，注意，单一对象只可以被单一线程访问，若想多个线程同时访问该对象，需要copy
template<typename T, typename ThreadingModel = SingleThreadModel>
class HResource
{
	friend class ResourceManagerImpl;

protected:
	typedef typename ThreadingModel::Volatile<int>::Type VolatileInt;
	bool				m_isOwnRCMgrment;
	size_t				m_handleInManager;
	VolatileInt*		m_pRefCount;
	ResourceManager<T>* m_pManager;
	T*					m_pResource;

	
	/*
	构造函数，仅仅ResourceManager可以调用。
		参数含义：
		pResource	资源指针
		pManager	管理器指针
		pRefCount	存储引用计数的指针
		h			句柄，用于删除用。
		isMgrment	指示是由管理器管理引用计数指针还是由句柄管理引用计数指针
	*/
	HResource(T* pResource, ResourceManager<T>* pManager, VolatileInt* pRefCount, size_t h, bool isMgrment)
		:	m_pManager(pManager), 
			m_pResource(pResource),
			m_pRefCount(pRefCount), 
			m_handleInManager(h), 
			m_isOwnRCMgrment(isMgrment)
	{}

public:
	static BOOL IsNullHandle(HResource& hres) {
		return m_pResource != NULL;
	}

	ResourceManager<T>* GetManager(){
		return m_pManager;
	}

	HResource(const HResource& rhs)
		:	m_pRefCount(rhs.m_pRefCount), m_pResource(rhs.m_pResource),
			m_pManager(rhs.m_pManager), m_handleInManager(rhs.m_handleInManager),
			m_isOwnRCMgrment(rhs.m_isOwnRCMgrment)
	{
		if(m_pRefCount){
			ThreadingModel::Inc(m_pRefCount);
		}
	}

	HResource& operator = (const HResource& rhs) {	
		if(this == &rhs) return *this;
		this->~HResource();
		m_pRefCount = rhs.m_pRefCount;
		if(m_pRefCount){
			ThreadingModel::Inc(m_pRefCount);
		}
		m_pManager = rhs.m_pManager;
		m_pResource = rhs.m_pResource;
		m_handleInManager = rhs.m_handleInManager,
		m_isOwnRCMgrment = rhs.m_isOwnRCMgrment;
		return *this;
	}

	const T& operator* () const{
		return (m_pResource ? *m_pResource : NullObject<T>::GetConstNullObject());
	}

	T& operator* () {
		return (m_pResource ? *m_pResource : NullObject<T>::GetNullObject());
	}

	~HResource(void) {
		if(!m_pResource) return;
		if(ThreadingModel::Dec(m_pRefCount) == 0) {
			m_pManager->ReleaseResource(m_handleInManager);
			if(m_isOwnRCMgrment) {
				delete m_pRefCount;
			}
		}
	}
};