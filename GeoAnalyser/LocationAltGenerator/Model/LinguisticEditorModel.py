# -*- coding: cp936 -*-
from PyQt4 import QtCore
from PyQt4 import QtGui

#LinguisticEditor的Model
class LinguisticEditorModel(QtCore.QAbstractTableModel):
	def __init__(self, linguisticTable, parent = None):
		QtCore.QAbstractTableModel.__init__(self, parent)
		self.lingTbl_ = linguisticTable
		self.colLookUpTbl_ = ["FeatCls", "FeatType", "FuzzyType", "a1", "r1", "a2", "r2"]
		
	def HorizontalHeaderItems(self):
		return ["Criterian Name", "Feature Type", "Membership", "Alpha1", "Gamma1", "Alpha2", "Gamma2"]
	
	def rowCount(self, index):
		return len(self.lingTbl_.Data())
	
	def columnCount(self, index):
		return len(self.HorizontalHeaderItems())
	
	def data(self, index, role):
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		if not index.isValid(): return QtCore.QVariant()
		if index.row() > len(self.lingTbl_.Data()):
			return QtCore.QVariant()
		if index.column() > self.columnCount(QtCore.QModelIndex()):
			return QtCore.QVariant()
		featClsName = self.lingTbl_.Data().keys()[index.row()]
		try:
			return QtCore.QVariant(getattr(self.lingTbl_.Data()[featClsName], self.colLookUpTbl_[index.column()]))
		except:
			return QtCore.QVariant()
	
	def setData(self, index, value, role = QtCore.Qt.EditRole):
		if role != QtCore.Qt.EditRole: return False
		if not value.isValid(): return False
		row = index.row()
		col = index.column()
		
		rowName = self.lingTbl_.Data().keys()[row]
		colName = self.colLookUpTbl_[col]
		
		valStr = str(value.toString())
		orgStr = str(getattr(self.lingTbl_.Data()[rowName], colName, None))
				
		if not (orgStr and valStr and valStr != orgStr):
			return False
		
		lingVal = self.lingTbl_.Data()[rowName]
		
		#名字不改
		if colName == "FeatCls":
			return False
		
		#更改fuzzy type
		if colName == "FuzzyType":
			setattr(lingVal, colName, valStr)
			if valStr == "CloseTo":
				lingVal.a2 = 0.0
				lingVal.r2 = 0.0
			else:
				del lingVal.a2
				del lingVal.r2
			return True
		if colName == "FeatType":
			setattr(lingVal, colName, valStr)
			return True
		#更改值
		try:
			if colName == "a1":
				lingVal.a1 = float(valStr)
				return True
			elif colName == "r1":
				lingVal.r1 = float(valStr)
				return True
			elif colName == "a2":
				lingVal.a2 = float(valStr)
				return True
			elif colName == "r2":
				lingVal.r2 = float(valStr)
				return True
		except:
			pass
		
		return False
	
	def headerData(self, section, orientation, role):
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		if orientation == QtCore.Qt.Horizontal:
			return QtCore.QVariant(self.HorizontalHeaderItems()[section])
		return QtCore.QVariant()
	
	def flags(self, index):
		baseFlags = QtCore.Qt.ItemIsEnabled | QtCore.Qt.ItemIsSelectable
		editableFlags = baseFlags | QtCore.Qt.ItemIsEditable
		
		lingTblKeys = self.lingTbl_.Data().keys()
		
		#名称不可编辑
		if index.column() == 0:
			return baseFlags
		
		# 如果fuzzy是near的话，a2和r2就不可编辑
		if self.lingTbl_.Data()[lingTblKeys[index.row()]].FuzzyType == 'Near':
			if index.column() > 4:
				return baseFlags
			
		return editableFlags
	
class LinguisticEditorDelegate(QtGui.QItemDelegate):
	def __init__(self, parent = None):
		QtGui.QItemDelegate.__init__(self, parent)
	
	def createEditor(self, parent, option, index):
		#Featcls，名字不改
		if index.column() == 0:
			return None
		
		#Feature Type
		if index.column() == 1:
			editor = QtGui.QComboBox(parent)
			editor.addItem("Vector")
			editor.addItem("Raster")
			editor.installEventFilter(self)
			return editor
		#Fuzzy Type
		if index.column() == 2:
			editor = QtGui.QComboBox(parent)
			editor.addItem("Near")
			editor.addItem("CloseTo")
			editor.installEventFilter(self)
			return editor
		
		#值
		editor = QtGui.QLineEdit(parent)
		editor.installEventFilter(self)
		return editor
	
	def setEditorData(self, editor, index):
		#第一列和第二列均为枚举（FeatType和FuzzyType列）
		if index.column() == 1 or index.column() == 2:
			oldText = index.model().data(index, QtCore.Qt.DisplayRole).toString()
			curItemIdx = editor.findText(oldText)
			editor.setCurrentIndex(curItemIdx)
		else:
			value = index.model().data(index, QtCore.Qt.DisplayRole).toString()
			editor.setText(value)
	
	def setModelData(self, editor, model, index):
		if index.column() == 1 or index.column() == 2:
			value = editor.currentText()
		else:
			value = editor.text()
		model.setData(index, QtCore.QVariant(value))
		
	def updateEditorGeometry(self, editor, option, index):
		editor.setGeometry(option.rect)