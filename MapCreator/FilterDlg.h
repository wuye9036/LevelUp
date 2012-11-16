#pragma once
#include "resource.h"
#include "atldlgs.h"
#include "atlddx.h"
#include "TerrainMakerAlgo.h"
#include "MapEditor.h"

class CFilterDlg : public CDialogImpl<CFilterDlg>,
				   public CWinDataExchange<CFilterDlg>
{
protected:
	float m_filterPar;
	int m_nFilteTimes;

public:
	BOOL PreTranslateMessage(MSG* pMsg)
	{
		DoDataExchange(true);
		return CWindow::IsDialogMessage(pMsg);
	}

	BEGIN_DDX_MAP(CFilterDlg)
		DDX_FLOAT(IDC_FILTER, m_filterPar)
		DDX_INT(IDC_NFILTETIMES, m_nFilteTimes)
	END_DDX_MAP()

	BEGIN_MSG_MAP(CFilterDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	END_MSG_MAP()

	enum { IDD = IDD_FILTERDLG };

	LRESULT OnInitDialog(UINT, WPARAM, LPARAM, BOOL&)
	{
		m_filterPar = 0.5f;
		m_nFilteTimes = 1;

		DoDataExchange(false);
		return 0;
	}

	BOOL DoFilter()
	{
		if(DoModal() == IDOK)
		{
			g_mapEditor.Filter(m_nFilteTimes, m_filterPar);
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
