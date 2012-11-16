#!/usr/bin/env python
# -*- coding: cp936 -*-

from PyExtLib.Matrix import *
from AHP.Logic.GoalsComparisonTable import *
from xml.dom.minidom import *

def dyn_import(name):
	mod = __import__(name)
	components = name.split('.')
	for comp in components[1:]:
		mod = getattr(mod, comp)
	return mod

class AltCmpTable(AHPComparisonTable):
	@staticmethod
	def FromArcGISFeatureClass(featClsName, crtName):
		epsilon = 1e-307
		
		featcls = dyn_import("GPHelper.FeatureClass").FeatureClass(featClsName)
		idList, valList = [], []
		for feat in featcls.Features():
			idList.append(feat.ID())
			valList.append(feat["FUZZY_GRADE"])
			
		cmpTbl = AltCmpTable(crtName, idList)
		cmpArr = Matrix.AllocArray2D((len(idList), len(idList)))
		
		for rowIdx in range(len(idList)):
			for colIdx in range(rowIdx, len(idList)):
				cmpArr[rowIdx][colIdx] = (valList[rowIdx] + epsilon) / (valList[colIdx] + epsilon)
				cmpArr[colIdx][rowIdx] = 1.0 / (cmpArr[rowIdx][colIdx] + epsilon)
		
		cmpTbl.SetComparisonMatrix(cmpArr)
		cmpTbl.CalculateProperties()
		
		return cmpTbl
	
	@staticmethod
	def FromAltCrtTable(altCrtMat, crtName):
		epsilon = 1e-307
		
		crtNames = altCrtMat.CriterionNames()
		altNames = altCrtMat.AlternativeNames()
		
		crtIdx = crtNames.index(crtName)
		if crtName not in crtNames:
			return None
		
		cmpTbl = AltCmpTable(crtName, altNames)
		cmpMat = Matrix((len(altNames), len(altNames)))
		valList = [altCrtMat.AltCrtValue(altNames.index(altName), crtIdx) for altName in altNames]
		
		for rowIdx in range(len(altNames)):
			for colIdx in range(rowIdx, len(altNames)):
				cmpMat[rowIdx][colIdx] = (valList[rowIdx] + epsilon) / (valList[colIdx] + epsilon)
				cmpMat[colIdx][rowIdx] = 1.0 / (cmpMat[rowIdx][colIdx] + epsilon)
		
		cmpTbl.SetComparisonMatrix(cmpMat.arr2d_)
		cmpTbl.CalculateProperties()
		
		return cmpTbl
	
	def __init__(self, crtName, items, RIDict = None):
		AHPComparisonTable.__init__(self, items, RIDict)
		self.crtName_ = crtName
		
	def CriterionName(self):
		return self.crtName_
	
	def LoadFromXml(self, xmlFileName):
		dom = parse(xmlFileName)
		root = dom.documentElement()
		crtNameNode = root.getElementsByTagName("Criterion")
		crtName = str(root.childNodes()[0].data).strip()
		altListNode = root.getElementsByTagName("AlternativeList")
		altNames = [str(altNameNode.childNodes()[0].data()).strip() for altNameNode in altListNode.getElementsByTagName("Alternative")]
		cmpArrNode = root.getElementsByTagName("Array")
		cmpArr = eval(cmpArrNode.childNodes()[0].data())
		
		self.crtName_ = crtName
		self.items_ = altNames
		self.mat_ = Matrix.FromArray2D(cmpArr)
		return None
		
	def SaveToXml(self, xmlFileName):
		try:
			impl = DOMImplemetation()
			dom = impl.createDocument(None, "AltCmpTable", None)
			root = dom.documentElement()
			
			crtNameNode = dom.createElement("Criterion")
			crtNameNode.appendChild(dom.createTextNode(self.crtName_))
			root.appendChild(crtNameNode)
			
			altListNode = dom.createElement("AlternativeList")
			root.appendChild(altListNode)
			for altName in self.items_:
				altNode = dom.createElement("Alternative")
				altNode.appendChild(dom.createTextNode(altName))
				altListNode.appendChild(altName)
				
			cmpArrNode = dom.createElement("Array")
			root.appendChild(cmpArrNode)
			cmpArrNode.appendChild(dom.createTextNode(str(self.mat_)))
			
			dom.writexml(xmlFileName, '', '\t', '\n')
			
		except:
			pass