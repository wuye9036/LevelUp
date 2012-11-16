#!/usr/bin/env python
# -*- coding: cp936 -*-
from PyQt4 import QtCore, QtGui
from AHP.Logic.SensitiveAnalyst import WSM
from AHP.Logic.SensitiveAnalyst import WPM

import math
def CreateThValViewerModel(modelName):
	if modelName == "WSM":
		return WSMThValViewerModel()
	if modelName == "WPM":
		return WPMThValViewerModel()
	
class ThValViewerModel(QtCore.QAbstractTableModel):
	def __init__(self, parent = None):
		QtCore.QAbstractTableModel.__init__(self, parent)
	
	def Load(self, altCrtMat):
		self.altCrtMat_ = altCrtMat
		self._LoadChgMat(altCrtMat)
		
	def _LoadChgMat(self, altCrtMat):
		self.chgMat_ = None
		
	def Rank2Idx(self, idx):
		pass
	
	def HorizontalHeaderItems(self):
		return ["Alt. (Ai)", "Rank (Ai)"] + self.chgMat_.CriteriaNames() + ["Rank (Aj)", "Alt. (Aj)"]
		
	def rowCount(self, index):
		altCount = len(self.altCrtMat_.AlternativeNames())
		return altCount * (altCount - 1)
	
	def columnCount(self, index):
		return len(self.HorizontalHeaderItems())
	
	def data(self, index, role):
		invalidRet = QtCore.QVariant()
		if role != QtCore.Qt.DisplayRole: return invalidRet
		if not index.isValid(): return invalidRet
		
		row, col = index.row(), index.column()
		altCount, crtCount = len(self.altCrtMat_.AlternativeNames()), len(self.altCrtMat_.CriterionNames())

		Ri = row / (altCount - 1) + 1
		Rjth = row % (altCount - 1) + 1
		if Rjth < Ri:
			Rj = Rjth
		else:
			Rj = Rjth+1
		
		Ai, Aj = map(self.Rank2Idx, (Ri, Rj))
		Ainame, Ajname = map(self.chgMat_.AlternativeNames().__getitem__, (Ai, Aj))
		
		if col == 0:
			return QtCore.QVariant(Ainame)
		if col == 1:
			return QtCore.QVariant(Ri)
		if 1 < col and col < crtCount + 2:
			return QtCore.QVariant(str(self.chgMat_.RelatedAlternativeChangeMatrix()[(Ri, Rj)][col-2]))
		if col == crtCount + 2:
			return QtCore.QVariant(Rj)
		if col == crtCount + 3:
			return QtCore.QVariant(Ajname)
		
		return QtCore.QVariant()
	
	def headerData(self, section, orientation, role):
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		if orientation == QtCore.Qt.Horizontal:
			return QtCore.QVariant(self.HorizontalHeaderItems()[section])
		return QtCore.QVariant()
	
	def flags(self, index):
		return QtCore.QAbstractTableModel.flags(self, index)
	
class WSMThValViewerModel(ThValViewerModel):
	def __init__(self, parent = None):
		ThValViewerModel.__init__(self, parent)
	
	def _LoadChgMat(self, altCrtMat):
		self.chgMat_ = WSM.ChangeMatrix.ChangeMatrix(altCrtMat)
		self.chgMat_.Compute()
		
	def Rank2Idx(self, idx):
		return self.altCrtMat_.IdxByRank(idx)
	
class WPMThValViewerModel(ThValViewerModel):
	def __init__(self, parent = None):
		ThValViewerModel.__init__(self, parent)
		
	def _LoadChgMat(self, altCrtMat):
		self.chgMat_ = WPM.ChangeMatrix.ChangeMatrix(altCrtMat)
		self.chgMat_.Compute()
		
	def Rank2Idx(self, rank):
		return self.chgMat_.RatioTable().Rank2Idx(rank)