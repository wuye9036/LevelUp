// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "MapEditorView.h"
#include "MapView.h"
#include "aboutdlg.h"
#include "stdafx.h"
#include <atlwin.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlddx.h>
#include <atlframe.h>
#include <atlapp.h>

class CMainFrame : public CFrameWindowImpl<CMainFrame>, public CUpdateUI<CMainFrame>,
		public CMessageFilter, public CIdleHandler
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	CSplitterWindow m_spWnd;

	CMapEditorView m_mapEditorView;

	CMapView m_mapView;

	CCommandBarCtrl m_CmdBar;

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		if(CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
		{
			return TRUE;
		}
		if(m_mapEditorView.PreTranslateMessage(pMsg))
		{
			return TRUE;
		}
		if(m_mapView.PreTranslateMessage(pMsg))
		{
			return TRUE;
		}
		return FALSE;
	}

	virtual BOOL OnIdle()
	{
		if(g_mapEditor.IsHasData() && !g_mapEditor.IsDrawed(false))
		{
			m_mapView.PostMessage(WM_PAINT);
		}

		//根据地图存在的情况设置Save菜单项
		if(g_mapEditor.IsHasData())
		{
			UIEnable(ID_FILE_SAVE, true);
			UIEnable(ID_FILE_SAVE_AS, true);
			UIEnable(ID_VIEW_FILL, true);
			UIEnable(ID_VIEW_NOSCALE, true);
			
			UISetCheck(ID_VIEW_FILL, FALSE);
			UISetCheck(ID_VIEW_NOSCALE, FALSE);
			UISetCheck(m_mapView.GetViewMode(), TRUE);
		}
		else
		{
			UIEnable(ID_FILE_SAVE, false);
			UIEnable(ID_FILE_SAVE_AS, false);
			UIEnable(ID_VIEW_FILL, false);
			UIEnable(ID_VIEW_NOSCALE, false);
		}

		//根据更改情况设置标题
		if(g_mapEditor.IsModified())
		{
			SetWindowText(_T("MapEditor*"));
		}
		else
		{
			SetWindowText(_T("MapEditor"));
		}

		UIUpdateToolBar();

		return FALSE;
	}

	BEGIN_UPDATE_UI_MAP(CMainFrame)
		UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_FILE_SAVE_AS, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_FILE_SAVE, UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_VIEW_FILL, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_NOSCALE, UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
		COMMAND_ID_HANDLER(ID_VIEW_TOOLBAR, OnViewToolBar)
		COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		//响应菜单消息，并转发
		COMMAND_ID_HANDLER(ID_FILE_OPEN, m_mapEditorView.OnFileOpen)
		COMMAND_ID_HANDLER(ID_FILE_SAVE, m_mapEditorView.OnFileSave)
		COMMAND_ID_HANDLER(ID_FILE_SAVE_AS, m_mapEditorView.OnFileSaveAs)
		COMMAND_ID_HANDLER(ID_FILE_NEW, m_mapEditorView.OnFileNew)
		//设置填充模式菜单
		COMMAND_ID_HANDLER(ID_VIEW_FILL, OnFill);
		COMMAND_ID_HANDLER(ID_VIEW_NOSCALE, OnNoScale);

		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// create command bar window
		HWND hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
		// attach menu
		m_CmdBar.AttachMenu(GetMenu());
		// load command bar images
		m_CmdBar.LoadImages(IDR_MAINFRAME);
		// remove old menu
		SetMenu(NULL);

		HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

		CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
		AddSimpleReBarBand(hWndCmdBar);
		AddSimpleReBarBand(hWndToolBar, NULL, TRUE);

		CreateSimpleStatusBar();

		//设置分隔栏窗口
		m_hWndClient = m_spWnd.Create(m_hWnd);
		m_mapEditorView.Create(m_spWnd);
		m_mapView.Create(m_spWnd);
		m_spWnd.SetSplitterPanes(m_mapEditorView, m_mapView);
		UpdateLayout();
		m_spWnd.SetSplitterPos(200);

		//分隔栏设置结束
	
		UIAddToolBar(hWndToolBar);
		UISetCheck(ID_VIEW_TOOLBAR, 1);
		UISetCheck(ID_VIEW_STATUS_BAR, 1);

		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);

		return 0;
	}

	LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		PostMessage(WM_CLOSE);
		return 0;
	}

	LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		static BOOL bVisible = TRUE;	// initially visible
		bVisible = !bVisible;
		CReBarCtrl rebar = m_hWndToolBar;
		int nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);	// toolbar is 2nd added band
		rebar.ShowBand(nBandIndex, bVisible);
		UISetCheck(ID_VIEW_TOOLBAR, bVisible);
		UpdateLayout();
		return 0;
	}

	LRESULT OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		BOOL bVisible = !::IsWindowVisible(m_hWndStatusBar);
		::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
		UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
		UpdateLayout();
		return 0;
	}

	LRESULT OnFill(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		m_mapView.SetViewMode(ID_VIEW_FILL);
		UISetCheck(ID_VIEW_FILL, TRUE);
		UISetCheck(ID_VIEW_NOSCALE, FALSE);
		return 0;
	}

	LRESULT OnNoScale(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		m_mapView.SetViewMode(ID_VIEW_NOSCALE);
		UISetCheck(ID_VIEW_FILL, FALSE);
		UISetCheck(ID_VIEW_NOSCALE, TRUE);
		return 0;
	}
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}
};
