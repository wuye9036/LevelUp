#include "StdAfx.h"
#include "TestSuiteWs.h"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>

using namespace boost::filesystem;

TestSuiteWs::TestSuiteWs()
{
}

TestSuiteWs::~TestSuiteWs(void)
{
}

bool TestSuiteWs::Load(const TCHAR* pWsName){
	string path_str(toAnsiString(pWsName));
	path cur_path(path_str);

	if(!is_directory(cur_path)) return false;

	bool is_has_report = false;
	//遍历所有子目录
	for( directory_iterator sub_path_it(cur_path); sub_path_it != directory_iterator(); ++sub_path_it )
	{
		//如果是子目录则递归读取，如果所有的子目录/文件均无效，那么便忽略该路径
		if(is_directory(*sub_path_it)){
			push_null(m_subTestSuiteWss, 1);
			if(m_subTestSuiteWss.back().Load(toTString((*sub_path_it).native_file_string()).c_str())){
				is_has_report = true;
			} else {
				m_subTestSuiteWss.pop_back();
			}
		} else {
			//处理非目录的情况
			push_null(m_subTestSuites, 1);
			if(extension(*sub_path_it) == string("xml") && m_subTestSuites.back().LoadFromXMLFile(toTString((*sub_path_it).native_file_string()).c_str())) {
				is_has_report = true;
			} else {
				m_subTestSuites.pop_back();
			}
		}
	}

	//如果它的全部子目录均没有报表，则直接返回 false。
	if(!is_has_report) return false;
	
	//否则统计并初始化数据
	size_t i = 0;
	for( i = 0; i < m_subTestSuiteWss.size(); ++i ){
		m_subTestSuiteWss[i].IsPassed() ? ++m_passedTestSuiteWssCount : ++m_failedTestSuiteWssCount;
	}
	for( i = 0; i < m_subTestSuites.size(); ++i ){
		m_subTestSuites[i].IsPassed() ? ++m_passedTestSuiteCount : ++m_failedTestSuiteCount;
	}
	
	m_suiteWsName = toTString(cur_path.leaf());
	return true;
}

uint32 TestSuiteWs::GetSuiteCount(byte suiteState)
{
	switch(suiteState){
		case TEST_PASSED : return m_passedTestSuiteCount;
		case TEST_FAILED : return m_failedTestSuiteCount;
		case TEST_ALL : return m_subTestSuites.size();
	}
	return 0;
}

uint32 TestSuiteWs::GetSuiteWsCount(byte suiteState)
{
	switch(suiteState){
		case TEST_PASSED : return m_passedTestSuiteWssCount;
		case TEST_FAILED : return m_failedTestSuiteWssCount;
		case TEST_ALL : return m_subTestSuiteWss.size();
	}
	return 0;
}

bool TestSuiteWs::IsPassed()
{
	return m_passedTestSuiteCount == m_subTestSuites.size() &&
				m_passedTestSuiteWssCount == m_subTestSuiteWss.size();
}

const _tstring& TestSuiteWs::GetSuiteWsName(){
	return m_suiteWsName;
}