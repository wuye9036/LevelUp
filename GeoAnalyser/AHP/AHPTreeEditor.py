#!/usr/bin/env python
# -*- coding: cp936 -*-
import os

from PyQt4 import QtCore, QtGui

from UI.AHPTreeEditor_ui import *
from Model.AHPTreeModel import *
from Logic.AHPTree import *

from AHPCmpTblEditor import *
from AHPTreeRandGenEditor import *

class AHPTreeContextMenu(QtCore.QObject):
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
	
	#根据条件设置Menu Action的有效性	
	def _SetupMenuActionEnabled(self, index):
		actMoveDownEnabled = True
		actMoveUpEnabled = True
			
		if not index.isValid():
			actMoveDownEnabled = False
			actMoveUpEnabled = False
		else:
			if  not index.parent().isValid():
				actMoveDownEnabled = False
				actMoveUpEnabled = False
			if not index.sibling(index.row() - 1, index.column()).isValid():
				actMoveUpEnabled = False
			if not index.sibling(index.row() + 1, index.column()).isValid():
				actMoveDownEnabled = False
		
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
		
class AHPTreeEditor(QtCore.QObject):
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
		self.treeModel_ = AHPTreeModel(self.tree_)
		self.contextMenu_ = AHPTreeContextMenu(self.ui_.aphTreeView)

		self.ui_.aphTreeView.setModel(self.treeModel_)
	
		#挂接signal/slot
		self._SetupSlots()
		
	def _SetupSlots(self):
		self.connect(self.ui_.aphTreeView, QtCore.SIGNAL("doubleClicked (const QModelIndex&)"), self._OnEditMatrix)
		self.connect(self.ui_.applyBtn, QtCore.SIGNAL("clicked(bool)"), self._OnSaveToFile)
		self.connect(self.ui_.acceptBtn, QtCore.SIGNAL("clicked(bool)"), self._OnAccept)
		self.connect(self.ui_.btnRandGen, QtCore.SIGNAL("clicked(bool)"), self._OnRandomGen)
		
	def _OnEditMatrix(self, index):
		if not index.isValid(): return
		
		if index.column() != 0:
			curTreeItem = index.internalPointer()
			curNode = curTreeItem.ahpNode_
			if not curNode: return
			matEditor = AHPCmpTblEditor(curNode.ahpMat_)
			matEditor.dlg_.setWindowTitle("Comparison Table Editor")
			matEditor.ShowWidgetModal()
			curTreeItem.UpdateTree()
	
	def _OnRandomGen(self):
		randGen = AHPTreeRandGenEditor(self.tree_)
		randGen.ShowWidgetModal()
		self.treeModel_.reset()
			
	def _OnSaveToFile(self, b):
		self.tree_.SaveXml(self.ahpFile_)
		self.tree_.SaveCriteriaToXmlFile(os.path.join(os.path.dirname(self.ahpFile_), "Criteria.xml"))
		
	def _OnAccept(self, b):
		self._OnSaveToFile(b)
		self.widget_.accept()
		
	def ShowWidget(self):
		self.widget_.show()
	
	def ShowWidgetModel(self):
		result = self.widget_.exec_()
		if result == QtGui.QDialog.Accepted:
			self._OnSaveToFile(True)