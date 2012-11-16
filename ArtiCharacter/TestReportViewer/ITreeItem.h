#pragma once

#include <platform/typedef.h>
#include <util/string.h>
#include <vector>
using namespace std;

typedef vector<const TCHAR*> StringList;

class TestSuiteWs;
class TestSuiteInfo;
class TestCaseInfo;
class TestMethodInfo;

class ITreeItem
{
public:
	virtual ~ITreeItem(void){};
	
	virtual bool Load(void* pData) = 0;
	virtual uint32 GetIcon() = 0;
	virtual const _tstring& GetLabel() = 0;
	virtual const vector<StringList>& GetListItems() = 0;
	virtual const StringList& GetListColumns() = 0;
	virtual const vector<ITreeItem*>& GetChilds() = 0;
	virtual bool IsPassed() = 0;
};

class TreeItemImpl : public ITreeItem{
protected:
	vector<ITreeItem*>	m_pTreeItems;
	vector<StringList>		m_listItems;
	StringList					m_columns;
	
	_tstring						m_label;
	uint32						m_icon;
	
	bool							m_isPassed;

public:
	virtual const vector<StringList> & GetListItems() {return m_listItems;}
	virtual const StringList& GetListColumns() {return m_columns;}
	virtual const _tstring& GetLabel() {return m_label;}
	virtual uint32 GetIcon() {return m_icon;}
	virtual const vector<ITreeItem*>& GetChilds(){return m_pTreeItems;}
	virtual bool IsPassed() {return m_isPassed;}
};

class MethodTreeItem : public TreeItemImpl{

	TestMethodInfo*				m_pMethod;

public:
	virtual bool Load(void* pData);
};

class CaseTreeItem : public TreeItemImpl{
	vector<MethodTreeItem>	m_methodItems;

	TestCaseInfo*						m_pCase;

public:
	virtual bool Load(void* pData);
};

class SuiteTreeItem : public TreeItemImpl{
	vector<CaseTreeItem>		m_caseItems;

	TestSuiteInfo*					m_pSuite;

public:
	virtual bool Load(void* pData);
};

class SuiteWsTreeItem : public TreeItemImpl{
	vector<SuiteWsTreeItem>	m_wsItems;
	vector<SuiteTreeItem>		m_suiteItems;
	
	TestSuiteWs*						m_pSuiteWs;

public:
	virtual bool Load(void* pData);
};

