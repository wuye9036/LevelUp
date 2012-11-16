#pragma once

class CTestListView : public CWindowImpl<CTestListView, CListViewCtrl>
{
public:
	DECLARE_WND_SUPERCLASS(NULL, CListViewCtrl::GetWndClassName())

	BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_MSG_MAP(CTestListView)
	END_MSG_MAP()
};
