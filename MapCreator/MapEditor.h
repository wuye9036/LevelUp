#pragma once
#include "atlmisc.h"

#define SAFE_DEL_ARRAY(p) if(p){delete[] (p); (p) = NULL;}

struct MapInfo
{
	float* pMapData;
	DWORD width;
	DWORD height;
	DWORD byteperdot;
};

class MapEditor
{
protected:
	CString m_str;
	bool m_isModified;
	bool m_isMapSizeChanged;
	bool m_isDrawed;

public:
	MapEditor(void);
	~MapEditor(void);

	void SetFileName(LPCTSTR fname);
	LPCTSTR GetFileName();

	bool CreateMapData(int width, int height); 
	void GetMapInfo(MapInfo* pmi); 

	bool IsDrawed(bool isProcessed);
	bool IsModified();
	bool IsAttachedFile();
	bool IsHasData();
	bool IsMapSizeChanged(bool isProcessed);

	bool SaveToFile();
	bool LoadFromFile();

	void InitMapByRandomHeight();
	void Filter(int nFilteTimes, float filterPar);
	void MakePlasma(float rough);
	void MakeFault(int iterations,int maxDelta,int minDelta,int iterationsPerFilter,float filter);

protected:
	//保存地图数据
	float* m_pMapData;
	//地图宽，高
	DWORD m_width;
	DWORD m_height;
};

extern MapEditor g_mapEditor;