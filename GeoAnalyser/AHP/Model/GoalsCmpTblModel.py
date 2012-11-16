#!/usr/bin/env python
# -*- coding: cp936 -*-

"""
与GoalsComprisonTable界面有关的Model和Delegate
"""
from PyQt4 import QtCore, QtGui
import traceback

class GoalsCmpTblModel(QtCore.QAbstractTableModel):
	def __init__(self, goalsCmpTbl, parent = None):
		QtCore.QAbstractTableModel.__init__(self, parent)
		self.goalsCmpTbl_ = goalsCmpTbl
	
	def HorizontalHeaderItems(self):
		return self.goalsCmpTbl_.GetItemNames() + ["Weight", "Ranking"]
		
	def rowCount(self, index):
		return self.goalsCmpTbl_.GetMatrixSize()[0]
	
	def columnCount(self, index):
		return len(self.HorizontalHeaderItems())
	
	def data(self, index, role):
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		
		col = index.column()
		row = index.row()
		result = None
		isMatrixItem = lambda col: 0 <= col and col < self.goalsCmpTbl_.GetMatrixSize()[1]
		
		#col属于矩阵则往矩阵中添加
		if isMatrixItem(col):
			return QtCore.QVariant(self.goalsCmpTbl_.mat_[row][col])
		else:
			#否则就是weight或者rank
			colName = str(
				self.headerData(col, QtCore.Qt.Horizontal, QtCore.Qt.DisplayRole).toString()
				)
			if colName.lower() == 'weight':
				return QtCore.QVariant(self.goalsCmpTbl_.Weight(self.goalsCmpTbl_.GetItemNames()[row]))
			if colName.lower() == 'ranking':
				return QtCore.QVariant(self.goalsCmpTbl_.Rank(self.goalsCmpTbl_.GetItemNames()[row]))
			
	def setData(self, index, value, role = QtCore.Qt.EditRole):
		if role != QtCore.Qt.EditRole: return False
		if not value.isValid(): return False
		row, col = index.row(), index.column()
		
		try:
			fvalue = float(eval(str(value.toString())))
			self.goalsCmpTbl_.mat_[row][col] = fvalue
			self.goalsCmpTbl_._UpdateByUTri()
			traceback.print_exc()
			self.reset()
		except:
			return False
		
	def headerData(self, section, orientation, role):
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		if orientation == QtCore.Qt.Horizontal:
			return QtCore.QVariant(self.HorizontalHeaderItems()[section])
		elif orientation == QtCore.Qt.Vertical:
			return QtCore.QVariant(self.goalsCmpTbl_.GetItemNames()[section])
		return QtCore.QVariant()
	
	def flags(self, index):
		return QtCore.QAbstractTableModel.flags(self, index) | QtCore.Qt.ItemIsEditable
	
class GoalsCmpTblDelegate(QtGui.QItemDelegate):
	def __init__(self, parent = None):
		QtGui.QItemDelegate.__init__(self, parent)
		
	def createEditor(self, parent, option, index):
		if 0 < index.column() and index.column() < index.model().rowCount(QtCore.QModelIndex()) and index.row() < index.column():
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
		
class GoalsCmpTblPropsModel(QtCore.QAbstractTableModel):
	def __init__(self, goalsCmpTbl, parent = None):
		QtCore.QAbstractTableModel.__init__(self, parent)
		self.goalsCmpTbl_ =  goalsCmpTbl
		
	def columnCount(self, parent):
		return 2
	
	def rowCount(self, parent):
		return len(self.goalsCmpTbl_.GetPropertyNames())
	
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
		propName = self.goalsCmpTbl_.GetPropertyNames()[row]
		if col == 0:
			return QtCore.QVariant(propName)
		return QtCore.QVariant(self.goalsCmpTbl_.GetProperty(propName))