#!/usr/bin/env python
#!/usr/bin/env python
# -*- coding: cp936 -*-
from PyQt4 import QtCore, QtGui
from AHP.Logic.SensitiveAnalyst import WSM
from AHP.Logic.SensitiveAnalyst import WPM

import math

def CreateSensListViewerModel(modelName):
	if modelName == "WSM":
		return WSMSensListViewerModel()
	if modelName == "WPM":
		return WPMSensListViewerModel()
	
class SensListViewerModel(QtCore.QAbstractTableModel):
	def __init__(self, parent = None):
		QtCore.QAbstractTableModel.__init__(self, parent)
	
	def Load(self, altCrtMat):
		self.altCrtMat_ = altCrtMat
		self._LoadChgMatAndSens(altCrtMat)

	def _LoadChgMatAndSens(self, altCrtMat):
		self.chgMat_ = None
		self.sens_ = None
		pass
	
	def HorizontalHeaderItems(self):
		return ["Criterion", "Sensitive"]
		
	def rowCount(self, index):
		return len(self.altCrtMat_.CriterionNames())
	
	def columnCount(self, index):
		return len(self.HorizontalHeaderItems())
	
	def data(self, index, role):
		invalidRet = QtCore.QVariant()
		if role != QtCore.Qt.DisplayRole: return invalidRet
		if not index.isValid(): return invalidRet
		
		row, col = index.row(), index.column()
		
		if col == 0:
			return QtCore.QVariant(self.chgMat_.CriteriaNames()[row])
		if col == 1:
			return QtCore.QVariant(self.sens_[row])
		
		return QtCore.QVariant()
	
	def headerData(self, section, orientation, role):
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		if orientation == QtCore.Qt.Horizontal:
			return QtCore.QVariant(self.HorizontalHeaderItems()[section])
		return QtCore.QVariant()
	
	def flags(self, index):
		return QtCore.QAbstractTableModel.flags(self, index)
	
class WSMSensListViewerModel(SensListViewerModel):
	def __init__(self, parent = None):
		SensListViewerModel.__init__(self, parent)
		
	def _LoadChgMatAndSens(self, altCrtMat):
		self.chgMat_ = WSM.ChangeMatrix.ChangeMatrix(self.altCrtMat_)
		self.chgMat_.Compute()
		crtSens = WSM.Sensitive.CriteriaSensitive(self.chgMat_)
		crtSens.Compute()
		self.sens_ = crtSens.CriteriaSensitives()

class WPMSensListViewerModel(SensListViewerModel):
	def __init__(self, parent = None):
		SensListViewerModel.__init__(self, parent)
		
	def _LoadChgMatAndSens(self, altCrtMat):
		self.chgMat_ = WPM.ChangeMatrix.ChangeMatrix(self.altCrtMat_)
		self.chgMat_.Compute()
		crtSens = WPM.Sensitive.CriteriaSensitive(self.chgMat_)
		crtSens.Compute()
		self.sens_ = crtSens.CriteriaSensitives()		