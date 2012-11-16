#!/usr/bin/env python
# -*- coding: cp936 -*-
from PyQt4 import QtCore, QtGui
from AHP.Logic.SensitiveAnalyst import WSM
from AHP.Logic.SensitiveAnalyst import WPM

import math
def CreateCrtDegsViewerModel(modelName):
	if modelName == "WSM":
		return WSMCrtDegsViewerModel()
	else:
		return WPMCrtDegsViewerModel()
	
class CrtDegsViewerModel(QtCore.QAbstractTableModel):
	def __init__(self, parent = None):
		QtCore.QAbstractTableModel.__init__(self, parent)
	
	def Load(self, altCrtMat):
		self.altCrtMat_ = altCrtMat
		self._LoadChgMatAndSens(altCrtMat)
		
	def _LoadChgMatAndSens(self, altCrtMat):
		self.chgMat_ = None
		self.sens_ = None
		
	def Rank2Idx(self, rank):
		pass
	
	def HorizontalHeaderItems(self):
		return ["Alternative", "Rank"] + self.chgMat_.CriteriaNames()
		
	def rowCount(self, index):
		altCount = len(self.altCrtMat_.AlternativeNames())
		return altCount
	
	def columnCount(self, index):
		return len(self.HorizontalHeaderItems())
	
	def data(self, index, role):
		invalidRet = QtCore.QVariant()
		if role != QtCore.Qt.DisplayRole: return invalidRet
		if not index.isValid(): return invalidRet
		
		row, col = index.row(), index.column()
		altCount, crtCount = len(self.altCrtMat_.AlternativeNames()), len(self.altCrtMat_.CriterionNames())
		
		Ri = row + 1
		Ai = self.Rank2Idx(Ri)
		Ainame = self.chgMat_.AlternativeNames()[Ai]
		
		if col > 1:
			if self.sens_[row][col-2]:
				sensVal, Rj = self.sens_[row][col-2]
				Aj = self.Rank2Idx(Rj)
				Ajname = self.chgMat_.AlternativeNames()[Aj]
		
		if col == 0:
			return QtCore.QVariant(Ainame)
		if col == 1:
			return QtCore.QVariant(Ri)
		if 1 < col and col < crtCount + 2:
			if not self.sens_[row][col-2]: return QtCore.QVariant("—".decode('cp936'))
			return QtCore.QVariant("%s(R%s,Alt.%s)" % (str(sensVal), str(Rj), str(Ajname)))

		return QtCore.QVariant()
	
	def headerData(self, section, orientation, role):
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		if orientation == QtCore.Qt.Horizontal:
			return QtCore.QVariant(self.HorizontalHeaderItems()[section])
		return QtCore.QVariant()
	
	def flags(self, index):
		return QtCore.QAbstractTableModel.flags(self, index)
	
class WSMCrtDegsViewerModel(CrtDegsViewerModel):
	def __init__(self, parent = None):
		CrtDegsViewerModel.__init__(self, parent)
		
	def _LoadChgMatAndSens(self, altCrtMat):
		self.chgMat_ = WSM.ChangeMatrix.ChangeMatrix(self.altCrtMat_)
		self.chgMat_.Compute()
		altSens = WSM.Sensitive.AlternativeSensitive(self.chgMat_)
		altSens.Compute()
		self.sens_ = altSens.CriticalDegrees()
		
	def Rank2Idx(self, rank):
		return self.altCrtMat_.IdxByRank(rank)
	
class WPMCrtDegsViewerModel(CrtDegsViewerModel):
	def __init__(self, parent = None):
		CrtDegsViewerModel.__init__(self, parent)
		
	def _LoadChgMatAndSens(self, altCrtMat):
		self.chgMat_ = WPM.ChangeMatrix.ChangeMatrix(self.altCrtMat_)
		self.chgMat_.Compute()
		altSens = WPM.Sensitive.AlternativeSensitive(self.chgMat_)
		altSens.Compute()
		self.sens_ = altSens.CriticalDegrees()
		
	def Rank2Idx(self, rank):
		return self.chgMat_.RatioTable().Rank2Idx(rank)