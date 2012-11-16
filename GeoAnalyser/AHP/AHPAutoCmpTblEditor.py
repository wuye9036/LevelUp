#!/usr/bin/env python
# -*- coding: cp936 -*-

from PyQt4 import QtCore, QtGui
from UI.AHPMatrixWeightSet_ui import *

from Model.AHPMatrixWeightSetModels import *
from Logic.Distributors import *

class AHPAutoCmpTblEditor(QtCore.QObject):
	def __init__(self, cmpTbl):
		QtCore.QObject.__init__(self)
		
		self.cmpTbl_ = cmpTbl
		self.distCol_ = DistributorCollection()
		self.curDist_ = None
		self.weights_ = [1.0 / len(cmpTbl.GetItemNames()) for i in range(len(cmpTbl.GetItemNames()))]
		
		self.dlg_ = QtGui.QDialog()
		self.ui_ = Ui_Dialog()
		self.ui_.setupUi(self.dlg_)
		
		self.weightListModel_ = WeightListModel(self.cmpTbl_.GetItemNames())
		self.paramModel_ = ParametersModel()	
		self.paramDelegate_ = ParametersDelegate()
	
		self.ui_.tblCrtWeights.setModel(self.weightListModel_)
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
		self.connect(self.ui_.btnRedist, QtCore.SIGNAL("clicked(bool)"), self._OnRedist)
		self.connect(self.ui_.comboDistName, QtCore.SIGNAL("currentIndexChanged (const QString&)"), self._OnDistributorChanged)
		return
	
	def ShowWidget(self):
		return self.dlg_.show()
		
	def ShowWidgetModal(self):
		return self.dlg_.exec_()
			
	def _OnRedist(self):
		newWeights = [self.paramModel_.GetDistributor().GetRandom() for i in self.weights_]
		self.weights_ = newWeights
		self.weightListModel_.SetWeights(self.weights_)
		pass
	
	def _OnOK(self):
		self._UpdateCmpTbl()
		self.dlg_.accept()
	
	def _OnCancel(self):
		self.dlg_.reject()
	
	def _OnDistributorChanged(self, itemStr):
		self.curDist_ = self.distCol_.GetDistributor(str(itemStr))
		self.paramModel_.SetDistributor(self.curDist_)
		
	def _UpdateCmpTbl(self):
		size = len(self.weights_)
		for iRow in range(size):
			for iCol in range(size):
				ratio = self.weights_[iRow] / self.weights_[iCol]
				if ratio > 1.0:
					int_ratio = round(ratio)
				else:
					int_ratio = 1.0 / round(1.0 / ratio)
				self.cmpTbl_.mat_[iRow][iCol] = int_ratio