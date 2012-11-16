// ResourceSystemDemo.cpp : 定义控制台应用程序的入口点。
//

#define _CRTDBG_MAP_ALLOC
#include "stdafx.h"
#include "FileSystem.h"
#include "ResourceManager.h"
#include "HResource.h"
#include "CommonResPolicy.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include <stdlib.h>
#include <crtdbg.h>

using namespace boost;

DECLARE_HAS_NULLOBJ(Test);
class Test
{
private :
	
	char * buf;
public:
	DECLARE_NULLOBJ(Test);
	
	Test(int, int) {
		buf = new char[1000];
		//cout << "Construct With Two Int!" << endl;
	}
	Test(int){
		buf = new char[1000];
		//cout << "Construct With Int!" << endl;
	}
	//Test() {
		//buf = new char[1000];
		//cout << "Construct With Nothing" << endl;
	//}
	~Test()
	{
		delete [] buf;
	}
	//void Output() {
		//cout << "Hello" << endl;
	//}
};

const Test Test::nullObject(1);
typedef HResource<Test, MultiThreadModel> HTest;
typedef ResourceManagerImpl<Test, HashMapStorage, CommonResPolicy, MultiThreadModel> TestManagerImpl;

TestManagerImpl tm;

void func(int x)
{
	for(int i = 0; i < 1000000; ++i)
	{
		HTest h(tm.GetResource(_T("Hello"), 5));
		HTest h2 = h;
		HTest h3(tm.GetResource(_T("Hello2"), 5));
		h2 = h3;
		h3 = h;
		h = h2;
		if(i % 100000 == 0)
		{
			printf("%s%d%s%d%s", "thread ", x, " running ", i/100000, "0%\r\n"); 
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	//tm.Initialize();
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
	thread t1(boost::bind(func,1));
	thread t2(boost::bind(func,2));
	thread t3(boost::bind(func,3));
	t1.join();
	t2.join();
	t3.join();
	}
	system("pause");
	return 0;
}