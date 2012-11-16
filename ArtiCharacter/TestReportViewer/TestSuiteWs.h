#pragma once
#include "../../SUnitTest/SUnitTestConsole.h"
#include "../../platform/typedef.h"
#include "TestSuiteInfo.h"
#include <vector>

using namespace std;
/** TestSuite Workspace 
		TestSuite Workspace 是包含着TestSuite的文件夹。TestSuite Workspace 可以通过自包含来实现树状的层级关系。*/

const byte SUITE_PASSED = 0x1;
const byte SUITE_FAILED = 0x2; 
const byte SUITE_ALL = 0x3;

class TestSuiteInfo;

class TestSuiteWs
{
private:
	vector<TestSuiteWs> m_subTestSuiteWss;		///< 子测试包
	vector<TestSuiteInfo> m_subTestSuites;			///< 子测试套件

	_tstring	m_suiteWsName;
	bool		m_isAllPassed;										///< 如果该工作空间下的所有测试套件/工作空间均通过，则该测试包被判别通过
	uint32	m_passedTestSuiteCount;
	uint32	m_failedTestSuiteCount;

	uint32	m_passedTestSuiteWssCount;
	uint32	m_failedTestSuiteWssCount;

public:
	TestSuiteWs();
	~TestSuiteWs(void);

	/** 向测试套间空间中添加一个子空间 */
	bool Load(const TCHAR* wsName);

	/** 查询某类型的测试套件的数量。
		@param suiteState 指定测试套件的情况，返回符合情况的测试套件的数量。 
	*/
	uint32 GetSuiteCount(byte suiteState);
	uint32 GetSuiteWsCount(byte suiteWsState);
	const _tstring& GetSuiteWsName();
	bool IsPassed();
};