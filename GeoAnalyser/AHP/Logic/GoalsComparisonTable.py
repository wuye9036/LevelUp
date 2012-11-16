#!/usr/bin/env python
# -*- coding: cp936 -*-
from copy import *
from math import *
from PyExtLib.Matrix import *
import traceback
from random import *

class AHPComparisonTable:
	u"""
	评价要素对评价目标的影响表。
	"""
	def __init__(self, items, RIDict = None):
		"""
		描述：初始化函数。
		参数：
			items：AHP矩阵的要素名称列表
			RIList: 随即一致性指标列表字典
		"""
		self.items_ = items
		matSize = len(items)
		self.mat_ = Matrix((matSize, matSize))
		
		self.propNames_  = ['MaxEigenvalue', 'CI', 'RI', 'CR', 'Consistancy']
		
		self.RIDict_ = RIDict
		if self.RIDict_ == None:
			RIList = [
				0.00, 0.00, 0.58, 0.90, 1.12, #5个一组
				1.24, 1.32, 1.41, 1.46, 1.49,
				1.52, 1.54, 1.56, 1.58, 1.59
				]
			self.RIDict_ = dict([(i+1, RIList[i]) for i in range(len(RIList))])
			
		self._InitializeProperties()
		return
	
	def _InitializeProperties(self):
		self.weights_ = []
		self.ranks_ = []
		self.maxLambda_ = 0.0
		self.CI_ = 0.0
		self.RI_ = 0.0
		self.CR_ = 0.0
		self.isConsistancy_ = False
			
	def _UpdateByLTri(self):
		size = self.mat_.Size()
		if size[0] == 0: return
		for iRow in range(1, size[0]):
			for iCol in range(iRow):
				if abs(self.mat_[iRow][iCol] < 1e-16):
					self.mat_[iCol][iRow] = 0.0
				else:
					self.mat_[iCol][iRow] = 1.0 / self.mat_[iRow][iCol]
		for iElem in range(0, size[0]):
			self.mat_[iElem][iElem] = 1.0
			
	def _UpdateByUTri(self):
		size = self.mat_.Size()
		if size[0] == 0: return
		for iCol in range(1, size[0]):
			for iRow in range(iCol):
				if abs(self.mat_[iRow][iCol] < 1e-16):
					self.mat_[iCol][iRow] = 0.0
				else:
					self.mat_[iCol][iRow] = 1.0 / self.mat_[iRow][iCol]
		for iElem in range(0, size[0]):
			self.mat_[iElem][iElem] = 1.0
				
	def _MaxLambda(self):
		self.maxLambda_, self.weights_ = MaxEigenvalue(self.mat_)
		
	def _ComputeConsistancyProperties(self):
		matSize = len(self.items_)
		self.CI_ = 0.0
		self.RI_ = 0.0
		self.CR_ = 0.0
		if matSize > 2:
			self.CI_ = (self.maxLambda_ - matSize) / (matSize - 1)
			if matSize in self.RIDict_:
				self.RI_ = self.RIDict_[matSize]
				self.CR_ = self.CI_ / self.RI_
			else:
				self.RI_ = 1.60
				self.CR_ = self.CI_ / self.RI_
		self.isConsistancy_ = (self.CR_ <= 0.1)
	def _RankItems(self):
		"""
		根据权重对项目进行排名
		"""
		if not (self.weights_ and len(self.weights_) > 0):
			return
		
		#将权重与标号对应，并按照权重进行排名。
		#得到排名后的标号-权重列表
		sortedWeightList = [(idx, self.weights_[idx]) for idx in range(len(self.weights_))]
		sortedWeightList.sort(cmp=lambda lhs, rhs: cmp(rhs[1], lhs[1]))
		
		#得到排序后的标号列表
		idxSeq = [item[0] for item in sortedWeightList]
		#查找标号i在序列中的位置，便可得到该标号的rank
		self.ranks_ = [idxSeq.index(idx)+1 for idx in range(len(idxSeq))]
	
	def ComparisonMatrix(self):
		return self.mat_
	
	def SetComparisonMatrix(self, arr2d):
		if Matrix.GetArraySize(arr2d) == self.mat_.Size():
			self.mat_ = Matrix.FromArray2D(arr2d)
		
	def GetItemNames(self):
		return self.items_
	
	def GetMatrixSize(self):
		return self.mat_.Size()
	
	def AddItem(self, itemName):
		self.items_.append(itemName)
		oldMat = self.mat_
		self.mat_ = Matrix((len(self.items_), len(self.items_)))
		self.mat_.SetSub(0, 0, oldMat)
		return
	
	def RemoveItem(self, itemName):
		try: idx = self.items_.index(itemName)
		except: return
		
		oldSize = len(self.items_)
		newSize = oldSize - 1
		self.items_.remove(itemName)
		if newSize == 0: return
		
		oldSubMatLT = self.mat_.GetSub(0, 0, (idx, idx))
		oldSubMatRT = self.mat_.GetSub(0, idx+1, (idx, oldSize-idx-1))
		oldSubMatLB = self.mat_.GetSub(idx+1, 0, (oldSize-idx-1, idx))
		oldSubMatRB = self.mat_.GetSub(idx+1, idx+1, (oldSize-idx-1, oldSize-idx-1))
		
		self.mat_ = Matrix((newSize, newSize))
		
		self.mat_.SetSub(0, 0, oldSubMatLT)
		self.mat_.SetSub(0, idx, oldSubMatRT)
		self.mat_.SetSub(idx, 0, oldSubMatLB)
		self.mat_.SetSub(idx, idx, oldSubMatRB)
	
	def RenameItem(self, oldName, newName):
		oldIndex = self.items_.index(oldName)
		self.items_[oldIndex] = newName
		
	def SwapItem(self, lhsItemName, rhsItemName):
		try:
			lhsId = self.items_.index(lhsItemName)
			rhsId = self.items_.index(rhsItemName)
			if lhsId == rhsId: return False
		except:
			return False
		
		#Swap Matrix
		lhsRow = self.mat_[lhsId]
		lhsCol = self.mat_.GetCol(lhsId)
		rhsRow = self.mat_[rhsId]
		rhsCol = self.mat_.GetCol(rhsId)
		
		self.mat_[lhsId] = rhsRow
		self.mat_[rhsId] = lhsRow
		self.mat_.SetCol(lhsId, rhsCol)
		self.mat_.SetCol(rhsId, lhsCol)
		
		#Swap Items
		self.items_[rhsId] = lhsItemName
		self.items_[lhsId]= rhsItemName
		return True
	
	def CalculateProperties(self):
		try:
			self._MaxLambda()
			self._ComputeConsistancyProperties()
			self._RankItems()
		except:
			traceback.print_exc()
			self._InitializeProperties()
		
	def Weight(self, itemName):
		idx = self.items_.index(itemName)
		if idx >= len(self.weights_):
			self.weights_ = [0.0 for i in range(idx+1)]
		return self.weights_[idx]
	
	def Rank(self, itemName):
		idx = self.items_.index(itemName)
		if idx >= len(self.ranks_):
			self.ranks_ = [0 for i in range(idx+1)]
		return self.ranks_[idx]
	
	def MaxEigenvalue(self):
		return self.maxLambda_
	def CI(self):
		return self.CI_
	def RI(self):
		return self.RI_
	def CR(self):
		return self.CR_
	def Consistancy(self):
		return self.isConsistancy_
	def GetPropertyNames(self):
		return self.propNames_
	def GetProperty(self, propertyName):
		return getattr(self ,propertyName)()
	
class GoalsComparisonTable(AHPComparisonTable):
	def __init__(self, items, RIDict = None):
		AHPComparisonTable.__init__(self, items, RIDict)

	def RandomFill(self, randomGen):
		size = self.GetMatrixSize()[0]
		org_weights = [randomGen.GetRandom() for tmpIdx in range(size)]
		for iRow in range(size):
			for iCol in range(size):
				ratio = org_weights[iRow] / org_weights[iCol]
				if ratio > 1.0:
					int_ratio = round(ratio)
				else:
					int_ratio = 1.0 / round(1.0 / ratio)
				self.mat_[iRow][iCol] = int_ratio
				
		self.CalculateProperties()