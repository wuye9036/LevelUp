#!/usr/bin/env python
# -*- coding: cp936 -*-

from LocationBuilderImpl.LocationBuilderSquare import *
from GPHelper.HelperFunctions import *
from GPHelper.Envelope import *

def EnumLocationBuilders():
	return ["Eight-Neighbor-Square", "Four-Neighbor-Square", "Triangular", "Hexagon"]

class ArcGISPointsBuilder:
	"""
	点构造器。
	依据指定的算法在一定的范围内构造一组有规律的点集，并输出到点要素类中。
	"""
	def __init__(self, boundaryFeatcls):
		"""
		描述：构造函数。
		参数：
			boundaryFeatcls：边界要素类名称，为面要素类。指定了生成点的范围。
		"""
		self.ptsBuilders_ = {
			"Square" : PointsBuilderAlgoSquare(),
			"Triangular": PointsBuilderAlgoTri(),
			"Hexagon" : PointsBuilderAlgoHex()
		}
		self.boundaryProp_ = get_featureclass_properties(boundaryFeatcls)
		self.curalgo_ = None
		
	def _GetEnvelope(self):
		"""
		描述：获得边界要素类的包围盒。用于确定生成点的坐标范围。
		返回值：
			env：Envelop的示例。参见Helper.Envelop
		"""
		agsEnv = self.boundaryProp_.lsEnvelope
		env = Envelope(agsEnv[0], agsEnv[1], agsEnv[2], agsEnv[3])
		return env
	
	#ptsBuilderAlgo: Name of points builder algorithm. eg: "Square" or "Triangle"
	def Build(self, ptsBuilderAlgoName, algoParams):
		"""
		描述：在指定范围内使用指定的算法构造一组点。
		参数：
			ptsBuilderAlgo：
				构造算法的名称。例如"Square"可以用于构造正方形的网格。
			algoParams：
				传入构造算法的参数。参见具体的算法。
				一元参数直接传入，多元参数以元组、列表或者字典的形式传入。
				例如在Square算法中，algoParams为单个参数，表示点之间的水平/垂直间隔。
		"""
		self.curalgo_ = self.ptsBuilders_[ptsBuilderAlgoName]
		self.curalgo_.Build(self._GetEnvelope(), algoParams)
		return
	
	def GetPoints(self):
		"""
		描述：获取全部点。
		返回值：点列表。格式：[(x0, y0), (x1, y1), ...]
		注意：
			尽管程序按照(x0,y0),(x1, y1)...的顺序进行保存，
			但是实际在要素类中不一定按照这样的顺序进行存储与编码OID；
			同时读取也没有办法保证就按照OID的顺序读取；
			OID也不能保证是连续递增的。
			因此将这一信息做持久化使用时需要谨慎。
		"""
		return self.curalgo_.GetPoints()
	
	def Save(self, oFeatcls):
		"""
		描述：将生成的点要素存储到要素类中
		参数：
			oFeatcls：
				输出的点要素类全路径
		返回：
			输出的点要素类全路径。
		"""
		sPath, sName = os.path.split(oFeatcls)
		return create_point_fc(sPath, sName, self.GetPoints(), self.boundaryProp_)
		
	
