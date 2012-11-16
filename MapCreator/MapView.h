//用于绘制将高度图绘制到窗口上

#pragma once
#include "resource.h"
#include <atlgdi.h>
#include "MapEditor.h"
#include <Gdiplus.h>

using namespace Gdiplus;

class CMapView : public CDialogImpl<CMapView>
{
protected:
	//位图类，用于存放位图
	Bitmap* m_pbmp;
	//位图信息
	BITMAPINFO m_bi;
	//位图像素指针
	BYTE*	m_pBitmapPixels;
	DWORD	m_viewMode;

	RECT	m_curRect;
public:
	enum {IDD = IDD_MAPVIEW};

	CMapView() : m_viewMode(ID_VIEW_FILL), m_pbmp(NULL), m_pBitmapPixels(NULL)
	{
		memset(&m_curRect, 0, sizeof(RECT));
	}
	~CMapView()
	{
		delete m_pbmp;
	}
	BOOL PreTranslateMessage(MSG* pMsg)
	{
		return CWindow::IsDialogMessage(pMsg);
	}

	BEGIN_MSG_MAP(CMapView)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_SIZE, OnResize)
		MESSAGE_HANDLER(WM_VSCROLL, OnVScroll)
		MESSAGE_HANDLER(WM_HSCROLL, OnHScroll)
	END_MSG_MAP()

	LRESULT OnResize(UINT, WPARAM, LPARAM, BOOL&)
	{
		UpdateScrollBar();

		PostMessage(WM_PAINT);
		return 0;
	}

	LRESULT OnPaint(UINT, WPARAM, LPARAM, BOOL&)
	{
		CPaintDC dc(m_hWnd);
		MapInfo mi;
		g_mapEditor.GetMapInfo(&mi);

		//如果没有地图，则也释放位图，并返回
		if(!g_mapEditor.IsHasData())
		{
			if(m_pbmp)
			{
				delete m_pbmp;
				m_pbmp = NULL;
			}
			return 1;
		}
		
		//如果地图发生了改变，也删掉位图，以便重新开辟
		if(g_mapEditor.IsMapSizeChanged(true))
		{
			if(m_pbmp)
			{
				delete m_pbmp;
				m_pbmp = NULL;
			}
		}

		if(g_mapEditor.IsHasData() && m_pbmp == NULL)
		{
			//如果数据存在，但是位图不存在，则创建一个新位图
			g_mapEditor.GetMapInfo(&mi);
			//创建一个新位图
			CreateBitmap();
		}

		if(!m_pbmp) return E_FAIL;
		
		//未绘制过的话，则重新设置位图
		if(!g_mapEditor.IsDrawed(true))
		{
			SetBitmap();
		}

		//首先是清理窗口
		//将位图显示到窗口上
		if(m_viewMode == ID_VIEW_FILL)
		{
			PaintBitmapFill(mi.width, mi.height);
		}
		else
		{
			PaintBitmapOriginSize(mi.width, mi.height);
		}

		return 1;
	}

	BOOL SetViewMode(DWORD mode);
	DWORD GetViewMode();

	//匹配
	void PaintBitmapFill(int mapWidth, int mapHeight);
	void PaintBitmapOriginSize(int mapWidth, int mapHeight);

	void ClearBkg(Graphics* pg, RectF& dirtyRF);

	
	void SetBitmap();		//设置位图
	void CreateBitmap(void);//创建位图

	void UpdateScrollBar(LPSCROLLINFO h = NULL, LPSCROLLINFO v = NULL);
	//响应滚动条消息
	LRESULT OnVScroll(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnHScroll(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};