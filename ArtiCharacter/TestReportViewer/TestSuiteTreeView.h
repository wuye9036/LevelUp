// TestReportViewerView.h : interface of the CTestReportViewerView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CTestSuiteTreeView : public CWindowImpl<CTestSuiteTreeView, CTreeViewCtrl>
{
public:
	DECLARE_WND_SUPERCLASS(NULL, CTreeViewCtrl::GetWndClassName())

	BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_MSG_MAP(CTestSuiteTreeView)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
};
