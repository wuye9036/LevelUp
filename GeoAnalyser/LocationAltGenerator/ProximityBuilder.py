#!/usr/bin/env python
# -*- coding: cp936 -*-

import sys, os, math
from xml.dom.minidom import *
from copy import *

from GPHelper.HelperFunctions import * 
from GPHelper.FeatureClass import *
from GPHelper.Log import *
from GPHelper.Shape import *
from GPHelper.Workspace import *

from ProximityBuilderImpl.LinguisticTable import *

#枚举可用的ProxmityBuilder
def EnumProximityBuilders():
	return ["Distance", "Fuzzy Grade"]#, "Arithmetic Level"]
	
def CreateProximityBuilder(algo, featCls):
	if algo == "Fuzzy Grade":
		return ArcGISFuzzyProximityBuilder(featCls, algo)
	if algo == "Distance":
		return ArcGISGeoProximityBuilder(featCls, algo)
	if algo == "Arithmetic Level":
		return ArcGISArithmeticLevelProximityBuilder(featCls, algo)
	if algo == "Geometric Level":
		return ArcGISGeometricLevelProximityBuilder(featCls, algo)
	if algo == "Manual Level":
		return ArcGISManualLevelProximityBuilder(featCls, algo)
	if algo == "Smooth Level":
		return ArcGISSmoothLevelProximityBuilder(featCls, algo)
	if algo == "Programmable":
		return ArcGISProgrammableLevelProximityBuilder(featCls, algo)
	return None

#计算临近度
class ArcGISGeoProximityBuilder:
	"""
	使用ArcGIS构造临近度信息。
	"""
	def __init__(self, inFeatcls, distAlgo = None):
		"""
		描述：构造函数。
		参数：
			inFeatcls：输入的点要素类型。
			distAlgo：空间距离求解算法。暂时无实现。
		"""
		self.distAlgo_ = distAlgo
		self.lingTbls_ = None
		
		self.inFeatcls_ = inFeatcls
		self.inFeatclsProp_ = get_featureclass_properties(inFeatcls)
		
		#Reschema the Dataset
		fuzzyField = "Fuzzy_Grade"
		if fuzzyField.upper() not in self.inFeatclsProp_.dcFields:
			if not self.inFeatclsProp_.dcFields.has_key(fuzzyField.upper()):
				pGP.AddField(inFeatcls, fuzzyField, "DOUBLE")
		
		return
	
	#检查linguistic file与要素类是否匹配。
	def Check(self, lingTbl):
		lingVals = lingTbl.Data().values()
		vecWs = Workspace(os.path.dirname(self.inFeatcls_))
		rasWs = Workspace(os.path.dirname(os.path.dirname(self.inFeatcls_)))
		retErrors = []
		for lingVal in lingVals:
			if lingVal.FeatType == "Vector":
				if not vecWs.IsInclude(lingVal.FeatCls):
					retErrors.append("feature class \" %s \" is not exist!" % lingVal.FeatCls)
			if lingVal.FeatType == "Raster":
				if not rasWs.IsInclude(lingVal.FeatCls):
					retErrors.append("raster \" %s \" is not exist!" % lingVal.FeatCls)
		return retErrors
	
	def Build(self, lingTbl):
		"""
		描述：
			根据linguistic file，计算点要素类中所有点到各个地理要素类的距离，
			并计算其模糊值。
		参数：
			linguisticFile：linguistic file。
		"""
		#read
		self.lingTbl_ = lingTbl
		multiFeatclsFuzzySet = {}
		
		#calculte fuzzy value of all feature classes 
		for lingValName in self.lingTbl_.Data().keys():
			lingVal = self.lingTbl_.Data()[lingValName]
			print "Now Analyse " + lingValName + "..."
			fuzzySet = self._ComputeProximity(self.inFeatcls_, lingVal)
			multiFeatclsFuzzySet[lingValName] = fuzzySet
		self.multiFeatclsFuzzySet_ = multiFeatclsFuzzySet
		
		return
	
	def SaveToFeatureClass(self, field = "Fuzzy_Grade"):
		"""
		描述：
			将计算所得的模糊值回写到输入的点要素类中。
		参数：
			field：回写的字段名。需要确保其存在。
		"""
		for featclsName in self.multiFeatclsFuzzySet_.keys():
			featclsFuzzys = self.multiFeatclsFuzzySet_[featclsName]
			copiedFeatcls = self._CopyFeatureClass(featclsName)
			fuzzyVals = featclsFuzzys
			
			oidField = pGP.describe(self.inFeatcls_).OIDFieldName
			rows = pGP.UpdateCursor(copiedFeatcls)
			row = rows.next()
			
			while row:
				row.SetValue(field, fuzzyVals[row.GetValue(oidField)])
				rows.UpdateRow(row)
				row = rows.next()
			
			del row
			del rows
		return
	
	#named constant for xml tags.
	xmlRootTag = "AlternativeCriterionEvaluationTable"
	criteriaListTag = "CriterionList"
	criteriaTag = "Criterion"
	matrixTag = "Matrix"
	altTag = "Alternative"
	
	def SaveToXMLFile(self, xmlFileName):
		#初始化dom及其根节点
		impl = getDOMImplementation()
		dom = impl.createDocument(None, self.xmlRootTag, None)
		criteriaListNode = dom.createElement(self.criteriaListTag)
		matrixNode = dom.createElement(self.matrixTag)
		dom.documentElement.appendChild(criteriaListNode)
		dom.documentElement.appendChild(matrixNode)
		
		altNodeDict = {}
		
		#对每个要素（即criteria）
		for criterianName in self.multiFeatclsFuzzySet_.keys():
			featclsFuzzys = self.multiFeatclsFuzzySet_[criterianName]
			
			#写criteria名称
			criteriaNode = dom.createElement(self.criteriaTag)
			criteriaNode.appendChild(dom.createTextNode(criterianName))
			criteriaListNode.appendChild(criteriaNode)
			
			#写matrix
			for altName in featclsFuzzys.keys():
				if altName not in altNodeDict:
					altNodeDict[altName] = dom.createElement(self.altTag)
					altNodeDict[altName].setAttribute("name", str(altName))
					matrixNode.appendChild(altNodeDict[altName])
					
				altNode = altNodeDict[altName]
				altCrtValNode = dom.createElement(self.criteriaTag)
				altCrtValNode.setAttribute("name", criterianName)
				
				altCrtValNode.appendChild(dom.createTextNode(str(featclsFuzzys[altName])))
				altNode.appendChild(altCrtValNode)
				
		f = open(xmlFileName, "w")
		dom.writexml(f, '', '\t', '\n')
		f.close()	
		
	def _CopyFeatureClass(self, lingVal):
		"""
		描述：根据linguistic value拷贝要素类。
		参数：
			lingVal : LingValue的实例。
		返回值：
			拷贝出的要素类名称。
		"""
		destFeatcls = self.inFeatcls_ + "_" + lingVal.FeatCls
		if pGP.Exist(destFeatcls):
			pGP.Delete_management(destFeatcls)
		pGP.Copy_management(self.inFeatcls_, destFeatcls, "")
		return destFeatcls
	
	def _ComputeGeoProximity(self, ptsFeatcls, lingVal):
		"""
		描述：
			用于从地理信息中提取临近信息。临近信息的单位由数据本身所决定
		输入参数：
			ptsFeatcls: 点要素类的名称
			lingVal: lingValue的实例
		返回值：
			{ptId : proximity_ptId, ...}
				# Assign the values of parameters
		"""
		
		# Convert linguistic features to points
		path, name = os.path.split(self.inFeatcls_)
		oFeatCls = os.path.join(path, lingVal.FeatCls)
		
		ptsX, ptsY = build_value_lists(ptsFeatcls)
		ptsNearDists = {}
		
		studyArea = []
		
		#提取地理信息。对Vector采用Distance，对于Raster采用Extract
		if lingVal.FeatType == "Vector":
			featCls = FeatureClass(oFeatCls)
			#对每个要素更新所有点的最近距离信息。
			for feat in featCls.Features():
				#点要素
				if feat.ShapeTypeName() == Shape.Point:
					shpPt = Point.FromFeature(feat)
					#求得点到点的距离，并更新每一个点的最近距离要素
					for ptKey in ptsX.keys():
						dist = ((ptsX[ptKey] - shpPt.X) ** 2 + (ptsY[ptKey] - shpPt.Y) ** 2) ** 0.5
						ptsNearDists[ptKey] = min(dist, ptsNearDists.get(ptKey, dist))
				#线和面要素
				else:
					shpLine = Line.FromFeature(feat)
					#分成多个segment，求每个segment到点的最近距离。
					for seg in shpLine.OuteriorSegments():
						studyArea = [(pt.X, pt.Y) for pt in seg]
					
						#长度小于3，需要进行逆转以后才能使用nearst_point
						if len(studyArea) < 3:
							studyAreaRev = copy(studyArea)
							studyAreaRev.reverse()
							studyArea += studyAreaRev[1:]
						
						#利用segment的最近距离更新全部的最近距离
						segNearestDists = nearest_point(studyArea, ptsX, ptsY)[0]
						for ptKey in segNearestDists.keys():
							dist = segNearestDists[ptKey]
							ptsNearDists[ptKey] = min(dist, ptsNearDists.get(ptKey, dist))
							
		if lingVal.FeatType == "Raster":
			#提取信息到临时要素类中
			tmpExtractedFeatcls = os.path.join(path, 'tmp_'+ name)
			rasterFeatCls = os.path.join(os.path.dirname(path), lingVal.FeatCls)
			
			logger.WriteLog("Extracting Values To Points...")
			pGP.CheckOutExtension("Spatial")
			pGP.ExtractValuesToPoints_sa(ptsFeatcls, rasterFeatCls, tmpExtractedFeatcls, "INTERPOLATE")
			
			#读取临时要素类信息
			logger.WriteLog("Read Raster Values...")
			tmpFeatcls = FeatureClass(tmpExtractedFeatcls)
			ptsNearDists = dict([(feat.ID(), feat["RASTERVALU"]) for feat in tmpFeatcls.Features()])
			
			if pGP.Exists(tmpExtractedFeatcls):
				pGP.Delete_management(tmpExtractedFeatcls)
		
		return ptsNearDists
	def _ComputeProximity(self, ptFeatcls, lingVal):
		return self._ComputeGeoProximity(ptFeatcls, lingVal)

class ArcGISFuzzyProximityBuilder(ArcGISGeoProximityBuilder):
	def __init__(self, inFeatcls, distAlgo = None):
		ArcGISGeoProximityBuilder.__init__(self, inFeatcls, distAlgo)
		
	def _ComputeFuzzy(self, ptsFeatcls, lingVal):
		"""
		描述：
			模糊值计算。
			由lingVal提供一个linguistic value。
			该方法将根据lingVal，选择要素类，计算ptsFeatcls上各个点至目标要素类的距离，
			并计算模糊度。
		输入参数：
			ptsFeatcls：点要素类名称。
			lingVal：LingValue的实例。
		返回值：
			返回所有点到一个要素类的模糊值。
			格式：
				[fuzzy0, fuzzy1, ...]
				其中fuzzyn为ptId为n的点的模糊值。
		"""
		# Assign the values of parameters
		retFuzzys = {}
		
		ptsNearDists = self._ComputeGeoProximity(ptsFeatcls, lingVal)
				
		# 使用提取出的数据计算模糊值
		# TODO: 可以使用Decorator模式
		ptIds = ptsNearDists.keys()
		
		for ptId in ptIds:
			dist = ptsNearDists[ptId]
			if self.distAlgo_ == "Distance":
				retFuzzys[ptId] = dist
			else:
				if (lingVal.FuzzyType == "Near"):
					fuzzyVal = near_membership_function(
							dist,
							lingVal.a1,
							lingVal.r1
							)
				else:
					fuzzyVal = close_to_membership_function(
							dist,
							lingVal.a1,
							lingVal.r1,
							lingVal.a2,
							lingVal.r2
							)
				retFuzzys[ptId] = fuzzyVal
		return retFuzzys
	
	def _ComputeProximity(self, ptsFeatcls, lingVal):
		return self._ComputeFuzzy(ptsFeatcls, lingVal)
	
class ArcGISArithmeticLevelProximityBuilder(ArcGISGeoProximityBuilder):
	def __init__(self, inFeatcls, distAlgo = None):
		ArcGISGeoProximityBuilder.__init__(self, inFeatcls, distAlgo)
	
	@staticmethod
	def minmax_reducer(minmax_val, val):
		if not minmax_val:
			return (val, val)
		if val < mimmax_val[0]:
			return (val, minmax_val[1])
		if mimax_val[1] < val:
			return (minmax_val[0], val)
		return minmax_val
		
	def _ComputeArithmeticLevel(self, ptsFeatcls, lingVal):
		geoProximities = self._ComputeGeoPriximity(self, ptsFeatcls, lingVal)
		min, max = reduce(minmax_reducer, geoProximities.values())
		
		