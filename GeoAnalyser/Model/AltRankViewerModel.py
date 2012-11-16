#!/usr/bin/env python
# -*- coding: cp936 -*-
from PyQt4 import QtCore, QtGui

def CreateAltRankViewerModel(modelName):
	if modelName == "WSM":
		return WSMAltRankViewerModel()
	if modelName == "WPM":
		return WPMAltRankViewerModel()
	
class WSMAltRankViewerModel(QtCore.QAbstractTableModel):
	def __init__(self, parent = None):
		QtCore.QAbstractTableModel.__init__(self, parent)
	
	def Load(self, altCrtMat):
		self.altCrtMat_ = altCrtMat
		
	def HorizontalHeaderItems(self):
		return ["Alternative", "Priority", "Rank"]
		
	def rowCount(self, index):
		return len(self.altCrtMat_.AlternativeNames())
	
	def columnCount(self, index):
		return len(self.HorizontalHeaderItems())
	
	def data(self, index, role):
		invalidRet = QtCore.QVariant()
		if role != QtCore.Qt.DisplayRole: return invalidRet
		if not index.isValid(): return invalidRet
		
		row, col = index.row(), index.column()
		
		rank = row + 1
		idx = self.altCrtMat_.IdxByRank(rank)
		
		if col == 0:
			return QtCore.QVariant(self.altCrtMat_.AlternativeNames()[idx])
		if col == 1:
			return QtCore.QVariant(self.altCrtMat_.PriorityIndex(idx))
		if col == 2:
			return QtCore.QVariant(rank)
		
		return QtCore.QVariant()
	
	def headerData(self, section, orientation, role):
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		if orientation == QtCore.Qt.Horizontal:
			return QtCore.QVariant(self.HorizontalHeaderItems()[section])
		return QtCore.QVariant()
	
	def flags(self, index):
		return QtCore.QAbstractTableModel.flags(self, index)

class WSMAltRankViewerModel(QtCore.QAbstractTableModel):
	def __init__(self, parent = None):
		QtCore.QAbstractTableModel.__init__(self, parent)
	
	def Load(self, altCrtMat):
		self.altCrtMat_ = altCrtMat
		
	def HorizontalHeaderItems(self):
		return ["Alternative", "Priority", "Rank"]
		
	def rowCount(self, index):
		return len(self.altCrtMat_.AlternativeNames())
	
	def columnCount(self, index):
		return len(self.HorizontalHeaderItems())
	
	def data(self, index, role):
		invalidRet = QtCore.QVariant()
		if role != QtCore.Qt.DisplayRole: return invalidRet
		if not index.isValid(): return invalidRet
		
		row, col = index.row(), index.column()
		
		rank = row + 1
		idx = self.altCrtMat_.IdxByRank(rank)
		
		if col == 0:
			return QtCore.QVariant(self.altCrtMat_.AlternativeNames()[idx])
		if col == 1:
			return QtCore.QVariant(self.altCrtMat_.PriorityIndex(idx))
		if col == 2:
			return QtCore.QVariant(rank)
		
		return QtCore.QVariant()
	
	def headerData(self, section, orientation, role):
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		if orientation == QtCore.Qt.Horizontal:
			return QtCore.QVariant(self.HorizontalHeaderItems()[section])
		return QtCore.QVariant()
	
	def flags(self, index):
		return QtCore.QAbstractTableModel.flags(self, index)		