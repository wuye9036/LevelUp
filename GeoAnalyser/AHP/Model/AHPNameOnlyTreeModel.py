#!/usr/bin/env python
# -*- coding: cp936 -*-

from PyQt4 import QtCore, QtGui
from AHPTreeModelItem import *

class AHPNameOnlyTreeModel(QtCore.QAbstractItemModel):
	def __init__(self, ahpTree, parent = None):
		QtCore.QAbstractItemModel.__init__(self, parent)
		self.insertTreeItems_ = None
		
		rootAHPNode = ahpTree.Root()
		self.titleTreeItem_ = AHPTreeModelItem()
		self.titleTreeItem_.SetData(rootAHPNode.GetPropertyNames())
		rootItem = AHPTreeModelItem(self.titleTreeItem_)
		self.titleTreeItem_.AddChildItem(rootItem)
		rootItem.SetAHPTree(rootAHPNode)
		
	def columnCount(self, parent):
		return 1 #仅名称列

	def data(self, index, role):
		if not index.isValid(): return QtCore.QVariant()
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		item = index.internalPointer()
		return QtCore.QVariant(item.Data(index.column()))
	
	def flags(self, index):
		if not index.isValid():
			return QtCore.Qt.ItemIsEnabled
		return QtCore.Qt.ItemIsEnabled | QtCore.Qt.ItemIsSelectable | QtCore.Qt.ItemIsEditable
	
	def headerData(self, section, orientation, role):
		if orientation == QtCore.Qt.Horizontal and role == QtCore.Qt.DisplayRole:
			return self.titleTreeItem_.Data(section)
		return QtCore.QVariant()
	
	def index(self, row, column, parent):
		if row < 0 or column < 0 or row >= self.rowCount(parent) or column >= self.columnCount(parent):
			return QtCore.QModelIndex()

		if not parent.isValid():
			parentItem = self.titleTreeItem_
		else:
			parentItem = parent.internalPointer()

		childItem = parentItem.ChildItem(row)
		if childItem:
			return self.createIndex(row, column, childItem)
		
		return QtCore.QModelIndex()
		
	def parent(self, index):
		if not index.isValid():
			return QtCore.QModelIndex()
		childItem = index.internalPointer()
		parentItem = childItem.ParentItem()
		
		if parentItem == self.titleTreeItem_:
			return QtCore.QModelIndex()
		return self.createIndex(parentItem.Row(), 0, parentItem)

	def rowCount(self, parent):
		if parent.column() > 0:
			return 0

		if not parent.isValid():
			parentItem = self.titleTreeItem_
		else:
			parentItem = parent.internalPointer()

		return parentItem.ChildItemCount()

	def setData(self, index, value, role = QtCore.Qt.EditRole):
		if not index.isValid(): return False
		if role != QtCore.Qt.EditRole: return False
		item = index.internalPointer()
		if item == self.titleTreeItem_: return False
		if not item.ahpNode_: return False
		if not value.isValid(): return False
		
		item.SetIndexById(index.column(), str(value.toString()))
		return True
	
	def removeRows(self, row, count, parentIndex = QtCore.QModelIndex()):
		"""
		删除行。修改Item的层级结构，但是不改变Node的层级结构
		"""
		if not parentIndex.isValid(): return False
		
		parentItem = parentIndex.internalPointer()
		if not parentItem.IsValid(): return False
		
		self.beginRemoveRows(parentIndex, row, row+count-1)
		for removedItemId in range(row, row+count):
			#删除AHPTreeNode和Item
			childItem = parentItem.ChildItem(removedItemId)
			parentItem.RemoveChildItem(childItem)
			
		parentItem.UpdateTree()
		self.endRemoveRows()
		return True
	
	def removeRow(self, row, parentIndex = QtCore.QModelIndex()):
		return self.removeRows(row, 1, parentIndex)
	
	def SetInsertedItems(self, insertTreeItems):
		self.insertTreeItems_ = insertTreeItems
		
	def insertRows(self, row, count, parentIndex = QtCore.QModelIndex()):
		"""
		插入行。修改Item的层级结构，但是不改变Node的层级结构。
		用户需要保证Node和Item的层级结构保持一致。
		"""
		if not (self.insertTreeItems_ and len(self.insertTreeItems_) == count):
			print "未设置需要插入的项或需要插入的项与行数不符！"
			return False
			
		if not parentIndex.isValid(): return False
		parentItem = parentIndex.internalPointer()
		if not parentItem.IsValid(): return False
		
		self.beginInsertRows(parentIndex, row, row+count-1)
		pos = row
		
		for childItem in self.insertTreeItems_:
			parentItem.AddChildItem(childItem, pos)
			pos += 1
		parentItem.UpdateTree()
		
		self.endInsertRows()
		self.insertTreeItems_ = None
		return True
	
	def insertRow(self, row, parentIndex):
		self.insertRows(row, 1, parentIndex)
	
class AHPNameOnlyTreeDelegate(QtGui.QItemDelegate):
	def __init__(self, parent = None):
		QtGui.QItemDelegate.__init__(self, parent)
		
	def createEditor(self, parent, option, index):
		#0列为名称列
		if index.column() == 0:
			editor = QtGui.QLineEdit(parent)
			editor.installEventFilter(self)
			return editor
		return None
	
	def setEditorData(self, lineEditor, index):
		value = index.model().data(index, QtCore.Qt.DisplayRole).toString()
		lineEditor.setText(value)
	
	def setModelData(self, lineEditor, model, index):
		value = lineEditor.text()
		if value and len(value) > 0:
			model.setData(index, QtCore.QVariant(value))
		
	def updateEditorGeometry(self, editor, option, index):
		editor.setGeometry(option.rect)