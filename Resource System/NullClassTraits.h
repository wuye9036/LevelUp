#pragma once

//宏定义，当某个资源类中定义了自己的Null对象的时候便需要使用该宏声明
//此项添加到类声明中
#define DECLARE_NULLOBJ(className) static const className nullObject;

//此项添加到类的namespace中
#define DECLARE_HAS_NULLOBJ(className) \
	class className;\
	template<>\
		class null_type_traits<className>\
	{\
	public:\
		static const bool isHasNullObject = true;\
	};\

//判定空对象的Traits
template<class T>
class null_type_traits
{
public:
	static const bool isHasNullObject = false;
};

//获取正确的获取空对象的函数
template<class T, bool isHasNullObject = null_type_traits<T>::isHasNullObject>
class NullObject
{
public:
	static const T& GetNullObject();
};

template<class T>
class NullObject<T, true>
{
public:
	static const T& GetConstNullObject() {
		return T::nullObject;
	}
	static T& GetNullObject() {
		MessageBox(NULL, _T("试图将空对象作为一个非常数引用返回！"), _T("错误"), MB_OK);
		__asm{ int 3}
		return const_cast<T&>(T::nullObject);
	}
};

template<class T>
class NullObject<T, false>
{
public:
	static const T& GetConstNullObject() {
		MessageBox(NULL, _T("非法解引用空对象！"), _T("错误"), MB_OK);
		__asm{ int 3}

		static int i = 0;
		return i;
	}

	static T& GetNullObject() {
		MessageBox(NULL, _T("试图将空对象作为一个非常数引用返回！"), _T("错误"), MB_OK);
		__asm{ int 3}

		static int i = 0;
		return i;
	}
};