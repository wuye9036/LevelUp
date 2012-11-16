#!/usr/bin/env python
# -*- coding: cp936 -*-

from PostAdjacencyBuilderImpl.DistanceThreshold import *
from GPHelper.HelperFunctions import *

pGP.OverWriteOutput = True

class ArcGISPostAdjBuilder:
	"""基于ArcGIS的邻接信息构造器，实现可以配接不同的邻接矩阵算法。
	邻接信息将使用一个点要素类作为输入。
	如果两点存在邻接关系，则以这两个点作为端点构造一条线段，并保存到一个线要素类中。
	"""
	def __init__(self, inFeatcls, adjBuilderAlgo = DistanceThreshold()):
		"""
		描述：构造函数。
		参数：
			inFeatcls：
				用于构造邻接矩阵的点要素类的完整路径。
			adjBuilderAlgo：
				构造算法。算法在PostAdjBuilder_Algo文件中实现。
		"""
		self.inFeatcls_ = inFeatcls
		self.adjBuilderAlgo_ = adjBuilderAlgo
		self.inFeatclsProp_ = get_featureclass_properties(inFeatcls)
		
	def _ReadPoints(self):
		"""
		描述：
			从要素类中读取点信息。
		注意：
			self.pnts_格式为[(x0, y0), (x1, y1), ...]
		"""
		self.pnts_ = get_feature_points(self.inFeatcls_)
		
	def _BuildPointIdListFromNeighbors(self, neighbors):
		"""
		描述：利用邻接信息构造点ID列表。
		返回值：
			点列表。格式：[(ptID0, ptID1), (ptID2, ptID3), ... ]
			同一元组的两个元素有邻接关系。例如 (ptID0, ptID1) 表示ptID0与ptID1有邻接关系。
		"""
		retPtIdList = []
		for srcPtId, destPtIds in neighbors.iteritems():
			for destPtId in destPtIds:
				retPtIdList.append( (srcPtId, destPtId) )
		return retPtIdList
	
	def _BuildPointCoordListFromIdList(self, idList):
		"""
		描述：利用点列表构造坐标列表。
		注意：
			precondition：
				点要素的OID从1开始，标号是连续的；
				读取点时从1开始读取，OID为i的要素坐标一定存放在pnts_[i-1]处。
			postcondition：
				同precondition。
		参数：
			idList：同_BuildPointIdListFromNeighors的返回值。
		返回：
			返回点坐标的列表。格式：[ ((ptCoordX0, ptCoordY0), (ptCoordX1, ptCoordY1))]
			ptCoordX/Yn对应ptIDn的X/Y坐标。
			参见_BuildPointIdListFromNeighbors的返回值信息。
		"""
		retPtCoords = []
		for idPair in idList:
			retPtCoords.append(self.pnts_[idPair[0] - 1])
			retPtCoords.append(self.pnts_[idPair[1] - 1])
		return retPtCoords
	
	def _UpdateLineEndIds(self, oFeatcls):
		"""
		描述：
			更新连线的端点信息。
		注释：
			邻接连线信息的保存使用了create_line_fc函数。
			函数仅保存了线段本身，但没有保存端点信息。
			因此这里添加一个保存遍，用于将线段的端点保存到要素信息中。
			Precondition：
				对线段要素的写顺序与之前保存几何信息时的写顺序相同。
		参数：
			oFeatcls：需要更新的要素类全路径。与Save中的要素类相同。
		"""
		pGP.RefreshCatalog(oFeatcls)
		
		if pGP.Exists(oFeatcls):
			pGP.AddField_management(oFeatcls, "SRCPTID", "long", 9)
			pGP.AddField_management(oFeatcls, "DESTPTID", "long", 9)
			
		rows = pGP.UpdateCursor(oFeatcls)
		row = rows.next()
		pntIdCur = 0
		while row:
			row.SetValue("SRCPTID", self.neighborPntIds_[pntIdCur][0])
			row.SetValue("DESTPTID", self.neighborPntIds_[pntIdCur][1])
			rows.UpdateRow(row)
			pntIdCur += 1
			row = rows.next()
		del row
		del rows
		return
	
	def Build(self, params):
		"""
		描述：构造邻接信息。
		参数：
			params为参数，以元组、字典、或者列表的形式提供。一元的参数不需要写成元组。
		"""
		self._ReadPoints()
		self.adjBuilderAlgo_.SetPoints(self.inFeatcls_)
		self.adjBuilderAlgo_.Build(params)
		neighbors = self.adjBuilderAlgo_.GetAdjInfos()
		self.neighborPntIds_ = self._BuildPointIdListFromNeighbors(neighbors)
		self.neighborPnts_ = self._BuildPointCoordListFromIdList(self.neighborPntIds_)
		return
	
	def Save(self, oFeatcls = None):
		"""
		描述：
			将构造完毕的邻接信息保存到线要素名称中。
		参数：
			oFeatcls：
				输出要素类名称。
				可选参数。如果不设置或者设为空，
				则利用输入的点要素类名称构造输出的线要素类名称。
				如果点要素类为$(point), 那么默认的线要素类名称为$(point)_network。
		返回值：
			返回输出要素类的名称。
		"""
		if oFeatcls == None:
			oFeatclsPath, inFeatclsName = os.path.split(self.inFeatcls_)
			oFeatclsName = inFeatclsName + "_network"
			oFeatcls = os.path.join(oFeatclsPath, oFeatclsName)
			
		oFeatclsPath, oFeatclsName = os.path.split(oFeatcls)
		
		create_line_fc(
			oFeatclsPath,
			oFeatclsName,
			self.neighborPnts_,
			self.inFeatclsProp_
			)
		
		self._UpdateLineEndIds(oFeatcls)
		return oFeatcls
	
	def GetAdjMat(self):
		return