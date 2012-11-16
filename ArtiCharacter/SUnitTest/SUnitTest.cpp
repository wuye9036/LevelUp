// SUnitTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SUnitTestConsole.h"

int foo(int x){
	return 2*x;
}

BEGIN_METHOD(TestFoo)
	TEST_TRUE_PASS(4 == foo(2))
END_METHOD()

BEGIN_TESTCASE(tcExample)
	ADD_METHOD(TestFoo)
END_TESTCASE()

BEGIN_TESTSUITE(tsExample)
	ADD_CASE(tcExample)
END_TESTSUITE()

int _tmain(int argc, _TCHAR* argv[])
{
	EXECUTE_TEST(tsExample);

	tcExample.PrintReportToConsole();

	MAKE_AND_SAVE_REPORT(tsExample, "test.xml")

	system("pause");
	return 0;
}

