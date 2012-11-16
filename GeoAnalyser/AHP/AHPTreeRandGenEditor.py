#!/usr/bin/env python
#!/usr/bin/env python
# -*- coding: cp936 -*-

from PyQt4 import QtCore, QtGui
from UI.AHPTreeRandParamSet_ui import *

from Model.AHPMatrixWeightSetModels import *
from Logic.Distributors import *

class AHPTreeRandGenEditor(QtCore.QObject):
	def __init__(self, ahpTree):
		QtCore.QObject.__init__(self)
		
		self.ahpTree_ = ahpTree
		self.distCol_ = DistributorCollection()
		self.curDist_ = None
		
		self.dlg_ = QtGui.QDialog()
		self.ui_ = Ui_Dialog()
		self.ui_.setupUi(self.dlg_)
		
		self.paramModel_ = ParametersModel()	
		self.paramDelegate_ = ParametersDelegate()
	
		self.ui_.tblDistParams.setModel(self.paramModel_)
		self.ui_.tblDistParams.setItemDelegate(self.paramDelegate_)
		
		self._SetupSlots()
		self._SetupControls()
		
	def _SetupControls(self):
		for distName in self.distCol_.GetDistributorNames():
			self.ui_.comboDistName.addItem(QtCore.QString(distName))
		
		self.ui_.comboDistName.setCurrentIndex(0)
		
	def _SetupSlots(self):
		self.connect(self.ui_.btnOK, QtCore.SIGNAL("clicked(bool)"), self._OnOK)
		self.connect(self.ui_.btnCancel, QtCore.SIGNAL("clicked(bool)"), self._OnCancel)
		self.connect(self.ui_.comboDistName, QtCore.SIGNAL("currentIndexChanged (const QString&)"), self._OnDistributorChanged)
		return
	
	def ShowWidget(self):
		return self.dlg_.show()
		
	def ShowWidgetModal(self):
		return self.dlg_.exec_()
			
	def _UpdateTree(self):
		nodes = self.ahpTree_.AllNodeList()
		for node in nodes:
			node.ahpMat_.RandomFill(self.curDist_)
		rootNode = self.ahpTree_.Root()
		rootNode.UpdateTree()
	
	def _OnOK(self):
		self._UpdateTree()
		self.dlg_.accept()
	
	def _OnCancel(self):
		self.dlg_.reject()
	
	def _OnDistributorChanged(self, itemStr):
		self.curDist_ = self.distCol_.GetDistributor(str(itemStr))
		self.paramModel_.SetDistributor(self.curDist_)
		
	def GetDistributor(self):
		return self.paramModel_.GetDistributor()