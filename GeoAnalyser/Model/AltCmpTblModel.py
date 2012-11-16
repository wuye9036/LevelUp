#!/usr/bin/env python
# -*- coding: cp936 -*-

from PyQt4 import QtCore, QtGui

class AltCmpTblModel(QtCore.QAbstractTableModel):
	def __init__(self, altCmpTbl, parent = None):
		QtCore.QAbstractTableModel.__init__(self, parent)
		self.altCmpTbl_ = altCmpTbl
	
	def HorizontalHeaderItems(self):
		return self.altCmpTbl_.GetItemNames() + ["Weight", "Ranking"]
		
	def rowCount(self, index):
		return self.altCmpTbl_.GetMatrixSize()[0]
	
	def columnCount(self, index):
		return len(self.HorizontalHeaderItems())
	
	def data(self, index, role):
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		
		col = index.column()
		row = index.row()
		result = None
		isMatrixItem = lambda col: 0 <= col and col < self.altCmpTbl_.GetMatrixSize()[1]
		
		#col属于矩阵则往矩阵中添加
		if isMatrixItem(col):
			return QtCore.QVariant(self.altCmpTbl_.mat_[row][col])
		else:
			#否则就是weight或者rank
			colName = str(
				self.headerData(col, QtCore.Qt.Horizontal, QtCore.Qt.DisplayRole).toString()
				)
			if colName.lower() == 'weight':
				return QtCore.QVariant(self.altCmpTbl_.Weight(self.altCmpTbl_.GetItemNames()[row]))
			if colName.lower() == 'ranking':
				return QtCore.QVariant(self.altCmpTbl_.Rank(self.altCmpTbl_.GetItemNames()[row]))
			
	def headerData(self, section, orientation, role):
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		if orientation == QtCore.Qt.Horizontal:
			return QtCore.QVariant(self.HorizontalHeaderItems()[section])
		elif orientation == QtCore.Qt.Vertical:
			return QtCore.QVariant(self.altCmpTbl_.GetItemNames()[section])
		return QtCore.QVariant()
	
	def flags(self, index):
		return QtCore.QAbstractTableModel.flags(self, index)
		
class AltCmpTblPropsModel(QtCore.QAbstractTableModel):
	def __init__(self, altCmpTbl, parent = None):
		QtCore.QAbstractTableModel.__init__(self, parent)
		self.altCmpTbl_ =  altCmpTbl
		
	def columnCount(self, parent):
		return 2
	
	def rowCount(self, parent):
		return len(self.altCmpTbl_.GetPropertyNames())
	
	def headerData(self, section, orientation, role):
		header = ["Index", "Value"]
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		if orientation == QtCore.Qt.Horizontal:
			return QtCore.QVariant(header[section])
		return QtCore.QVariant()
	
	def data(self, index, role):
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		col = index.column()
		row = index.row()
		result = None
		propName = self.altCmpTbl_.GetPropertyNames()[row]
		if col == 0:
			return QtCore.QVariant(propName)
		return QtCore.QVariant(self.altCmpTbl_.GetProperty(propName))