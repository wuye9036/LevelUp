#!/usr/bin/env python
# -*- coding: cp936 -*-

from copy import *

def GetRank2IdxDict(v):
	rankDict = GetIdx2RankDict(v)
	retDict = {}
	for idx in rankDict:
		retDict[rankDict[idx]] = idx
	return retDict

def GetIdx2RankDict(v):
	"""
	获得list的排位列表，
	如原列表为[4.0, 2.0, 6.0]则返回。
	"""
	if v == None: return None
	if len(v) == 0: return []
	
	#将权重与标号对应，并按照权重进行排名。
	#得到排名后的标号-权重列表
	sortedList = [ (idx, v[idx]) for idx in range(len(v)) ]
	sortedList.sort(cmp=lambda lhs, rhs: cmp(rhs[1], lhs[1]))
	
	#得到排序后的标号列表
	return dict([(sortedList[i][0], i+1) for i in range(len(sortedList))])
	
class Matrix:
	@staticmethod
	def FromArray2D(arr2d):
		retMat = Matrix((1,1))
		retMat.arr2d_ = deepcopy(arr2d)
		return retMat
	
	"""二维矩阵"""
	def __init__(self, size):
		"""
		描述：初始化函数。
		参数：
			size: 要分配的矩阵大小.[rowsize, colsize]
		"""
		self.arr2d_ = self._AllocArray(size)
	
	def __getitem__(self, key):
		return self.arr2d_[key]
	
	def Size(self):
		return self.GetArraySize(self.arr2d_)
	
	@staticmethod
	def GetArraySize(arr2d):
		rowSize = len(arr2d)
		colSize = 0
		if rowSize > 0:
			colSize = len(arr2d[0])
		return (rowSize, colSize)
	
	def _AllocArray(self, size, initValue = 1.0):
		"""
		描述：矩阵分配函数。分配一个size大小的方阵
		参数：
			size: 要分配的矩阵大小.[rowsize, colsize]
		返回值：
			由嵌套List表示的Row-major Matrix。与numpy的格式兼容。
		"""
		return [ [1.0 for iCol in range(size[1])] for iRow in range(size[0])]
	
	def GetSub(self, row, col, size):
		"""
		描述：获得AHP矩阵的子矩阵
		参数：
			row, col：子矩阵的起始位置
			size：子矩阵的大小。[rowsize, colsize]
		返回值：
			size大小的方阵。
		"""
		retMat = self._AllocArray(size)
		for iRow in range(0, size[0]):
			for iCol in range(0, size[1]):
				retMat[iRow][iCol] = self.arr2d_[row+iRow][col+iCol]
		
		return retMat
	
	def SetSub(self, row, col, arr2d):
		"""
		描述：设置子矩阵。
		参数：
			row, col：子矩阵设置的起点。
			arr2d：需要设置的子矩阵，为方阵。
		"""
		size = self.GetArraySize(arr2d)
		for iRow in range(0, size[0]):
			for iCol in range(0, size[1]):
				self.arr2d_[row+iRow][col+iCol] = arr2d[iRow][iCol]
	
	def GetCol(self, col):
		return map(lambda lst: lst[col], self.arr2d_)
	
	def SetCol(self, col, colList):
		for iRow in range(len(self.arr2d_)):
			self.arr2d_[iRow][col] = colList[iRow]
	
	def __len__(self):
		return len(self.arr2d_)
	
	def __getitem__(self, key):
		return self.arr2d_[key]
	
	def __setitem__(self, key, lst):
		if len(lst) == self.Size()[1]:
			self.arr2d_[key] = lst
			
	def __mul__(self, v):
		if len(v) == self.Size()[1]:
			return	[sum(
					[row[i] * v[i] for i in range(len(v))]
					)
					 for row in self.arr2d_]
		
	def __rmul__(self, v):
		if len(v) == self.size()[0]:
			tmpMat = Matrix(self.Size())
			tmpMat.arr2d_ = zip(*self.arr2d_)
			return tmpMat.__mul__(v)
		
	def __str__(self):
		return str(self.arr2d_)
	
def MaxEigenvalue(mat, recycleBound = 10000):
	"""
	return value:
		(max eigenvalue, eigenvector of max eigenvalue)
	"""
	recycleCount = 0
	#除法
	vecdiv = lambda vec, s: [comp/float(s) for comp in vec]
	
	rowcnt, colcnt = mat.Size()
	if rowcnt <= 0 or colcnt <= 0 or rowcnt != colcnt:
		return (0.0, [])

	retVec = None
	retLambda = None
	v = [1.0 for i in range(colcnt)]
	u = v
	delta = 1.0
	maxLambda = None
	while delta > 1e-12:
		v = mat * u
		newMaxLambda = _MaxAbsComp(v)
		if maxLambda:
			delta = abs(newMaxLambda - maxLambda) / maxLambda
		maxLambda = newMaxLambda
		u = vecdiv(v, maxLambda)
		
		if recycleCount > recycleBound:
			break
		recycleCount += 1
		
	retLambda = maxLambda
	
	u = [abs(comp) for comp in u]
	retVec = vecdiv(u, sum(u))
	
	return (retLambda, retVec)

def PrintMatrix(mat):
	for i_row in range(mat.Size()[0]):
		print mat[i_row]
		
def _MaxAbsComp(vec):
	"""获取向量中的绝对值最大的分量"""
	maxAbsComp = vec[0]
	
	for curComp in vec:
		if abs(curComp) > abs(maxAbsComp):
			maxAbsComp = curComp
		
	return maxAbsComp