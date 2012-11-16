#!/usr/bin/env python
# -*- coding: cp936 -*-

from HelperFunctions import *
import networkx

class NetworkDistanceMatrixBuilder:
	"""
	基于网络分析的距离矩阵计算。
	"""
	def __init__(self):
		self.graph_ = networkx.XGraph()
		self.distMat_ = {}
		self.ptCnt_ = 0
		return
	
	def GetFeatureCount(self, featcls):
		"""
		描述：获取要素类的要素数量。
		注意：该算法是读取所有的要素并计数的，因此效率较低。
		参数：
			featcls：需要统计要素数量的要素类。
		返回值：要素的数量，整数。
		"""
		retCnt = 0
		rows = pGP.SearchCursor(featcls)
		row = rows.next()
		while row:
			retCnt += 1
			row = rows.next()
		del rows
		del row
		
		return retCnt
		
	def Build(self, inFeatcls):
		"""
		描述：使用一个线要素类建立距离矩阵。
		注意：
			precondition：
				SRCPTID与DESTPTID源自于同一个点要素类；
				点要素类中要素的OID从1开始到n，n为点的数目；
				SRCPTID与DESTPTID与线段端点是对应的
			允许点要素类与线要素类构成的图中有孤立点与不联通的情况出现
		参数：
			inFeatcls：线要素类名称
		"""
		self._LoadFeatures(inFeatcls)
		self.nodeList_ = self.graph_.nodes()
		for ptId in self.graph_.nodes():
			self.distMat_[ptId] = networkx.path.single_source_dijkstra_path_length(self.graph_, ptId)
		return 
	
	def Save(self, ptCnt, oFileName):
		"""
		描述：
			保存距离矩阵到文件中。
			文件的首行提供了点的数量；
			若点的数量为n，则文件将以n行n列的形式保存为一个n*n的双精度浮点矩阵；
			行号为起点，列号为终点。
			若起止点号相同，则距离为0，若起止点间无通路，则通路大小设为1e300.
		注意：
			对无通路的距离设定为1e300，仍可能对结果产生较大的影响。
			precondition
				ptCnt为对应点要素类的要素数量相同。
		参数：
			ptCnt：图中节点数量（对应点要素类的数量）。
			oFileName：矩阵输出文件。
		"""
		f = open(oFileName, "w")
		
		f.write("%d" % ptCnt)
		for srcPtId in range(1, ptCnt + 1):
			for destPtId in range(1, ptCnt + 1):
				isHasKey = False
				if self.distMat_.has_key(srcPtId):
					if self.distMat_[srcPtId].has_key(destPtId):
						f.write( "%24.16e" % self.distMat_[srcPtId][destPtId])
						isHasKey = True
				if not isHasKey:
					f.write("%24.16e" % 1e200)
			f.write("\n")
		f.close()
		
		return
	
	def _LoadFeatures(self, lineFeatcls):
		"""
		描述：读取线要素类，并将线作为图的边加入图中。
		注意：线要素类需要符合一定的Schema。
		输入：
			lineFeatcls：线要素类名称。
		"""
		rows = pGP.SearchCursor(lineFeatcls)
		row = rows.next()
		
		while row:
			self.graph_.add_edge(int(row.SRCPTID), int(row.DESTPTID), row.Shape.Length)
			row = rows.next()
			
		del rows
		del row