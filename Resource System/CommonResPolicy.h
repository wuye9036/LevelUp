#pragma once
#include <windows.h>

template
<
	typename StoragePolicy,
	typename ResType,
	template <typename> class Allocator,
	class ThreadingModel
>
class CommonResPolicy
{
public:
	typedef typename ThreadingModel::Volatile<int>::Type VolatileInt;
	class ResStorage {
	public:
		ResType*	pRes;
		VolatileInt	refCount;
	};
	typedef typename StoragePolicy::Rebind<ResStorage>::OtherStorage Storage;
	Allocator<ResStorage>	m_resStorageAllocator;
	Allocator<ResType>		m_resAllocator;

	Construct<Allocator<ResType>, ResType>			m_resConstruct;
	Construct<Allocator<ResStorage>, ResStorage>	m_resStorageConstruct;

	Storage m_storage;

	BOOL Initialize() {
		if(!m_storage.Empty()) {
			return FALSE;
		}
		return TRUE;
	}
	BOOL Update() {
		return TRUE;
	}

	ResType* GetResource(LPCTSTR resstr, size_t* ph, VolatileInt** ppRefCount) {
		ResStorage* pResStorage = m_storage.Find(resstr, ph);
		if(!pResStorage) {
			pResStorage = m_resStorageAllocator.allocate(1);
			m_resStorageConstruct(m_resStorageAllocator, pResStorage);
			pResStorage->pRes = m_resAllocator.allocate(1);
			m_resConstruct(m_resAllocator, pResStorage->pRes);
			pResStorage->refCount = 0;
			*ph = m_storage.Insert(resstr, pResStorage);		
		}
		ThreadingModel::Inc(&(pResStorage->refCount));
		*ppRefCount = &(pResStorage->refCount);
		return pResStorage->pRes;
	}
	template <typename P1>
	ResType* GetResource(LPCTSTR resstr, size_t* ph, VolatileInt** ppRefCount, const P1& p1) {
		ResStorage* pResStorage = m_storage.Find(resstr, ph);
		if(!pResStorage) {
			pResStorage = m_resStorageAllocator.allocate(1);
			m_resStorageConstruct(m_resStorageAllocator, pResStorage);
			pResStorage->pRes = m_resAllocator.allocate(1);
			m_resConstruct(m_resAllocator, pResStorage->pRes, p1);
			pResStorage->refCount = 0;
			*ph = m_storage.Insert(resstr, pResStorage);		
		}
		ThreadingModel::Inc(&(pResStorage->refCount));
		*ppRefCount = &(pResStorage->refCount);
		return pResStorage->pRes;
	}
	template <typename P1, typename P2>
	ResType* GetResource(LPCTSTR resstr, size_t* ph, VolatileInt** ppRefCount, const P1& p1, const P2& p2) {
		ResStorage* pResStorage = m_storage.Find(resstr, ph);
		if(!pResStorage) {
			pResStorage = m_resStorageAllocator.allocate(1);
			m_resStorageConstruct(m_resStorageAllocator, pResStorage);
			pResStorage->pRes = m_resAllocator.allocate(1);
			m_resConstruct(m_resAllocator, pResStorage->pRes, p1, p2);
			pResStorage->refCount = 0;
			*ph = m_storage.Insert(resstr, pResStorage);		
		}
		ThreadingModel::Inc(&(pResStorage->refCount));
		*ppRefCount = &(pResStorage->refCount);
		return pResStorage->pRes;
	}

	BOOL ReleaseResource(size_t h) {
		if(h != 0) {
			size_t th;
			if(m_storage.Find(LPCTSTR(h), &th)->refCount > 0) {
				return TRUE;
			}
			ResStorage* pResStorage = m_storage.Erase(h);
			m_resAllocator.destroy(pResStorage->pRes);
			m_resAllocator.deallocate(pResStorage->pRes, 1);
			m_resStorageAllocator.destroy(pResStorage);
			m_resStorageAllocator.deallocate(pResStorage, 1);
		}
		return TRUE;
	}
	void Clear() {
		if(!m_storage.Empty()) {
			__asm { int 3 }
		}
	}
};