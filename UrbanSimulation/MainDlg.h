// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "UrbanSimulator.h"
#include <atlctrls.h>
#include "resource.h"
#include <atlmisc.h>

class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
		public CMessageFilter, public CIdleHandler, 
		public CWinDataExchange<CMainDlg>
{
public:
	UrbanSimulator		m_us;
	CProgressBarCtrl	m_pbc;
	TCHAR				m_fldStr[260];
	bool				m_flag;
	enum { IDD = IDD_URBANSIMDLG };

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return CWindow::IsDialogMessage(pMsg);
	}

	virtual BOOL OnIdle()
	{
		m_pbc.SetPos(int(m_us.GetPercentage() * 1000));
		if (m_flag && m_us.IsDone())
		{
			ENDSTATE es = m_us.GetEndState();
			switch(es){
				case ABORT : 
					MessageBox("中断！");
					break;
				case UNSHORTEQUAL : 
					MessageBox("短期不均衡！");
					break;
				case UNLONGEQUAL : 
					MessageBox("长期不均衡！");
					break;
				case OK :
					MessageBox("执行结束！");
			}
			m_flag = false;
		}
		PostMessage(WM_PAINT);
		return FALSE;
	}

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_ID_HANDLER(IDC_CHOOSEDIRBTN, OnChooseDir)
	END_MSG_MAP()

	BEGIN_DDX_MAP(CMainDlg)
		DDX_INT(IDC_GRIDSTEPEDIT, m_us.m_grdstep)
		DDX_FLOAT(IDC_TCEDIT,	m_us.m_tc)
		DDX_FLOAT(IDC_W0EDIT,	m_us.m_w0)
		DDX_FLOAT(IDC_PHIEDIT,	m_us.m_phi)
		DDX_FLOAT(IDC_DELTAEDIT,m_us.m_delta)
		DDX_FLOAT(IDC_RHOEDIT,	m_us.m_rho)
		DDX_FLOAT(IDC_SPEDIT,	m_us.m_sp)
		DDX_FLOAT(IDC_GAMMAEDIT,m_us.m_gamma)
		DDX_FLOAT(IDC_BETAEDIT,	m_us.m_beta)
		DDX_FLOAT(IDC_ALPHAEDIT,m_us.m_alpha)
		DDX_FLOAT(IDC_LEDIT,	m_us.m_L)
		DDX_FLOAT(IDC_SIGMAEDIT,m_us.m_sigma)
		DDX_INT(IDC_SITEDIT,	m_us.m_shortit)
		DDX_INT(IDC_LITEDIT,	m_us.m_longit)
		DDX_TEXT(IDC_DIREDIT,	m_fldStr)
	END_DDX_MAP()
// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// center the dialog on the screen
		CenterWindow();

		// set icons
		HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
		SetIcon(hIcon, TRUE);
		HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
		SetIcon(hIconSmall, FALSE);

		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);

		UIAddChildWindowContainer(m_hWnd);
		
		m_us.Init();
		m_fldStr[0] = _T('\0');
		DoDataExchange(FALSE);
		m_pbc.Attach(GetDlgItem(IDC_PERCENTAGEPROGRESS));
		m_pbc.SetRange(0, 1000);
		m_pbc.SetPos(0);
		
		return TRUE;
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}

	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		DoDataExchange(TRUE);
		//m_us.m_folder = m_fldStr;
		m_flag = true;
		m_us.Calc();
		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CloseDialog(wID);
		return 0;
	}

	void CloseDialog(int nVal)
	{
		DestroyWindow();
		::PostQuitMessage(nVal);
	}

	LRESULT OnChooseDir(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CFolderDialog m_fldDlg;
		if(m_fldDlg.DoModal())
		{
			m_us.m_folder = m_fldDlg.m_szFolderPath;
		}
		_tcscpy(m_fldStr, m_fldDlg.m_szFolderPath);
		DoDataExchange(FALSE, IDC_DIREDIT);
		return 0;
	}
};
