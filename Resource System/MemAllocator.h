#pragma once
#include <xmemory>
#include "StdextConstruct.h"
#include <Loki/SmallObj.h>

#pragma pack(push,8)
#pragma warning(push,3)

 #pragma warning(disable: 4100)

_STD_BEGIN
template<class _Ty>
	class LokiMemPoolAllocator
		: public _Allocator_base<_Ty>
	{	// generic allocator for objects of class _Ty
public:
	Loki::SmallObject<> lokiAllocator;

	typedef _Allocator_base<_Ty> _Mybase;
	typedef typename _Mybase::value_type value_type;


	typedef value_type _FARQ *pointer;
	typedef value_type _FARQ& reference;
	typedef const value_type _FARQ *const_pointer;
	typedef const value_type _FARQ& const_reference;

	typedef _SIZT size_type;
	typedef _PDFT difference_type;

	template<class _Other>
		struct rebind {
			typedef LokiMemPoolAllocator<_Other> other;
		};

	pointer address(reference _Val) const {
		return (&_Val);
	}

	const_pointer address(const_reference _Val) const {
		return (&_Val);
	}

	LokiMemPoolAllocator() {}

	LokiMemPoolAllocator(const LokiMemPoolAllocator<_Ty>&){}

	template<class _Other>
		LokiMemPoolAllocator(const LokiMemPoolAllocator<_Other>&){}

	template<class _Other>
		LokiMemPoolAllocator<_Ty>& operator=(const LokiMemPoolAllocator<_Other>&)
	{	// assign from a related allocator (do nothing)
		return (*this);
	}

	void deallocate(pointer _Ptr, size_type size)
	{	// deallocate object at _Ptr, ignore size
		lokiAllocator.operator delete(_Ptr, size * sizeof(value_type));
	}

	pointer allocate(size_type _Count) {
		return pointer(lokiAllocator.operator new(_Count * sizeof(value_type)));
	}

	pointer allocate(size_type _Count, const void _FARQ *)
	{	// allocate array of _Count elements, ignore hint
		return (allocate(_Count));
	}

	void construct(pointer _Ptr, const _Ty& _Val)
	{	// construct object at _Ptr with value _Val
		_Construct(_Ptr, _Val);
	}

	void destroy(pointer _Ptr)
	{	// destroy object at _Ptr
		_Destroy(_Ptr);
	}

	_SIZT max_size() const
	{	// estimate maximum array size
		_SIZT _Count = (_SIZT)(-1) / sizeof (_Ty);
		return (0 < _Count ? _Count : 1);
	}
	};

		// allocator TEMPLATE OPERATORS
template<class _Ty,
	class _Other> inline
	bool operator==(const LokiMemPoolAllocator<_Ty>&, const LokiMemPoolAllocator<_Other>&)
	{	// test for allocator equality (always true)
	return (true);
	}

template<class _Ty,
	class _Other> inline
	bool operator!=(const LokiMemPoolAllocator<_Ty>&, const LokiMemPoolAllocator<_Other>&)
	{	// test for allocator inequality (always false)
	return (false);
	}

		// CLASS allocator<void>
template<> class _CRTIMP2 LokiMemPoolAllocator<void>
	{	// generic allocator for type void
public:
	typedef void _Ty;
	typedef _Ty _FARQ *pointer;
	typedef const _Ty _FARQ *const_pointer;
	typedef _Ty value_type;

	template<class _Other>
		struct rebind
		{	// convert an allocator<void> to an allocator <_Other>
		typedef LokiMemPoolAllocator<_Other> other;
		};

	LokiMemPoolAllocator()
		{	// construct default allocator (do nothing)
		}

	LokiMemPoolAllocator(const LokiMemPoolAllocator<_Ty>&)
		{	// construct by copying (do nothing)
		}

	template<class _Other>
		LokiMemPoolAllocator(const LokiMemPoolAllocator<_Other>&)
		{	// construct from related allocator (do nothing)
		}

	template<class _Other>
		LokiMemPoolAllocator<_Ty>& operator=(const LokiMemPoolAllocator<_Other>&)
		{	// assign from a related allocator (do nothing)
		return (*this);
		}
	};
_STD_END

#pragma warning(default: 4100)

#pragma warning(pop)
#pragma pack(pop)