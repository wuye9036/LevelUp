// MapCreatorView.h : interface of the CMapCreatorView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "resource.h"
#include <atlwin.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlddx.h>
#include <atlframe.h>
#include <atlapp.h>
#include "MapEditor.h"

class CMapEditorView :	public CDialogImpl<CMapEditorView>, 
						public CWinDataExchange<CMapEditorView>
{
protected:
	//地图宽度
	int m_mapWidth;
	int m_mapHeight;

	CEdit m_mapWidthEdit;
	CEdit m_mapHeightEdit;

	CButton m_submitBtn;
	CButton m_initBtn;

	CComboBox m_chooseInitMethodCombo;

public:
	enum { IDD = IDD_MAPEDITORVIEW };

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		m_initBtn.EnableWindow(g_mapEditor.IsHasData());
		::EnableWindow(GetDlgItem(IDC_FIRFILTER), g_mapEditor.IsHasData());
		DoDataExchange(true);
		return CWindow::IsDialogMessage(pMsg);
	}

	BEGIN_DDX_MAP(CMapEditorView)
		DDX_INT(IDC_MAPW, m_mapWidth)
		DDX_INT(IDC_MAPH, m_mapHeight)
	END_DDX_MAP()

	BEGIN_MSG_MAP(CMapEditorView)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDC_BTNSUBMIT, BN_CLICKED, OnMapCreationSubmit)
		COMMAND_HANDLER(IDC_INITMAPBTN, BN_CLICKED, OnInitMap)
		COMMAND_HANDLER(IDC_FIRFILTER, BN_CLICKED, OnFIRFilter)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

//初始化对话框
LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

//响应提交创建的消息，并创建地图。
LRESULT OnMapCreationSubmit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

//响应文件打开消息，打开文件
LRESULT OnFileOpen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

//响应文件保存消息，保存文件
LRESULT OnFileSave(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

//响应另存为消息，另存文件
LRESULT OnFileSaveAs(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

//响应创建新文件消息，准备创建新的地图
LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

//响应初始化地图消息。
LRESULT OnInitMap(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

//初始化Combo控件，提供地图初始化选项
void InitCombo();

//获取地图信息，并显示
LRESULT GetMapInfoAndShow();

//判断是否可以更改地图信息。（不是指Modify，而是指变更地图。）
BOOL IsMapCanChange();
LRESULT OnFIRFilter(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
