// ViewerTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <util/string.h>
#include <SUnitTest/SUnitTestConsole.h>
#include <Tools\TestReportViewer\TestSuiteInfo.h>

BEGIN_METHOD(AnsiStringTest)
	string ansiString("TestString");
	wstring wideString(L"TestString");
	_tstring tString(_T("TestString"));

	TEST_TRUE_PASS(ansiString == toAnsiString(wideString));
	TEST_TRUE_PASS(ansiString == toAnsiString(ansiString));
	TEST_TRUE_PASS(ansiString == toAnsiString(tString));
END_METHOD()

BEGIN_METHOD(WideStringTest)
	string ansiString("TestString");
	wstring wideString(L"TestString");
	_tstring tString(_T("TestString"));

	TEST_TRUE_PASS(wideString == toWideString(wideString));
	TEST_TRUE_PASS(wideString == toWideString(ansiString));
	TEST_TRUE_PASS(wideString == toWideString(tString));
END_METHOD()

BEGIN_TESTCASE(StringTest)
	ADD_METHOD(AnsiStringTest)
	ADD_METHOD(WideStringTest)
END_TESTCASE()

TestSuiteInfo suiteInfo;

BEGIN_METHOD(suiteInfoLoadTest)
	suiteInfo.LoadFromXMLFile(_T("C:\\Test.xml"));
	TEST_TRUE_PASS(suiteInfo.GetTestCaseCount(TEST_ALL) == 2);
	_tstring suiteName(suiteInfo.GetSuiteName());
	_tstring refName(_T("ViewerTest"));
	TEST_TRUE_PASS(suiteName == refName);
END_METHOD()

BEGIN_METHOD(suiteTreeTest)
	/*	测试Suite是否正常 */
	vector<TestCaseInfo*> totalCases(suiteInfo.GetTestCaseList(TEST_ALL));
	vector<TestCaseInfo*> passedCases(suiteInfo.GetTestCaseList(TEST_PASSED));
	TEST_TRUE_PASS(totalCases.size() == suiteInfo.GetTestCaseCount(TEST_ALL));
	TEST_TRUE_PASS(passedCases.size() == suiteInfo.GetTestCaseCount(TEST_PASSED));

	/* 测试 case 是否正常 */
	TEST_TRUE_PASS(totalCases[0]->GetCaseName() == _tstring(_T("StringTest")));
	TEST_TRUE_PASS(totalCases[1]->GetCaseName() == _tstring(_T("SuiteInfoTest")));

END_METHOD()

BEGIN_TESTCASE(SuiteInfoTest)
	ADD_METHOD(suiteInfoLoadTest)
	ADD_METHOD(suiteTreeTest)
END_TESTCASE()

BEGIN_TESTSUITE(ViewerTest)
	ADD_CASE(StringTest)
	ADD_CASE(SuiteInfoTest)
END_TESTSUITE()

int _tmain(int argc, _TCHAR* argv[])
{
	EXECUTE_TEST(ViewerTest);
	MAKE_AND_SAVE_REPORT(ViewerTest, "ViewerTest.xml");
	return 0;
}

