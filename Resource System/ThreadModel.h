#pragma once
#include <boost/thread.hpp>

using boost::mutex;
using boost::mutex::scoped_lock;

//这里使用的Loki的线程模型
class SingleThreadMutex 
{
};

class SingleThreadLock
{
public:
	SingleThreadLock(const SingleThreadMutex&) {
	}
	~SingleThreadLock(){
	}
};

class SingleThreadModel
{
public:
	typedef SingleThreadLock	Lock;
	typedef SingleThreadMutex	Mutex;

	template <class T>
	struct Volatile {
		typedef T Type;
	};

	static int Inc(int* pInt){
		return ++(*pInt);
	}
	static int Dec(int* pInt){
		return --(*pInt);
	}
	static int Exchange(int* pInt, int i){
		int rv = *pInt;
		*pInt = i;
		return rv;
	}
};

class MultiThreadModel
{
public:
	typedef scoped_lock	Lock;
	typedef mutex		Mutex;

	template <class T>
	struct Volatile {
		typedef volatile T Type;
	};

	static int Inc(volatile int* pInt){
		return InterlockedIncrement((volatile long*)pInt);
	}
	static int Dec(volatile int* pInt){
		return InterlockedDecrement((volatile long*)pInt);
	}
	static int Exchange(volatile int* pInt, int i){
		return InterlockedExchange((volatile long*)pInt, i);
	}
};