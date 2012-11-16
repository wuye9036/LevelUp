#!/usr/bin/env python

from GPHelper.FeatureClass import *
from MainDocument import *
from GPHelper.Workspace import *
from networkx import *

class DistanceMatrix:
	def __init__(self, ws):
		self.graph_ = XGraph()
	
	def Load(self, featClsName):
		featcls = FeatureClass(ws.FullName(mainDoc.featClsName))
		if not featcls:
			return
		for feat in featcls.Features():
			srcId = float(feat["SRCPTID"])
			destId = float(feat["DESTPTID"])
			edgeLen = float(feat.Shape().Length)
			self.graph_.add_edge(srcId, destId, edgeLen)
		self._NetworkAnalysis()
	
	def Matirx(self, ptCount):
		#按照 Point ID 重新组织self.dists_为二维矩阵并输出
		infinite = 1e300
		
		retMat = []
		for i in range(1, ptCount+1):
			retMatRow = []
			for j in range(i+i, ptCount+1):
				if self.dists_.has_key(i) and self.dists_[i].has_key(j):
					retMatRow.append(dists[i][j])
				else:
					retMatRow.append(1e300)
				retMat.append( retMatRow )
		
		return retMat
	
	def _NetworkAnalysis(self):
		self.dists_ = {}
		for node in self.graph_.nodes():
			self.dists_[node] = networkx.path.single_source_dijkstra_path_length(self.graph_, node)
		pass