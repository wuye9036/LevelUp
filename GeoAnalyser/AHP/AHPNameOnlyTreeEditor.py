#!/usr/bin/env python
# -*- coding: cp936 -*-

import os, sys

from Model.AHPNameOnlyTreeModel import *
from Logic.AHPTree import *
from UI.AHPTreeEditor_ui import *
from LocationAltGenerator.ProximityBuilderImpl.LinguisticTable import *

class AHPNameOnlyTreeContextMenu(QtCore.QObject):
	def __init__(self, treeView):
		QtCore.QObject.__init__(self, treeView)
		self.treeView_ = treeView
		self._SetupActions()
		self.connect(treeView, QtCore.SIGNAL("pressed (const QModelIndex&)"), self._SetupMenuActionEnabled)
		
	def _SetupActions(self):
		font = QtGui.QFont("宋体", 9)
		self.actMoveUp_ = QtGui.QAction("上移节点".decode("cp936"), self.treeView_)
		self.actMoveUp_.setFont(font)
		self.connect(self.actMoveUp_, QtCore.SIGNAL("triggered(bool)"), self._OnMoveUp)
		self.treeView_.addAction(self.actMoveUp_)
		
		self.actMoveDown_ = QtGui.QAction("下移节点".decode("cp936"), self.treeView_)
		self.actMoveDown_.setFont(font)
		self.connect(self.actMoveDown_, QtCore.SIGNAL("triggered(bool)"), self._OnMoveDown)
		self.treeView_.addAction(self.actMoveDown_)
		
		self.actDelete_ = QtGui.QAction("删除节点".decode("cp936"), self.treeView_)
		self.actDelete_.setFont(font)
		self.connect(self.actDelete_, QtCore.SIGNAL("triggered(bool)"), self._OnDelete)
		self.treeView_.addAction(self.actDelete_)
		
		self.actAdd_ = QtGui.QAction("添加子节点".decode("cp936"),self.treeView_)
		self.actAdd_.setFont(font)
		self.connect(self.actAdd_, QtCore.SIGNAL("triggered(bool)"), self._OnAdd)
		self.treeView_.addAction(self.actAdd_)
	
	#根据条件设置Menu Action的有效性	
	def _SetupMenuActionEnabled(self, index):
		actMoveDownEnabled = True
		actMoveUpEnabled = True
		actAddEnabled = True
		actDeleteEnabled = True
			
		if not index.isValid():
			actMoveDownEnabled = False
			actMoveUpEnabled = False
			actAddEnabled = False
			actDeleteEnabled = False
		else:
			if  not index.parent().isValid():
				actMoveDownEnabled = False
				actMoveUpEnabled = False
				actDeleteEnabled = False
			if not index.sibling(index.row() - 1, index.column()).isValid():
				actMoveUpEnabled = False
			if not index.sibling(index.row() + 1, index.column()).isValid():
				actMoveDownEnabled = False
		
		self.actAdd_.setEnabled(actAddEnabled)
		self.actDelete_.setEnabled(actDeleteEnabled)
		self.actMoveDown_.setEnabled(actMoveDownEnabled)
		self.actMoveUp_.setEnabled(actMoveUpEnabled)
		
	def _MoveCurrentItem(self, offset):
		curIndex = self.treeView_.currentIndex()
		if not curIndex.isValid(): return
		parentIndex = curIndex.parent()
		if not parentIndex.isValid(): return
		curItem = curIndex.internalPointer()
		if not curItem.IsValid(): return
		parentItem = curItem.ParentItem()
		if not parentItem.IsValid():return
		rhsIndex = curIndex.sibling(curIndex.row() + offset, 0)
		if not rhsIndex.isValid():return
		rhsItem = rhsIndex.internalPointer()
		if not rhsItem.IsValid(): return
		
		parentItem.SwapChildItemById(curIndex.row(), curIndex.row() + offset)
		self.treeView_.model().emit(QtCore.SIGNAL("layoutChanged ()"))

	def _OnMoveUp(self, b):
		self._MoveCurrentItem(-1)
	
	def _OnMoveDown(self, b):
		self._MoveCurrentItem(1)
	
	def _OnAdd(self, b):
		#获得现有索引、项目与AHP节点
		curIndex = self.treeView_.currentIndex()
		if not curIndex.isValid(): return
		curItem = curIndex.internalPointer()
		if not curItem.IsValid(): return
		curNode = curItem.ahpNode_
		
		#猜测一个临时的新名称
		tmpNameId = 0
		tmpName = "NewNode0"
		while curNode.IsNodeNameExists(tmpName):
			tmpNameId += 1
			tmpName = "NewNode"+str(tmpNameId)
		
		#构造新的树项目与节点并构造AHPNode的层级结构
		newNode = AHPTreeNode(deepcopy(tmpName), curNode.owner_, curNode)
		curNode.AddChild(newNode)
		newItem = AHPTreeModelItem(curItem)
		newItem.SetAHPTree(newNode)
		
		#追加节点
		rowPosInserted = curItem.ChildItemCount()
		self.treeView_.model().SetInsertedItems([newItem])
		self.treeView_.model().insertRow(rowPosInserted, curIndex)
	
	def _OnDelete(self, b):
		curIndex = self.treeView_.currentIndex()
		if not curIndex.isValid(): return
		parentIndex = curIndex.parent()
		
		curItem = curIndex.internalPointer()
		parentItem = curItem.ParentItem()
		if not (curItem.IsValid() and parentItem.IsValid()):
			return
		
		parentNode = parentItem.ahpNode_
		curNode = curItem.ahpNode_
		
		parentNode.RemoveChild(curNode.Name())
		self.treeView_.model().removeRow(curIndex.row(), parentIndex)
		
class AHPNameOnlyTreeEditor(QtCore.QObject):
	def __init__(self, ahpFile, parent = None):
		QtCore.QObject.__init__(self)
		
		#构造组件
		self.ahpFile_ = ahpFile
		self.tree_ = AHPTree()
		self.tree_.LoadXml(ahpFile)
		self.widget_ = QtGui.QDialog(parent)
		self.ui_ = Ui_AHPEditor()
		self.ui_.setupUi(self.widget_)
		
		#挂接模型与菜单
		self.treeModel_ = AHPNameOnlyTreeModel(self.tree_)
		self.treeDelegate_ = AHPNameOnlyTreeDelegate()
		self.contextMenu_ = AHPNameOnlyTreeContextMenu(self.ui_.aphTreeView)
		self.ui_.btnRandGen.setHidden(True)

		self.ui_.aphTreeView.setModel(self.treeModel_)
		self.ui_.aphTreeView.setItemDelegate(self.treeDelegate_)
	
		#挂接signal/slot
		self._SetupSlots()
		
	def _SetupSlots(self):
		self.connect(self.ui_.aphTreeView, QtCore.SIGNAL("doubleClicked (const QModelIndex&)"), self._OnEditMatrix)
		self.connect(self.ui_.applyBtn, QtCore.SIGNAL("clicked(bool)"), self._OnSaveToFile)
		self.connect(self.ui_.acceptBtn, QtCore.SIGNAL("clicked(bool)"), self._OnAccept)
	
	def _OnEditMatrix(self, index):
		if not index.isValid(): return
		
		if index.column() == 1:
			curTreeItem = index.internalPointer()
			curNode = curTreeItem.ahpNode_
			if not curNode: return
			matEditor = AHPMatrixEditor(curNode.ahpMat_)
			matEditor.ShowWidgetModal()
			curTreeItem.UpdateTree()
			
	def _OnSaveToFile(self, b):
		self.tree_.SaveXml(self.ahpFile_)
		self.tree_.SaveCriteriaToXmlFile(os.path.join(os.path.dirname(self.ahpFile_), "Criteria.xml"))
		
		#更新Linguistic Table
		leafList = [node for node in self.tree_.AllNodeList() if node.IsLeaf()]
		leafNameSet = set([node.Name() for node in leafList])
		lt = LinguisticTable(os.path.join(os.path.dirname(self.ahpFile_), "Linguistic File.txt"))
		ltDict = lt.Data()
		ltNameSet = set(ltDict.keys())
		missingItems = leafNameSet - ltNameSet
		unwantedItems = ltNameSet - leafNameSet
		
		for unwantedItem in unwantedItems:
			del ltDict[unwantedItem]
		for missingItem in missingItems:
			ltDict[missingItem] = LinguisticValue.DefaultValue(missingItem)
		lt.Save()
		
	def _OnAccept(self, b):
		self._OnSaveToFile(b)
		self.widget_.accept()
		
	def ShowWidget(self):
		self.widget_.show()
	
	def ShowWidgetModal(self):
		result = self.widget_.exec_()
		if result == QtGui.QDialog.Accepted:
			self._OnSaveToFile(True)