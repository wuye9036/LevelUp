// ReadWriteCondLock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <windows.h>
#include <iostream>

using namespace std;
using namespace boost;

class read_write_mutex
{
	mutex mtx_;
	int read_cnt_;
	condition cond_;

public:
	read_write_mutex(): read_cnt_(0){}
	~read_write_mutex(){}

	void lock_read(){
		mutex::scoped_lock lock(mtx_);
		while(read_cnt_ < 0){
			cond_.wait(lock);
		}
		++read_cnt_;
	}
	
	void unlock_read(){
		mutex::scoped_lock lock(mtx_);
		--read_cnt_;
		cond_.notify_all();
	}

	void lock_write(){
		mutex::scoped_lock lock(mtx_);
		while(read_cnt_ != 0){
			cond_.wait(lock);
		}
		read_cnt_ = -1;
	}

	void unlock_write(){
		mutex::scoped_lock lock(mtx_);
		read_cnt_ = 0;
		cond_.notify_all();
	}
};

class scoped_rlock
{
	read_write_mutex& cond_;
public:
	scoped_rlock(read_write_mutex& c):cond_(c){cond_.lock_read();}
	~scoped_rlock(){cond_.unlock_read();}
};

class scoped_wlock
{
	read_write_mutex& cond_;
public:
	scoped_wlock(read_write_mutex& c):cond_(c){cond_.lock_write();}
	~scoped_wlock(){cond_.unlock_write();}
};

int top = 0;
int stack[1000];
read_write_mutex rwc;
mutex io_mutex;

void read(int val)
{
	for(int i = 0; i < 20; ++i)
	{
		Sleep(2);

		scoped_rlock rlock(rwc);
		int s = top;

		{
			mutex::scoped_lock lock(io_mutex);
			cout << "read begin " << val << endl;
		}

		Sleep(10);

		{
			mutex::scoped_lock lock(io_mutex);
			cout << "read end " << val << endl;
		}

		if(s != top)
		{
			cout << "error!"<<endl;
		}
	}
}

void write(int val)
{
	for(int i = 0; i < 20; ++i)
	{
		Sleep(2);

		scoped_wlock wlock(rwc);

		{
			mutex::scoped_lock lock(io_mutex);
			cout << "write begin " << val << endl;
		}

		Sleep(5);

		{
			mutex::scoped_lock lock(io_mutex);
			cout << "write end " << val << endl;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	thread_group rtg;

	for(int i = 0; i < 10; ++i)
	{
		rtg.create_thread(boost::bind(&read, i));
	}

	for(int i = 0; i < 2; ++i)
	{
		rtg.create_thread(boost::bind(&write, i));
	}

	rtg.join_all();

	system("pause");

	return 0;
}

