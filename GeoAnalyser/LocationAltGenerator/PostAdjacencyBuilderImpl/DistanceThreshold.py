#!/usr/bin/env python
# -*- coding: cp936 -*-

from GPHelper.HelperFunctions import *

"""
邻接表后构造器的算法实现文件。
后构造器仅依赖点位坐标构造邻接关系。
"""

class DistanceThreshold:
	"""节点邻接表构造器，用于构造节点的邻接信息。
	使用Set -> Build -> Get的顺序获取信息。
	"""
	def __init__(self):
		return
	
	def SetXYs(self, pntsX, pntsY):
		"""
		描述：设置点位的XY坐标。
		返回值：无返回值
		参数：
			pntsX：点的X坐标。格式为{ptID0: CoordX0, ptID1: CoordX1, ...}
						ptIDn为点的ID。
						CoordXn为点ptIDn的X坐标。
			pntsY：格式同pntsX。
		"""
		self.pntsX_ = pntsX
		self.pntsY_ = pntsY
		
	def SetPoints(self, inFeatcls):
		"""
		描述：设置点要素类。
		返回值：无返回值
		参数：
			inFeatcls：点要素类的全路径名
		"""
		self.pntsX_, self.pntsY_ = build_value_lists(inFeatcls)
	
	def Build(self, distLimit):
		"""
		描述：构造邻接表
		返回值：无返回值
		参数：
			distLimit：距离阈值。如果两点距离小于该值则认为两点邻接。
		"""
		self.pntsNeighbors_ = build_neighbor_list(self.pntsX_, self.pntsY_, distLimit)
	
	def BuildWithDist(self):
		"""
		描述：构造带距离信息的邻接表。未实现。
		返回值：无
		"""
		return
	
	# 获得邻接表
	# 返回的邻接表格式：
	def GetAdjInfos(self):
		"""
		描述：获得构造完毕的邻接表
		返回值：
			返回一个邻接表。格式：{ sourceNodeId0 : [destNodeId0, destNodeId1, ...], ... }
			代表sourceNodeId0与destNodeId0/1等相邻。	
		"""
		return self.pntsNeighbors_
	
	# 返回邻接矩阵（暂时无法使用）
	def GetAdjMat(self):
		"""
		描述：返回带距离信息的邻接矩阵。未实现
		返回值：带距离信息的邻接矩阵。
		"""
		return