#!/usr/bin/env python
# -*- coding: cp936 -*-
from PyQt4 import QtCore, QtGui
from AHP.Logic.SensitiveAnalyst import WSM
from AHP.Logic.SensitiveAnalyst import WPM
import math

def CreateRelChgViewerModel(modelName):
	if modelName == "WSM":
		return WSMRelChgViewerModel()
	if modelName == "WPM":
		return WPMRelChgViewerModel()
	
class RelChgViewerModel(QtCore.QAbstractTableModel):
	def __init__(self, parent = None):
		QtCore.QAbstractTableModel.__init__(self, parent)
	
	def Load(self, altCrtMat):
		self.altCrtMat_ = altCrtMat
		self._LoadChgMat(altCrtMat)
		
	def _LoadChgMat(self, altCrtMat):
		self.chgMat_ = None
		
	def Rank2Idx(self, rank):
		return
		
	def HorizontalHeaderItems(self):
		return ["Alt Pair", "Rank Pair"] + self.chgMat_.CriteriaNames()
		
	def rowCount(self, index):
		return (len(self.altCrtMat_.AlternativeNames()) - 1 + 1) * (len(self.altCrtMat_.AlternativeNames()) - 1) / 2
	
	def columnCount(self, index):
		return len(self.HorizontalHeaderItems())
	
	def data(self, index, role):
		invalidRet = QtCore.QVariant()
		if role != QtCore.Qt.DisplayRole: return invalidRet
		if not index.isValid(): return invalidRet
		
		row, col = index.row(), index.column()
		altCount, crtCount = len(self.altCrtMat_.AlternativeNames()), len(self.altCrtMat_.CriterionNames())
		
		#首先计算是怎样的Rank Pair
		hiRank, lowRank = self._RowIdxToRankPair(row, altCount)
		hiRankAltId, lowRankAltId = map(self.Rank2Idx, (hiRank, lowRank))
		hiRankAltName, lowRankAltName = self.chgMat_.AlternativeNames()[hiRankAltId], self.chgMat_.AlternativeNames()[lowRankAltId]
		if col == 0:
			return QtCore.QVariant("%s - %s" % (hiRankAltName, lowRankAltName))
		if col == 1:
			return QtCore.QVariant("A%d - A%d" % (hiRank, lowRank))
		
		return QtCore.QVariant(str(self.chgMat_.RelatedCriteriaChangeMatrix()[(hiRank, lowRank)][col - 2]))
		
		return QtCore.QVariant()
	
	def headerData(self, section, orientation, role):
		if role != QtCore.Qt.DisplayRole: return QtCore.QVariant()
		if orientation == QtCore.Qt.Horizontal:
			return QtCore.QVariant(self.HorizontalHeaderItems()[section])
		return QtCore.QVariant()
	
	def flags(self, index):
		return QtCore.QAbstractTableModel.flags(self, index)
	
	def _RowIdxToRankPair(self, rowIdx, altCount):
		delta = lambda n, c: ((n+0.5)**2 - 4*(-0.5)*(-c))**0.5
		calcLvl = lambda n, c: (-(n+0.5)+delta(n, c))/(-1.0)
		
		totalCount = rowIdx + 1
		bottomCount = altCount - 1
		
		hiRank = math.ceil(calcLvl(bottomCount, totalCount))
		underLevelCount = hiRank - 1
		topCount = altCount - hiRank + 1

		underLevelItemCount = ( bottomCount + topCount ) * underLevelCount / 2.0
		lowRank = hiRank + (totalCount - underLevelItemCount)
		
		return int(hiRank), int(lowRank)

class WSMRelChgViewerModel(RelChgViewerModel):
	def __init__(self, parent = None):
		RelChgViewerModel.__init__(self, parent)
	
	def _LoadChgMat(self, altCrtMat):
		self.chgMat_ = WSM.ChangeMatrix.ChangeMatrix(altCrtMat)
		self.chgMat_.Compute()
		pass
	
	def Rank2Idx(self, rank):
		return self.altCrtMat_.IdxByRank(rank)
		pass
	
class WPMRelChgViewerModel(RelChgViewerModel):
	def __init__(self, parent = None):
		RelChgViewerModel.__init__(self, parent)
	
	def _LoadChgMat(self, altCrtMat):
		self.chgMat_ = WPM.ChangeMatrix.ChangeMatrix(altCrtMat)
		self.chgMat_.Compute()
		pass
	
	def Rank2Idx(self, rank):
		return self.chgMat_.RatioTable().Rank2Idx(rank)
		pass