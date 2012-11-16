#!/usr/bin/env python
# -*- coding: cp936 -*-
from GPHelper.HelperFunctions import pGP

class ArcGISLocationClipFilter:
	"""
	基于ArcGIS的裁切实现。
	"""
	def __init__(self, boundaryFeatcls):
		"""
		描述：初始化函数。
		参数：
			boundaryFeatcls：边界面要素类。
		"""
		self.boundaryFeatcls_ = boundaryFeatcls
		self.destFeatcls_ = None
		
	def Filtrate(self, srcFeatcls, destFeatcls = None):
		"""
		描述：对输入的要素类依据已设定的边界要素类进行裁剪，并输出到新要素类中。
		参数：
			srcFeatcls：供裁剪的要素类。
			destFeatcls：裁剪的结果要素类。如果该项为None，程序将自动为输出类命名。
		返回：
			无返回值，如果需要获取输出要素类名称，使用GetClipped函数。
		"""
		# create an output feature class
		envelopeFC = "TEMP_Envelope"
		self.destFeatcls_ = destFeatcls
		if destFeatcls == None or destFeatcls == "":
			self.destFeatcls_ = srcFeatcls + "_filtered"
		
		pGP.MakeFeatureLayer_management(self.boundaryFeatcls_, envelopeFC, True)
		pGP.Clip_analysis(srcFeatcls, envelopeFC, self.destFeatcls_)
		pGP.Delete_management(envelopeFC)
		
	def GetFilteredFeatureClassName(self):
		return self.destFeatcls_