#!/usr/bin/env python
# -*- coding: cp936 -*-

import os, sys, MainDocument
from PyQt4 import QtGui, QtCore

def SaveTableModel(modelLst, sdir, parent):
	if not sdir:
		sdir = MainDocument.mainDoc.ProjDir
	fileName = QtGui.QFileDialog.getSaveFileName(
		parent,
		"Save Table as Excel Readable File",
		os.path.join(sdir, "untitled.csv"),
		"CSV File (*.csv)"
	)
	if not fileName:
		return
	
	#写表格
	f = open(unicode(fileName), 'w')
	for mdl in modelLst:
		rowcnt, colcnt = mdl.rowCount(QtCore.QModelIndex()), mdl.columnCount(QtCore.QModelIndex())
		#提取行表头
		hHeaderLst = []
		for hItemIdx in range(colcnt):
			var = mdl.headerData(hItemIdx, QtCore.Qt.Horizontal, QtCore.Qt.DisplayRole)
			if var.isValid():
				hHeaderLst.append(str(var.toString()))
			else:
				hHeaderLst.append("")
		#提取列表头
		vHeaderLst = []
		for vItemIdx in range(rowcnt):
			var = mdl.headerData(vItemIdx, QtCore.Qt.Vertical, QtCore.Qt.DisplayRole)
			if var and var.isValid():
				vHeaderLst.append(str(var.toString()))
			else:
				vHeaderLst.append("")
		
		f.write(',' + reduce(lambda s,item: s + ',' + item, hHeaderLst) + '\n')
		for rowIdx in range(rowcnt):
			f.write(vHeaderLst[rowIdx] + ',')
			dataLine = ""
			for colIdx in range(colcnt):
				mdlIdx = mdl.createIndex(rowIdx, colIdx)
				data = mdl.data(mdlIdx, QtCore.Qt.DisplayRole)
				if data and data.isValid():
					dataLine += (str(data.toString()) + ',')
				else:
					dataLine += ","
			f.write(dataLine + '\n')
			
		f.write(",\n,\n")
	f.close()