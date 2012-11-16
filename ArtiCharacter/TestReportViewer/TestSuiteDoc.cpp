#include "StdAfx.h"
#include "TestSuiteDoc.h"

TestSuiteDoc::TestSuiteDoc(void)
{
}

TestSuiteDoc::~TestSuiteDoc(void)
{
}

bool TestSuiteDoc::OpenReportFile(const TCHAR* pfStr)
{
	return false;
}

bool TestSuiteDoc::OpenReportWorkspace(const TCHAR* pWs)
{
	return false;
}

StringList TestSuiteDoc::GetListColumns(void)
{
	return StringList();
}

bool TestSuiteDoc::SetCurrentTreeNode(const TCHAR* pTreeDir)
{
	return false;
}
