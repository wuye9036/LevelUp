/**
 * 提供了一个源码级别的简易单元测试工具,提供一个简单的测试报告。
 * 
 * Copyright (c) 2007 by 空明流转 
 * Email: wuye9036@gmail.com
 * 保留所有权利
 */
#pragma once
#define TIXML_USE_STL

#include <vector>
#include <string>
#include <tinyxml.h>

using namespace std;

enum TEST_STATE {
	UNKNOWN,
	PASS,
	FAILURE
};

/**单Assert的测试结果*/
struct SingleTestReport{
	string	content;	///< 单个测试项(表达式)的内容
	bool	isPass;		///< 测试结果

	SingleTestReport(const string& content, bool isPass);
	SingleTestReport(const SingleTestReport& rhs) ;

	const SingleTestReport& operator = (const SingleTestReport& rhs);
};

/**单个测试方法的结果*/
struct TestMethodReport{
	vector<SingleTestReport> testItemReports;	///< 测试方法中所有的测试项结果列表
	string	testMethodName;								///< 测试方法名称
	int		testItemCount;									///< 测试项目数
	int		passedItemCount;								///< 通过项目数
	int		failedItemCount;									///< 失败项目数
	bool	isPass;												///< 测试方法是否通过(只有所有的测试项通过才能算作测试方法通过)

	TestMethodReport();
	TestMethodReport(const TestMethodReport& rhs);
	const TestMethodReport& operator = (const TestMethodReport& rhs);
};

/** 用于执行测试方法的函数,收集测试数据 */
typedef bool (*PTestMethodFunc)(TestMethodReport*);

/** 测试用例,包含多个测试方法 */
class STestCase
{
	string m_testCaseName;												///< 测试用例名称

	vector<PTestMethodFunc>	m_testMethodList;				///< 测试方法列表
	vector<TestMethodReport>	m_testMethodReports;			///< 测试用例中全部测试方法结果报告

	int m_passedTestMethodCount;									///< 通过的测试用例数
	int m_failedTestMethodCount;										///< 失败的测试用例数

public:
	STestCase(const string& caseName);

	void AddMethod(PTestMethodFunc pf);
	void ExecuteTest();
	void PrintReportToConsole();
	void SaveTestReport(const string& logf);

	/** 保存为XML节点 */
#ifdef TINYXML_INCLUDED
	void SaveTestReport(TiXmlNode* pNode);
#endif
};

/** 测试套件，包含多个测试用例 */
class STestSuite
{
	vector<STestCase*> m_testCaseList;		///< 测试用例列表
	
	string m_testSuiteName;						///< 测试套件名称

#ifdef TINYXML_INCLUDED
	TiXmlDocument* m_pXmlDoc;				///< XML文档，用于保存测试结果
#endif

public:
	STestSuite(const string& suiteName);

	void AddTestCase(STestCase* pTestCase);
	void ExecuteTest();
	
#ifdef TINYXML_INCLUDED
	/** 以XML格式保存测试报告 */
	void MakeXMLDocument();
	void SaveTestReportXML(const string& fname);
#endif
};
#define CONTACT(s1, s2) s1##s2
#define CONTACT_S(s1, s2) CONTACT(s1, s2)
#define AUTO_GEN(s1) CONTACT_S(s1, __COUNTER__)

/**开始测试用例*/
#define BEGIN_TESTCASE(tcName) \
	STestCase tcName(#tcName); \
	class tcName##Setting {\
		STestCase* pTestCase;\
	public:\
			   tcName##Setting() : pTestCase(&tcName){

/** 向测试用例中添加测试函数 */
#define ADD_METHOD(method_name) \
	pTestCase->AddMethod(&method_name);

/**结束测试用例*/
#define END_TESTCASE() \
		} \
	} AUTO_GEN(TestCase); 

/** 测试方法声明开始。测试方法中可以内嵌常规语句。但是测试只能通过宏完成 */
#define BEGIN_METHOD(method_name)  \
	bool method_name(TestMethodReport* report) { report->testMethodName = #method_name;

/** 测试验证宏。expr是一个表达式。如果改表达式为真则表明测试通过, 否则测试不通过*/
#define TEST_TRUE_PASS(expr) \
	++(report->testItemCount);\
	report->testItemReports.push_back(SingleTestReport(#expr, false)); \
	if(expr) { report->testItemReports.back().isPass = true; ++(report->passedItemCount);} \
	else { ++(report->failedItemCount); }

#define TEST_IN_RANGE_PASS(expr, l, u) \
	++(report->testItemCount);\
	report->testItemReports.push_back(SingleTestReport(#expr ##"is between" #l "and" #u, false)); \
	if((expr) > (l) && (expr) < (u)) { report->testItemReports.back().isPass = true; ++(report->passedItemCount);} \
	else { ++(report->failedItemCount); }

#define TEST_IN_DELTA_PASS(expr, v, delta) \
	++(report->testItemCount);\
	report->testItemReports.push_back(SingleTestReport(#expr " is in " #v "|+/-|" #delta, false)); \
	if((expr) > (v)-(delta) && (expr) < (v)+(delta)) { report->testItemReports.back().isPass = true; ++(report->passedItemCount);} \
	else { ++(report->failedItemCount); }

#define TEST_TRUE_PASS_DESC(expr, desc) \
	++(report->testItemCount);\
	report->testItemReports.push_back(SingleTestReport(desc, false)); \
	if(expr) { report->testItemReports.back().isPass = true; ++(report->passedItemCount);} \
	else { ++(report->failedItemCount); }

/** 测试方法声明结束 */
#define END_METHOD() return report->isPass = (report->failedItemCount == 0);}

/** 执行测试 */
#define EXECUTE_TEST(testName) testName.ExecuteTest();

/** 开始定义测试套件 */
#define BEGIN_TESTSUITE(suiteName) \
	STestSuite suiteName(#suiteName);\
	class suiteName_##Setting {\
		STestSuite* pTestSuite;\
	public:\
		suiteName_##Setting() : pTestSuite(&suiteName) {

/** 添加测试用例 */
#define ADD_CASE(case_name) \
	pTestSuite->AddTestCase(&case_name);

/** 结束测试套件定义 */
#define END_TESTSUITE() \
		}\
	} AUTO_GEN(TestSuite);

/** 生成并保存记录（XML） */
#define MAKE_AND_SAVE_REPORT(suiteName, fname) \
	suiteName.MakeXMLDocument();\
	suiteName.SaveTestReportXML(fname);

