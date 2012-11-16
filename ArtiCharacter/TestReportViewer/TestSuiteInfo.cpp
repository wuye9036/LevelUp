#include "StdAfx.h"
#include "TestSuiteInfo.h"
#include <tinyxml.h>

bool TestMethodInfo::LoadFromXMLNode(TiXmlElement* pMethodElem){
	int tmpint;
	toTString2(m_testMethodName, pMethodElem->Attribute("name"));

	pMethodElem->QueryIntAttribute("totalItemCount", &tmpint);
	m_testItemCount = uint32(tmpint);

	pMethodElem->QueryIntAttribute("passedItemCount", &tmpint);
	m_passedItemCount = uint32(tmpint);

	pMethodElem->QueryIntAttribute("failedItemCount", &tmpint);
	m_failedItemCount = uint32(tmpint);

	m_testItems.resize(m_testItemCount);
	size_t iItem = 0;

	//读取所有的测试项目数据
	TiXmlHandle methodHandle(pMethodElem);
	TiXmlElement* pElem = methodHandle.FirstChildElement("TEST").ToElement();
	for(pElem; pElem; pElem = pElem->NextSiblingElement("TEST")){
		TiXmlHandle itemHandle(pElem);
		m_testItems[iItem].content = itemHandle.FirstChildElement("CONTENT").ToElement()->GetText();
		m_testItems[iItem].isPassed = (strcmp(itemHandle.FirstChildElement("ISPASS").ToElement()->GetText(), "True") == 0);
	}
	
	return true;
}

uint32 TestMethodInfo::GetItemCount(byte itemState){
	switch(itemState){
		case TEST_PASSED : return m_passedItemCount;
		case TEST_FAILED : return m_failedItemCount;
		case TEST_ALL : return m_testItemCount;
	}
	return 0;
}

bool	TestMethodInfo::IsPassed() {
	return m_passedItemCount == m_testItemCount;
}

const _tstring& TestMethodInfo::GetMethodName(){
	return m_testMethodName;
}

vector<TestItemInfo*> TestMethodInfo::GetItemList(byte itemState)
{
	vector<TestItemInfo*> tmp;
	switch(itemState){
		case TEST_PASSED : tmp.reserve(m_passedItemCount); break;
		case TEST_FAILED : tmp.reserve(m_failedItemCount); break;
		case TEST_ALL : tmp.reserve(m_testItemCount); break;
	}

	/*
	Tips! 依据isPassed，构造出一个caseState，与传入的caseState位运算，测试是否满足条件。
	*/
	byte bitgate[2] = {TEST_FAILED, TEST_PASSED};

	for(size_t i = 0; i < m_testItems.size(); ++i){
		if(((bitgate[m_testItems[i].isPassed ? 1 : 0]) & itemState) > 0){
			tmp.push_back(&m_testItems[i]);
		}
	}

	return tmp;       
}

bool TestCaseInfo::LoadFromXMLNode(TiXmlElement* pCaseElem)
{
	//获得属性
	int tmpint;
	toTString2(m_testCaseName, pCaseElem->Attribute("name"));

	pCaseElem->QueryIntAttribute("totalMethodCount", &tmpint);
	m_testMethodCount = uint32(tmpint);
	
	pCaseElem->QueryIntAttribute("passedMethodCount", &tmpint);
	m_passedMethodCount = uint32(tmpint);
	
	pCaseElem->QueryIntAttribute("failedMethodCount", &tmpint);
	m_failedMethodCount = uint32(tmpint);

	m_testMethods.resize(m_testMethodCount);
	size_t iMethod = 0;

	//读取所有的测试方法数据
	TiXmlHandle caseHandle(pCaseElem);
	TiXmlElement* pElem = caseHandle.FirstChildElement("TESTMETHOD").ToElement();
	for(pElem; pElem; pElem = pElem->NextSiblingElement("TESTMETHOD")){
		m_testMethods[iMethod++].LoadFromXMLNode(pElem);
	}

	return true;
}

uint32 TestCaseInfo::GetMethodCount(byte methodState){
	switch(methodState){
		case TEST_PASSED : return m_passedMethodCount;
		case TEST_FAILED : return m_failedMethodCount;
		case TEST_ALL : return m_testMethodCount;
	}
	return 0;
}

bool TestCaseInfo::IsPassed()
{
	return m_passedMethodCount == m_testMethodCount;
}

const _tstring& TestCaseInfo::GetCaseName(){
	return m_testCaseName;
}
vector<TestMethodInfo*> TestCaseInfo::GetMethodList(byte methodState){
	vector<TestMethodInfo*> tmp;
	switch(methodState){
		case TEST_PASSED : tmp.reserve(m_passedMethodCount); break;
		case TEST_FAILED : tmp.reserve(m_failedMethodCount); break;
		case TEST_ALL : tmp.reserve(m_testMethodCount); break;
	}

	/*
	Tips! 依据isPassed，构造出一个caseState，与传入的caseState位运算，测试是否满足条件。
	*/
	byte bitgate[2];
	bitgate[1] = TEST_PASSED;
	bitgate[0] = TEST_FAILED;

	for(size_t i = 0; i < m_testMethods.size(); ++i){
		if(((bitgate[m_testMethods[i].IsPassed() ? 1 : 0]) & methodState) > 0){
			tmp.push_back(&m_testMethods[i]);
		}
	}

	return tmp;       
}

TestSuiteInfo::TestSuiteInfo(void)
{
}

TestSuiteInfo::~TestSuiteInfo(void)
{
}

bool TestSuiteInfo::LoadFromXMLFile(const TCHAR* pfName)
{
	//读入文件
	m_xmlDoc.LoadFile(toAnsiString(pfName));

	//读取root并判断是否为XMLNode
	TiXmlHandle xmlHandle(&m_xmlDoc);
	TiXmlElement* pRoot = xmlHandle.FirstChildElement().ToElement();
	if(!pRoot || pRoot->ValueStr() != string("TESTSUITE")){
		return false;
	}

	//如果文件确实是测试报表文件
	TiXmlHandle root(pRoot);

	//读取测试套件的属性
	toTString2(m_testSuiteName, pRoot->Attribute("name"));
	
	//遍历每一个TestCase
	TiXmlElement* pElem = pRoot->FirstChildElement("TESTCASE");
	for(pElem; pElem; pElem = pElem->NextSiblingElement("TESTCASE"))
	{
		m_testCaseInfos.resize(++m_testCaseCount);
		m_testCaseInfos.back().LoadFromXMLNode(pElem);
		if(m_testCaseInfos.back().IsPassed()){
			++m_passedCaseCount;
		} else {
			++m_failedCaseCount;
		}
	}

	return true;
}

uint32 TestSuiteInfo::GetTestCaseCount(byte caseState){
	switch(caseState){
		case TEST_PASSED : return m_passedCaseCount;
		case TEST_FAILED : return m_failedCaseCount;
		case TEST_ALL : return m_testCaseCount;
	}
	return 0;
}

vector<TestCaseInfo*> TestSuiteInfo::GetTestCaseList(byte caseState){
	vector<TestCaseInfo*> tmp;
	switch(caseState){
		case TEST_PASSED : tmp.reserve(m_passedCaseCount); break;
		case TEST_FAILED : tmp.reserve(m_failedCaseCount); break;
		case TEST_ALL : tmp.reserve(m_testCaseCount); break;
	}

	/*
	Tips! 依据isPassed，构造出一个caseState，与传入的caseState位运算，测试是否满足条件。
	*/
	byte bitgate[2];
	bitgate[1] = TEST_PASSED;
	bitgate[0] = TEST_FAILED;

	for(size_t i = 0; i < m_testCaseInfos.size(); ++i){
		if(((bitgate[m_testCaseInfos[i].IsPassed() ? 1 : 0]) & caseState) > 0){
			tmp.push_back(&m_testCaseInfos[i]);
		}
	}

	return vector<TestCaseInfo*>(tmp);       
}

const _tstring& TestSuiteInfo::GetSuiteName(){
	return m_testSuiteName;
}

bool TestSuiteInfo::IsPassed(){
	return m_passedCaseCount == m_testCaseCount;
}