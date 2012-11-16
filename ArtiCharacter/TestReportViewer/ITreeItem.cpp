#include "StdAfx.h"
#include "ITreeItem.h"

bool SuiteWsTreeItem::Load(void* pData)
{
	TestSuiteWs* pWs = static_cast<TestSuiteWs*>(pData);
	if(!pWs) return false;


}

bool SuiteTreeItem::Load(void* pData)
{
	TestSuiteWs* pWs = static_cast<TestSuiteWs*>(pData);
	if(!pWs) return false;
}

bool CaseTreeItem::Load(void* pData)
{
	TestSuiteWs* pWs = static_cast<TestSuiteWs*>(pData);
	if(!pWs) return false;
}

bool MethodTreeItem::Load(void* pData)
{
	TestSuiteWs* pWs = static_cast<TestSuiteWs*>(pData);
	if(!pWs) return false;
}