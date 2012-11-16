#pragma once

#include <xmemory>

_STD_BEGIN

template<class _Ty> inline
_Ty _FARQ *_Aligned_Allocate(_SIZT _Count, _SIZT _Alignment, _Ty _FARQ *)
{	// check for integer overflow
	if (_Count <= 0)
		_Count = 0;
	else if (((_SIZT)(-1) / _Count) < sizeof (_Ty))
		_THROW_NCEE(std::bad_alloc, NULL);

	// allocate storage for _Count elements of type _Ty
	return ((_Ty _FARQ *) _aligned_malloc(_Count * sizeof (_Ty), _Alignment));
}

template<class _Ty, _SIZT _Alignment = 1>
class aligned_allocator
	: public _Allocator_base<_Ty>
{	// generic aligned_allocator for objects of class _Ty
public:
	typedef _Allocator_base<_Ty> _Mybase;
	typedef typename _Mybase::value_type value_type;
	typedef value_type _FARQ *pointer;
	typedef value_type _FARQ& reference;
	typedef const value_type _FARQ *const_pointer;
	typedef const value_type _FARQ& const_reference;

	typedef _SIZT size_type;
	typedef _PDFT difference_type;

	static const _SIZT alignment = _Alignment;

	template<class _Other>
	struct rebind
	{	// convert an aligned_allocator<_Ty> to an aligned_allocator <_Other>
		typedef aligned_allocator<_Other, alignment> other;
	};

	pointer address(reference _Val) const
	{	// return address of mutable _Val
		return (&_Val);
	}

	const_pointer address(const_reference _Val) const
	{	// return address of nonmutable _Val
		return (&_Val);
	}

	aligned_allocator() _THROW0()
	{	// construct default aligned_allocator (do nothing)
	}

	aligned_allocator(const aligned_allocator<_Ty>&) _THROW0()
	{	// construct by copying (do nothing)
	}

	template<class _Other>
	aligned_allocator(const aligned_allocator<_Other>&) _THROW0()
	{	// construct from a related aligned_allocator (do nothing)
	}

	template<class _Other>
	aligned_allocator<_Ty>& operator=(const aligned_allocator<_Other>&)
	{	// assign from a related aligned_allocator (do nothing)
		return (*this);
	}

	void deallocate(pointer _Ptr, size_type)
	{	// deallocate object at _Ptr, ignore size
		_aligned_free(_Ptr);
	}

	pointer allocate(size_type _Count)
	{	// allocate array of _Count elements
		return (_Aligned_Allocate(_Count, _Alignment,(pointer)0));
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

	_SIZT max_size() const _THROW0()
	{	// estimate maximum array size
		_SIZT _Count = (_SIZT)(-1) / sizeof (_Ty);
		return (0 < _Count ? _Count : 1);
	}
};

// aligned_allocator TEMPLATE OPERATORS
template<class _Ty,
class _Other> inline
	bool operator==(const aligned_allocator<_Ty>&, const aligned_allocator<_Other>&) _THROW0()
{	// test for aligned_allocator equality (always true)
	return (true);
}

template<class _Ty,
class _Other> inline
	bool operator!=(const aligned_allocator<_Ty>&, const aligned_allocator<_Other>&) _THROW0()
{	// test for aligned_allocator inequality (always false)
	return (false);
}

_STD_END