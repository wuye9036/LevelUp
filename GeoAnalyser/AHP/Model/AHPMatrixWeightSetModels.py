#!/usr/bin/env python
# -*- coding: cp936 -*-

from PyQt4 import QtCore, QtGui
from AHP.Logic.Distributors import *

class WeightListModel(QtCore.QAbstractTableModel):
	def __init__(self, items, parent = None):
		QtCore.QAbstractTableModel.__init__(self, parent)
		
		self.items_ = items
		self.itemCnt_ = len(self.items_)
		
		self.weights_ = [1.0 / self.itemCnt_ for i in range(self.itemCnt_)]
	
	def SetWeights(self, weights):
		self.weights_ = weights
		self.reset()
		
	def HorizontalHeaderItems(self):
		return ["Criterion", "Weights"]
		
	def rowCount(self, index):
		return self.itemCnt_
	
	def columnCount(self, index):
		return len(self.HorizontalHeaderItems())
	
	def data(self, index, role):
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		
		row = index.row()
		col = index.column()
		
		try:
			if col == 0:
				return QtCore.QVariant(self.items_[row])
			if col == 1:
				return QtCore.QVariant(self.weights_[row])
		except:
			return QtCore.QVariant()
		
		return QtCore.QVariant()
		
	def headerData(self, section, orientation, role):
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		if orientation == QtCore.Qt.Horizontal:
			return QtCore.QVariant(self.HorizontalHeaderItems()[section])
		return QtCore.QVariant()

class ParametersModel(QtCore.QAbstractTableModel):
	def __init__(self, parent = None):
		QtCore.QAbstractTableModel.__init__(self, parent)
		self.dist_ = None
		
	def SetDistributor(self, dist):
		self.dist_ = dist
		self.reset()
	
	def GetDistributor(self):
		return self.dist_
	
	def HorizontalHeaderItems(self):
		return ["Parameter", "Value"]
		
	def rowCount(self, index):
		if not self.dist_:
			return 0
		
		return len(self.dist_.GetParameterNames())
	
	def columnCount(self, index):
		return len(self.HorizontalHeaderItems())
	
	def data(self, index, role):
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		
		row = index.row()
		col = index.column()
		
		try:
			if col == 0:
				return QtCore.QVariant(self.dist_.GetParameterNames()[row])
			if col == 1:
				return QtCore.QVariant( getattr(self.dist_, self.dist_.GetParameterNames()[row]) )
		except:
			return QtCore.QVariant()
		
		return QtCore.QVariant()
		
	def headerData(self, section, orientation, role):
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		if orientation == QtCore.Qt.Horizontal:
			return QtCore.QVariant(self.HorizontalHeaderItems()[section])
		return QtCore.QVariant()
	
	def setData(self, index, value, role = QtCore.Qt.EditRole):
		if role != QtCore.Qt.EditRole: return False
		if not value.isValid(): return False
		
		row, col = index.row(), index.column()
		
		try:
			svalue = float(str(value.toString()))
			paramName = self.dist_.GetParameterNames()[row]
			setattr(self.dist_, paramName, svalue)
			return True
		
		except:
			return False
		
	def flags(self, index):
		return QtCore.QAbstractTableModel.flags(self, index) | QtCore.Qt.ItemIsEditable
	
class ParametersDelegate(QtGui.QItemDelegate):
	def __init__(self, parent = None):
		QtGui.QItemDelegate.__init__(self, parent)
		
	def createEditor(self, parent, option, index):
		if index.column() == 1:
			editor = QtGui.QLineEdit(parent)
			editor.installEventFilter(self)
			return editor
		else:
			return
	
	def setEditorData(self, lineEditor, index):
		value = index.model().data(index, QtCore.Qt.DisplayRole).toString()
		lineEditor.setText(value)
	
	def setModelData(self, lineEditor, model, index):
		value = lineEditor.text()
		model.setData(index, QtCore.QVariant(value))
		
	def updateEditorGeometry(self, editor, option, index):
		editor.setGeometry(option.rect)
	

	

