#pragma once
#include <xmemory>

_STD_BEGIN

/*
执行实际的Construct的函数，是对Std::_Construct的扩展
*/
template <class T> inline 
void _Construct(T* p) {
	new ((void*)p) T;
}
template <class T, class P1, class P2>
inline void _Construct(T* p, const P1& p1, const P2& p2)
{
	new ((void*)p) T(p1, p2);
}

/*
不执行任何操作的Construct
*/
template <typename T> inline
void _ConstructNon(T* p) {
}
template <typename T, typename P1> inline
void _ConstructNon(T* p, const P1& p1) {
}
template <typename T, typename P1, typename P2> inline
void _ConstructNon(T* p, const P1& p1, const P2& p2) {
}

/*
构造策略，依据分配器类型来确定使用哪种构造方式（调用分配器的Construct或者使用外置的Construct
*/
template <class T>
struct ConstructTraits {
	static const bool IsDoConstructInAllocator = false;
};

/*
构造类，用于进行实际的构造工作，依据情况选择
*/
template <class Allocator, class T, bool B = ConstructTraits<T>::IsDoConstructInAllocator>
struct Construct {
};

template <class Allocator, class T>
struct Construct<Allocator, T, true> {
	template <typename T>
	void operator ()(Allocator& al, T* p) {
		al.construct(p);
	}
	template <typename T, typename P1>
	void operator ()(Allocator& al, T* p, const P1& p1) {
		al.construct(p, p1);
	}
	template <typename T, typename P1, typename P2>
	void operator ()(Allocator& al, T* p, const P1& p1, const P2& p2) {
		al.construct(p, p1, p2);
	}
};

template <class Allocator, class T>
struct Construct<Allocator, T, false> {
	template <typename T>
	void operator ()(Allocator& al, T* p) {
		_Construct(p);
	}
	template <typename T, typename P1>
	void operator ()(Allocator& al, T* p, const P1& p1) {
		_Construct(p, p1);
	}
	template <typename T, typename P1, typename P2>
	void operator ()(Allocator& al, T* p, const P1& p1, const P2& p2) {
		_Construct(p, p1, p2);
	}
};
_STD_END

/*
支持宏，用于告诉编译器构造的位置
*/
#define DECLARE_CONSTRUCT_IN_ALLOCATOR(className) \
	template<>\
	class ConstructTraits<className>\
	{\
		static const bool IsConstructInAllocator = true;\
	}