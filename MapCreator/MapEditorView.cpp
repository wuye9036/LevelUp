#include "StdAfx.h"
#include "MapEditorView.h"
#include <atlframe.h>
#include ".\mapeditorview.h"
#include "FilterDlg.h"
#include "PlasmaDlg.h"
#include "FaultDlg.h"

LRESULT CMapEditorView::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_mapWidthEdit.Attach( GetDlgItem(IDC_MAPW) );
	m_mapHeightEdit.Attach( GetDlgItem(IDC_MAPH) );

	m_submitBtn.Attach( GetDlgItem(IDC_BTNSUBMIT) );
	m_initBtn.Attach( GetDlgItem(IDC_INITMAPBTN) );
	m_chooseInitMethodCombo.Attach( GetDlgItem(IDC_INITCHOOSE) );
	InitCombo();

	m_mapWidth = 0;
	m_mapHeight = 0;

	DoDataExchange(false);
	m_initBtn.EnableWindow(g_mapEditor.IsHasData());
	::EnableWindow(GetDlgItem(IDC_FIRFILTER), g_mapEditor.IsHasData());

	m_mapWidthEdit.SetReadOnly(true);
	m_mapHeightEdit.SetReadOnly(true);

	m_submitBtn.ShowWindow(false);
	return S_OK;
}

LRESULT CMapEditorView::OnMapCreationSubmit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(g_mapEditor.CreateMapData(m_mapWidth, m_mapHeight))
	{
		m_mapWidthEdit.SetReadOnly(true);
		m_mapHeightEdit.SetReadOnly(true);

		m_submitBtn.ShowWindow(0);
	}
	else
	{
		MessageBox(_T("创建失败！"), _T("警告"));
	}

	return S_OK;
}

LRESULT CMapEditorView::OnFileOpen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	//判断用户是否决定打开文件（有时候用户会先退回去）
	if(!IsMapCanChange())
	{
		return S_OK;
	}

	CFileDialog dlg(TRUE, _T("hmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("HeightFeild Map Files (*.hmp)\0*.hmp\0All Files (*.*)\0*.*\0"), m_hWnd);

	if(dlg.DoModal() == IDCANCEL)
	{
		return S_OK;
	}

	g_mapEditor.SetFileName(dlg.m_szFileName);
	if(g_mapEditor.LoadFromFile())
	{
		GetMapInfoAndShow();
		return S_OK;
	}

	MessageBox(_T("文件读取错误！"), _T("打开错误"));
	return S_OK;
}

LRESULT CMapEditorView::OnFileSave(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 在此添加命令处理程序代码
	if(!g_mapEditor.IsAttachedFile())
	{
		BOOL b;
		OnFileSaveAs(0, 0, NULL, b);
	}
	else
	{
		if(g_mapEditor.SaveToFile())
		{
			return S_OK;
		}

		MessageBox(_T("文件存储错误！"), _T("存储错误"));
	}
	return S_OK;
}

LRESULT CMapEditorView::OnFileSaveAs(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog dlg(FALSE, _T("hmp|txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("HeightFeild Map Files (*.hmp)\0*.hmp\0Text Files (*.txt)\0*.txt\0"), m_hWnd);

	// TODO: 在此添加命令处理程序代码
	if(dlg.DoModal() == IDCANCEL)
	{
		return S_OK;
	}

	g_mapEditor.SetFileName(dlg.m_szFileName);
	if(g_mapEditor.SaveToFile())
	{
		return S_OK;
	}

	MessageBox(_T("文件存储错误！"), _T("存储错误"));
	return S_OK;
	return 0;
}

LRESULT CMapEditorView::OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	//点击“新建”菜单时，首先判断是否有文件需要保存。
	if(!IsMapCanChange())
	{
		return S_OK;
	}

	//打开“提交新建”按钮，并给地图参数置初值，启用输入控件。
	m_mapWidth = 0;
	m_mapHeight = 0;
	DoDataExchange(false);

	m_mapWidthEdit.SetReadOnly(false);
	m_mapHeightEdit.SetReadOnly(false);

	m_submitBtn.ShowWindow(1);

	return 0;
}

LRESULT CMapEditorView::GetMapInfoAndShow()
{
	MapInfo mi;
	g_mapEditor.GetMapInfo(&mi);
	ATLASSERT(mi.pMapData);

	m_mapWidth = mi.width;
	m_mapHeight = mi.height;

	DoDataExchange(false);
	return S_OK;
}

BOOL CMapEditorView::IsMapCanChange()
{
	//判断文件是否被修改过，若被修改过，则提示保存。Open会根据返回的情况来判断是否打开文件选择对话框。
	if(g_mapEditor.IsHasData() && g_mapEditor.IsModified())
	{
		int rv = ::MessageBoxEx(m_hWnd, _T("文件已修改，是否保存？"), _T("保存文件"), MB_YESNOCANCEL, 0);
		if(rv == IDYES)
		{
			BOOL b;
			OnFileSave(0, 0, NULL, b);
		}
		else
		{
			if( rv == IDCANCEL) return FALSE;
		}
	}
	return TRUE;
}

LRESULT CMapEditorView::OnInitMap(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	//初始化地图。。。没这么简单咯。
	if(g_mapEditor.IsHasData())
	{
		CString str;
		int id = m_chooseInitMethodCombo.GetCurSel();
		if(id == CB_ERR)
		{
			return 0;
		}
		m_chooseInitMethodCombo.GetLBText(id, str);
		if(_tcscmp(str, _T("随机填充")) == 0)
		{
			g_mapEditor.InitMapByRandomHeight();
		}
		else if(_tcscmp(str, _T("中点置换")) == 0)
		{
			CPlasmaDlg pdlg;
			pdlg.DoPlasma();
		}
		else if(_tcscmp(str, _T("随机断层线")) == 0)
		{
			CFaultDlg cdlg;
			cdlg.DoFault();
		}
		else
		{
			ATLASSERT(true);
		}
	}
	return 0;
}

void CMapEditorView::InitCombo()
{
	m_chooseInitMethodCombo.AddString(_T("随机填充"));
	m_chooseInitMethodCombo.AddString(_T("随机断层线"));
	m_chooseInitMethodCombo.AddString(_T("中点置换"));
	//m_chooseInitMethodCombo.AddString(_T("等值填充"));
}

//点击了过滤按钮以后，使用低通滤波器过滤
LRESULT CMapEditorView::OnFIRFilter(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CFilterDlg fdlg;
	fdlg.DoFilter();
	return 0;
}
