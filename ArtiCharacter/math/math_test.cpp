// math.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Vector.h"
#include "../SUnitTest/SUnitTestConsole.h"

BEGIN_METHOD(normalize_test)
	vec3 v(1.0f, 2.0f, 3.0f);
	v = normalize(v);
	TEST_TRUE_PASS(length(v) == 1.0f);
	TEST_IN_DELTA_PASS(length(v), 1.0f, 0.001f);
END_METHOD()

BEGIN_TESTCASE(vec_test_case)
	ADD_METHOD(normalize_test)
END_TESTCASE()

BEGIN_TESTSUITE(math_test_suite)
	ADD_CASE(vec_test_case)
END_TESTSUITE()

int _tmain(int argc, _TCHAR* argv[])
{
	EXECUTE_TEST(math_test_suite);
	MAKE_AND_SAVE_REPORT(math_test_suite, "math_test_report.xml");
	
	return 0;
}

