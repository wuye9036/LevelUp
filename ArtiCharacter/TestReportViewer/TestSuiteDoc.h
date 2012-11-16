// ***************************************************************
//	@file 
//  TestSuiteDoc date: 01/29/2007
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2007 LightSky / wuye9036@gmail.com - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#pragma once

/**
	与TreeView / MainFrame / ListView相对应的逻辑部分，提供基本的数据分派处理/输入输出/显示过程的数据处理等
*/
#include "TestSuiteWs.h"
#include "ITreeItem.h"

class TestSuiteDoc
{
private:
	string				m_fileName;		///<	文档阅览的文件名称
	TestSuiteWs	m_rootWs;			///<	根工作空间

public:
	TestSuiteDoc(void);
	~TestSuiteDoc(void);

public:
	/** 
	@brief 打开一个报表文件
	@date 1/29/2007
	@author		LightSky
	@param	pfStr	文件名称
	@return	如果打开文件成功则返回true，否则返回false。			
	@bug
	@warning
	*/
	bool OpenReportFile(const TCHAR* pfStr);

	/**
	@brief		打开一个报表工作空间
	@date		1/29/2007
	@author		LightSky
	@param		pWs	工作空间的名称。即包含测试报告的目录。
	@return		如果目录不存在则返回false。
	@bug
	@warning
	*/
	bool OpenReportWorkspace(const TCHAR* pWs);

	/** 
	@brief		获取列表的行名称
	@date		1/29/2007
	@author		LightSky
	@param
	@return		返回一个保存了列表控件所需要的行。
	@bug
	@warning
	*/
	StringList GetListColumns(void);

	/** 
	@brief		设置当前的有效树结点。List将会依据Tree的类型得到更新。
	@date		1/29/2007
	@author		LightSky
	@param		pTreeDir		设置树结点的路径字串。根目录不计。
	@return		如果找不到对应的树结点，则返回false。
	@bug
	@warning
	*/
	bool SetCurrentTreeNode(const TCHAR* pTreeDir);
};
