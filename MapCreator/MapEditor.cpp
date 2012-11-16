#include "StdAfx.h"
#include ".\mapeditor.h"
#include "log2.h"
#include "atlcrack.h"
#include <cassert>
#include <gdiplus.h>
#include "TerrainMakerAlgo.h"

MapEditor g_mapEditor;

MapEditor::MapEditor(void) : m_str(LPCTSTR(NULL)), m_pMapData(NULL), m_isModified(false), m_isMapSizeChanged(false), m_isDrawed(true)
{
}

MapEditor::~MapEditor(void)
{
	SAFE_DEL_ARRAY(m_pMapData);
}

void MapEditor::SetFileName(LPCTSTR fname)
{
	m_str = fname;
}

LPCTSTR MapEditor::GetFileName()
{
	return m_str;
}

void MapEditor::GetMapInfo(MapInfo* pmi)
{
	assert(pmi);
	
	pmi->width = m_width;
	pmi->height = m_height;
	pmi->pMapData = m_pMapData;
}

bool MapEditor::CreateMapData(int width, int height)
{
	
	if(!(width > 2 && height > 2))
	{
		//return false;
	}
	//长宽必须是2的幂+1
	if( ((1 << log2le(width)) != (width - 1)) && 
		((1 << log2le(height)) != (height - 1)))
	{
		return false;
	}

	SAFE_DEL_ARRAY(m_pMapData);
	m_pMapData = new float[width * height];
	memset(m_pMapData, 0, sizeof(float) * width * height);
	
	m_width = width;
	m_height = height;

	m_isModified = true;
	m_isMapSizeChanged = true;
	m_isDrawed = false;
	return true;
}

bool MapEditor::SaveToFile()
{
	if ( _tcsstr(m_str, _T(".txt") ) != NULL ){
		FILE* f;
		f = _tfopen( LPCTSTR(m_str), _T("w"));
		if( !f ) return false;
		_ftprintf(f, _T("%s\n"), _T("RMCF"));
		_ftprintf(f, _T("%d %d\n"), m_width, m_height);
		for( int y = 0; y < m_height; ++y){
			for( int x = 0; x < m_width; ++x ){
				_ftprintf(f, _T("%f "), m_pMapData[y * m_width + x]);
			}
			_ftprintf(f, _T("\n"));
		}
		fclose(f);
	} else {
		FILE* f;
		f = _tfopen(LPCTSTR(m_str), L"wb");
		if(!f) return false;

		DWORD h = 'HMAP';
		fwrite(&h, sizeof(h), 1, f);
		fwrite(&m_width, sizeof(m_width), 1, f);
		fwrite(&m_height, sizeof(m_height), 1, f);
		fwrite(m_pMapData, sizeof(float), m_width * m_height, f);
		fclose(f);
	}

	m_isModified = false;
	return true;		
}

bool MapEditor::LoadFromFile()
{
	FILE* f;
	f = _tfopen(LPCTSTR(m_str), L"rb");
	if(!f) goto OnOpenError;

	DWORD h = 0;
	if(fread(&h, sizeof(h), 1, f) < 1 || h != 'HMAP') 
	{
		goto OnOpenError;
	}

	if(fread(&m_width, sizeof(m_width), 1, f) < 1) 
	{
		goto OnOpenError;
	}

	if(fread(&m_height, sizeof(m_height), 1, f) < 1)
	{
		goto OnOpenError;
	}
	
	if(!CreateMapData(m_width, m_height) || fread(m_pMapData, sizeof(float), m_width * m_height, f) < m_width * m_height)
	{
		goto OnOpenError;
	}
	
	m_isModified = false;
	m_isMapSizeChanged = true;
	m_isDrawed = false;
	fclose(f);
	return true;

OnOpenError:
	SAFE_DEL_ARRAY(m_pMapData);
	m_str = _T("\0");
	if(f) fclose(f);
	return false;
}

bool MapEditor::IsModified()
{
	return m_isModified;
}

bool MapEditor::IsAttachedFile()
{
	if(LPCTSTR(m_str) != NULL)
	{
		return _tcslen(m_str) > 0;
	}
	return false;
}

bool MapEditor::IsHasData()
{
	return m_pMapData != NULL;
}

bool MapEditor::IsMapSizeChanged(bool isProcessed)
{
	bool t = m_isMapSizeChanged;
	if(isProcessed)
	{
		m_isMapSizeChanged = false;
	}
	return t;
}

bool MapEditor::IsDrawed(bool isProcessed)
{
	bool t = m_isDrawed;
	if(isProcessed)
	{
		m_isDrawed = true;
	}
	return t;
}

void MapEditor::InitMapByRandomHeight()
{	
	for(UINT i = 0; i < m_height * m_width; ++i)
	{
		m_pMapData[i] = Random(0.0f, 1.0f);
	}
	m_isModified = true;
	m_isDrawed = false;
}

void MapEditor::Filter(int nFilteTimes, float filterPar)
{
	ATLASSERT(nFilteTimes > 0);
	for(int i = 0; i < nFilteTimes; ++i)
	{
		FilterHeightField(m_pMapData, m_height, filterPar);
	}
	m_isModified = true;
	m_isDrawed = false;
}

void MapEditor::MakePlasma(float rough)
{
	MakeTerrainPlasma(m_pMapData, m_height, rough);

	m_isModified = true;
	m_isDrawed = false;
}

void MapEditor::MakeFault(int iterations,int maxDelta,int minDelta,int iterationsPerFilter,float filter)
{
	MakeTerrainFault(m_pMapData, m_height, iterations, maxDelta, minDelta, iterationsPerFilter, filter);

	m_isModified = true;
	m_isDrawed = false;
}