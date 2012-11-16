// PropertyUtility.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TestClass.h"
#include <iostream>

#define TEST_TRUE(exp) if(exp){cout << #exp << "...................succeed!" << endl;} else {cout << #exp << "...................failed!" << endl; succeed_all = false;}
#define TEST_DECL(str) cout << #str << endl;

int _tmain(int argc, _TCHAR* argv[])
{
	bool succeed_all = true;
	//测试用例所需要的变量
	TestBase tb1;
	TestBase tb2;
	TestDerived td;

	TestBase* ptb;
	TestDerived* ptd;

	int src1 = 1;
	int src2 = 2;
	int src3 = 3;
	int dest1 = -1;
	int dest2 = -1;
	int dest3 = -1;

	//常规测试
	tb1.Set(_T("testint"), src1);
	tb1.Get(_T("testint"), dest1);

	TEST_DECL(基本存取测试);
	TEST_TRUE(dest1 == src1);  
	TEST_TRUE(tb1.x == src1);

	tb2.Set(_T("testint"), src2);
	tb2.Get(_T("testint"), dest2);
	tb1.Get(_T("testint"), dest1);

	TEST_DECL(交叉存取测试);
	TEST_TRUE(dest2 == src2);
	TEST_TRUE(tb2.x == src2);
	TEST_TRUE(dest1 == src1);
	TEST_TRUE(tb1.x == src1);

	td.Set(_T("testint3"), src3);
	td.Get(_T("testint3"), dest3);

	TEST_DECL(继承类元素存取测试);
	TEST_TRUE(src3 == dest3);
	TEST_TRUE(td.xx == src3);

	src1 = 4; dest1 = -4;
	td.Set(_T("testint"), src1);
	td.Get(_T("testint"), dest1);

	TEST_DECL(继承类的基类元素存取测试);
	TEST_TRUE(src1 == dest1);
	TEST_TRUE(td.x == src1);

	src1 = 5; dest1 = -5;
	ptb = &td;
	ptb->Set(_T("testint"), src1);
	ptb->Get(_T("testint"), dest1);
	

	TEST_DECL(多态情况下继承类的基类元素存取测试);
	TEST_TRUE(src1 == dest1);
	TEST_TRUE(td.x == src1);

	src1 = 6; dest1 = -6;
	ptb->Set(_T("testint3"), src1);
	ptb->Get(_T("testint3"), dest1);
	

	TEST_DECL(多态情况下继承类的元素存取测试);
	TEST_TRUE(src1 == dest1);
	TEST_TRUE(td.xx == src1);

	TEST_DECL(继承类属性表测试);
	vector<const TCHAR*> _prop_names = ptb->GetPropertySet()->EnumProperties();
	for(size_t i = 0; i < _prop_names.size(); ++i){
	wcout << _prop_names[i] << endl;
	}

	TEST_DECL(基类属性表测试);
	vector<const TCHAR*> _prop_names2 = tb1.GetPropertySet()->EnumProperties();
	for(size_t i = 0; i < _prop_names2.size(); ++i){
	wcout << _prop_names2[i] << endl;
	}

	TEST_TRUE(succeed_all);
	/*
	TEST_DECL(附加测试，用于编译器匹配);
	TEST_DECL(测试多态指针情况);

	ptb = &td;
	ptd = &td;
	
	TEST_TRUE(ptb == ptd);
	TEST_TRUE(static_cast<void*>(ptb) == static_cast<void*>(ptd));

	ptb = &tb1;
	TestBase* ptb2 = &tb2;
	TEST_TRUE(((char*)&(ptb->x) - (char*)(ptb)) ==  ((char*)&(ptb2->x) - (char*)ptb2 ));
	unsigned int offset = (char*)&(ptb->x) - (char*)(ptb);
	TEST_TRUE(&(tb1.x) == (int*)((char*)(&tb1) + offset));
	*/
	system("pause");
	return 0;
}

