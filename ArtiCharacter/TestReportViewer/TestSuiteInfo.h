#pragma once

#include "../../platform/typedef.h"
#define TIXML_USE_STL
#include <tinyxml.h>
#include <util/string.h>
#include <vector>
#define TMPSTR_MAX_LEN 1024
using namespace std;

const byte TEST_PASSED = 0x1;
const byte TEST_FAILED = 0x2; 
const byte TEST_ALL = 0x3;

struct TestItemInfo{
	string		content;
	bool		isPassed;
};

class TestMethodInfo{
private:
	_tstring								m_testMethodName;

	vector<TestItemInfo>		m_testItems;
	uint32							m_testItemCount;
	uint32							m_passedItemCount;
	uint32							m_failedItemCount;

public:
	bool		LoadFromXMLNode(TiXmlElement* pMethodElem);
	uint32	GetItemCount(byte itemState);
	bool		IsPassed();
	const _tstring& GetMethodName();
	vector<TestItemInfo*> GetItemList(byte itemState);
};

class TestCaseInfo{
private:
	_tstring								m_testCaseName;

	vector<TestMethodInfo>		m_testMethods;
	uint32								m_testMethodCount;
	uint32								m_passedMethodCount;
	uint32								m_failedMethodCount;

public:
	bool		LoadFromXMLNode(TiXmlElement* pCaseElem);			///<	从XMLNode中读取信息
	uint32	GetMethodCount(byte methodState);						///<	获得测试通过的条目数量
	bool		IsPassed();
	const _tstring& GetCaseName();
	vector<TestMethodInfo*> GetMethodList(byte methodState);
};

/**
@class	TestSuiteInfo
@brief	测试套件信息。 
@date 1/29/2007
@author LightSky
@bug
@warning
*/
class TestSuiteInfo
{
	vector<TestCaseInfo>		m_testCaseInfos;
	TiXmlDocument				m_xmlDoc;
	
	_tstring							m_testSuiteName;
	uint32							m_testCaseCount;
	uint32							m_passedCaseCount;
	uint32							m_failedCaseCount;

public:
	TestSuiteInfo(void);
	~TestSuiteInfo(void);

	/** 
	@brief		从XML中读取测试套件的信息
	@date		1/29/2007
	@author		LightSky
	@param		pfName	测试套件的XML报告文件
	@return		如果解析成功则返回true
	@bug
	@warning
	*/
	bool LoadFromXMLFile(const TCHAR* pfName);
	uint32 GetTestCaseCount(byte caseState);
	vector<TestCaseInfo*> GetTestCaseList(byte caseState);
	const _tstring& GetSuiteName();
	bool IsPassed();
};
