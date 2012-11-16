#pragma once
#include "resource.h"
#include "atldlgs.h"
#include "atlddx.h"
#include "TerrainMakerAlgo.h"
#include "MapEditor.h"

class CPlasmaDlg : public CDialogImpl<CPlasmaDlg>,
				   public CWinDataExchange<CPlasmaDlg>
{
protected:
	float m_rough;

public:
	BOOL PreTranslateMessage(MSG* pMsg)
	{
		DoDataExchange(true);
		return CWindow::IsDialogMessage(pMsg);
	}

	BEGIN_DDX_MAP(CPlasmaDlg)
		DDX_FLOAT(IDC_ROUGH, m_rough)
	END_DDX_MAP()

	BEGIN_MSG_MAP(CPlasmaDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	END_MSG_MAP()

	enum { IDD = IDD_PLASMADLG };

	LRESULT OnInitDialog(UINT, WPARAM, LPARAM, BOOL&)
	{
		m_rough = 0.5f;
		DoDataExchange(false);
		return 0;
	}

	BOOL DoPlasma()
	{
		if(DoModal() == IDOK)
		{
			ATLASSERT(g_mapEditor.IsHasData());
			g_mapEditor.MakePlasma(m_rough);
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