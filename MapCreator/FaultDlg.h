#pragma once
#include "resource.h"
#include "atldlgs.h"
#include "atlddx.h"
#include "TerrainMakerAlgo.h"
#include "MapEditor.h"

class CFaultDlg : public CDialogImpl<CFaultDlg>,
				   public CWinDataExchange<CFaultDlg>
{
protected:
	float m_filterPar;
	int	  m_nIter;
	int	  m_nFilterIter;
	int m_maxDelta;
	int m_minDelta;

public:
	BOOL PreTranslateMessage(MSG* pMsg)
	{
		DoDataExchange(true);
		return CWindow::IsDialogMessage(pMsg);
	}

	BEGIN_DDX_MAP(CFaultDlg)
		DDX_FLOAT(IDC_FILTER, m_filterPar)
		DDX_INT(IDC_NFILTERITER, m_nFilterIter)
		DDX_INT(IDC_NITER, m_nIter)
		DDX_INT(IDC_MAXDELTA, m_maxDelta)
		DDX_INT(IDC_MINDELTA, m_minDelta)
	END_DDX_MAP()

	BEGIN_MSG_MAP(CFaultDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	END_MSG_MAP()

	enum { IDD = IDD_FAULTDLG };

	LRESULT OnInitDialog(UINT, WPARAM, LPARAM, BOOL&)
	{
		m_filterPar = 0.5f;
		m_nIter = 8;
		m_nFilterIter = 1;
		m_maxDelta = 10;
		m_minDelta = 1;

		DoDataExchange(false);
		return 0;
	}

	BOOL DoFault()
	{
		if(DoModal() == IDOK)
		{
			g_mapEditor.MakeFault(m_nIter, m_maxDelta, m_minDelta, m_nFilterIter, m_filterPar);
			return TRUE;
		}
		return FALSE;
	}

	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		DoDataExchange(true);
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}
};
