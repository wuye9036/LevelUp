#!/usr/bin/env python
# -*- coding: cp936 -*-

from PyQt4 import QtGui, QtCore

class AltCrtModel(QtCore.QAbstractTableModel):
	def __init__(self, altCrtMat, parent = None):
		QtCore.QAbstractTableModel.__init__(self, parent)
		self.altCrtMat_ = altCrtMat
		print altCrtMat.Priorities()
		
	def HorizontalHeaderItems(self):
		return [""] + self.altCrtMat_.CriterionNames() + ["Priority", "Ranking"]
		
	def rowCount(self, index):
		return len(self.altCrtMat_.AlternativeNames()) + 1 #多的一个是为了给criteria的值显示
	
	def columnCount(self, index):
		return len(self.HorizontalHeaderItems())
	
	def data(self, index, role):
		invalidRet = QtCore.QVariant()
		if role != QtCore.Qt.DisplayRole: return invalidRet
		if not index.isValid(): return invalidRet
		
		#第一行喂Criteria Value
		row, col = index.row(), index.column()
		if row == 0:
			#第一列喂AlternativeNames
			if col == 0: return QtCore.QVariant("AlternativeNames")
			if col - 1 < len(self.altCrtMat_.CriterionNames()):
				return QtCore.QVariant(self.altCrtMat_.CrtPriority(col - 1))
		
		#第一列喂AlternativeNames	
		if col == 0:
			return QtCore.QVariant(self.altCrtMat_.AlternativeNames()[row-1])
		
		#属于Alt - Crt矩阵的项
		if col - 1 < len(self.altCrtMat_.CriterionNames()):
			return QtCore.QVariant(self.altCrtMat_.AltCrtValue(row-1, col-1))

		#属于Priority和Rank的项
		if col - len(self.altCrtMat_.CriterionNames()) == 1:
			if row > 0:
				return QtCore.QVariant(self.altCrtMat_.PriorityByIndex(row - 1))
		
		if col - len(self.altCrtMat_.CriterionNames()) == 2:
			if row > 0:
				return QtCore.QVariant(self.altCrtMat_.RankByIdx(row - 1))
			
		return QtCore.QVariant()
	
	def headerData(self, section, orientation, role):
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		if orientation == QtCore.Qt.Horizontal:
			return QtCore.QVariant(self.HorizontalHeaderItems()[section])
		return QtCore.QVariant()
	
	def flags(self, index):
		return QtCore.QAbstractTableModel.flags(self, index)