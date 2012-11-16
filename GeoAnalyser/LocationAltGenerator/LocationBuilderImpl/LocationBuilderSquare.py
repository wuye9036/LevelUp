#!/usr/bin/env python
# -*- coding: cp936 -*-

import math

class PointsBuilderAlgoSquare:
	"""
	依据输入的Envelop，构造轴向对齐呈正方形的点集，并提供预构造的邻接表。
	"""
	def __init__(self):
		"""
		描述：初始化函数。
		"""
		self.pts_ = None
		self.adjMat_ = None
		self.adjBuilders_ = {
			"4-Link": self._Adj4Link,
			"8-Link": self._Adj8Link
			}
		
	def _MakePts(self, env, dist):
		"""
		描述：
			点生成程序的实现。
		参数：
			env：Envelop对象，指定了点的生成范围（轴向包围盒），所生成的点不会超过该范围。
			dist：正方形中相邻点之间轴向上的距离。
		"""
		dMaxX = env.MaxX
		dMinX = env.MinX
		dMaxY = env.MaxY
		dMinY = env.MinY
		fResolution = dist
		
		lNumXs = int(math.floor((dMaxX - dMinX) / fResolution)) + 1
		lNumYs = int(math.floor((dMaxY - dMinY) / fResolution)) + 1
	
		# create a list of points
		pPnts = []
		for iY in range (0, lNumYs):
			dY = dMinY + iY * fResolution
			dX = 0
			for iX in range (0, lNumXs):
				dX = dMinX + iX * fResolution
				p = (dX, dY)
				pPnts.append(p)
		
		self.pts_ = pPnts
	
	def _MakeAdjMat(self, adjBuilderName):
		"""
		描述：邻接矩阵预构造。尚无可用的实现。
		参数：
			adjBuilderName:
				邻接表预构造器的名称
		"""
		pFunc = self.AdjBuilders_[adjBuilderName]
		self.adjMat_ = pFunc()
		
	def _Adj4Link(self):
		"""
		描述：
			四方向的邻接表预构造器的实现。尚未实现。
		"""
		return
		
	def _Adj8Link(self):
		"""
		描述：
			八方向的邻接表预构造器的实现。尚未实现。
		"""
		return
	
	def GetAdjMat(self):
		"""
		描述：获得邻接矩阵。由于尚未实现预构造器，因此该方法总是返回空。
		"""
		return self.adjMat_
	
	def GetPoints(self):
		"""
		描述：返回生成的点列表。
		返回值：
			[ (x0, y0), (x1, y1), ... ]
		"""
		return self.pts_
	
	def GetAdjMatAlgos(self):
		"""
		描述：获得可用的邻接表的预构造算法名称列表。列表中的名称可用于Build的参数。
		返回值：
			可用的预构造算法名称列表。
			例如：["algo name1", "algo name2"]
		"""
		return self.adjBuilders_.keys()
		
	def Build(self, env, dist, adjMatName = None):
		"""
		描述：在指定的范围内按照一定的间隔构造呈正方形排列的点集。
		参数：
			env：Envelop的实例，指定了构造点的范围。
			dist：点之间的间隔（轴向上相邻点的距离）
			adjMatName：邻接表构造器的名称。
		返回值：无。产生的点集与邻接表使用Get函数获取。
		"""
		self._MakePts(env, dist)
		if adjMatName and self.adjBuilders_.has_keys():
			self._MakeAdjMat(adjMatName)

class PointsBuilderAlgoTri:
	"""
	依据输入的Envelop，构造底边与Env底边平行的正三角形集。
	"""
	def __init__(self):
		self.pts_ = None
	
	def _MakePts(self, env, dist):
		"""
		描述：在指定范围内生成点
		参数：
			env：envelop对象，指定点的生成范围
			dist：三角形的边长
		备注：由于三角形底边平行env的底边，行高为sqrt(3) / 2倍的边长
		"""
		
		rowEdgeRatio = math.sqrt(3.0) / 2.0 #行高和边长的比值
		rowHeight = dist * rowEdgeRatio
		
		#求行数和较宽列的点数
		rowPtCount = int(math.floor((env.MaxY - env.MinY) / rowHeight)) + 1
		majColPtCount = int(math.floor((env.MaxX - env.MinX) / dist)) + 1
		
		pnts = []
		
		for iRow in range(rowPtCount):
			curColPtCount = majColPtCount
			curOffset = 0.0
			if iRow % 2 == 1:
				curColPtCount = majColPtCount - 1
				curOffset = dist / 2.0
			for iCol in range(curColPtCount):
				curX = env.MinX + curOffset + iCol * dist
				curY = env.MinY + iRow * rowHeight
				pnts.append((curX, curY))
		
		self.pts_ = pnts
		
	def GetPoints(self):
		return self.pts_
	
	def Build(self, env, dist):
		"""
		描述：在指定的范围内按照一定的间隔构造呈正三角形方形排列的点集。
		参数：
			env：Envelop的实例，指定了构造点的范围。
			dist：三角形的边长
		返回值：无。产生的点集与邻接表使用Get函数获取。
		"""
		self._MakePts(env, dist)
		#if adjMatName and self.adjBuilders_.has_keys():
			#self._MakeAdjMat(adjMatName)

class PointsBuilderAlgoHex:
	def __init__(self):
		self.pts_ = None
	
	def _MakePts(self, env, dist):
		#建立方法在等边三角形的基础上筛点。
		
		rowEdgeRatio = math.sqrt(3.0) / 2.0 #行高和边长的比值
		rowHeight = dist * rowEdgeRatio
		
		#求行数和较宽列的点数
		rowPtCount = int(math.floor((env.MaxY - env.MinY) / rowHeight)) + 1
		majColPtCount = int(math.floor((env.MaxX - env.MinX) / dist)) + 1
		
		pnts = []
		
		for iRow in range(rowPtCount):
			curColPtCount = majColPtCount
			curOffset = 0.0
			clipPosOffset = 2
			
			if iRow % 2 == 1:
				curColPtCount = majColPtCount - 1
				curOffset = dist / 2.0
				clipPosOffset = 1
				
			for iCol in range(curColPtCount):
				if (iCol + clipPosOffset) % 3 != 0:
					curX = env.MinX + curOffset + iCol * dist
					curY = env.MinY + iRow * rowHeight
					pnts.append((curX, curY))
		
		self.pts_ = pnts
		
	def GetPoints(self):
		return self.pts_
	
	def Build(self, env, dist):
		self._MakePts(env, dist)