#!/usr/bin/env python
# -*- coding: cp936 -*-

from xml.dom.minidom import *
from PyExtLib.Matrix import *

class WSMComputePriorityStrategy:
	def Priorities(self, altCrtMat):
		return altCrtMat.mat_ * altCrtMat.criteria_;
	
class WPMComputePriorityStrategy:
	def Priorities(self, altCrtMat):
		retPriorities = [1.0 for i in len(altCrtMat.altNames_)]
		for idxAlt in range(0, len(retPriorities)):
			retPriorities[idxAlt] = reduce(
				lambda rslt, item: rslt * item,
				[altCrtMat.AltCrtValue(idxAlt, idxCrt) ** altCrtMat.CrtPriority(idxCrt)
					for idxCrt in range(len(altCrtMat.crtNames_))]
				)
def Priorities(altCrtMat, strategyName):
	objTable = {
		"WSM": WSMComputePriorityStrategy(),
		"WPM": WPMComputePriorityStrategy()
	}
	return objTable[strategyName].Priorities(altCrtMat)
							 
class AltCrtMatrix:
	altcrtRootTag = "AlternativeCriterionEvaluationTable"
	crtRootTag = "Criteria"
	criterionNamesTag = "CriterionList"
	criterionNameTag = "Criterion"
	criteriaNameAttrTag = "name"
	matrixTag = "Matrix"
	altTag = "Alternative"
	altNameAttrTag = "name"
	altcrtFactorTag = "Criterion"
	altcrtFactorNameAttrTag = "name"
	
	def __init__(self):
		self.altNames_ = []
		self.crtNames_ = []
		self.mat_ = Matrix((0, 0))
		self.priorities_ = []
		self.criteria_ = []
		self.rank2idxDict_ = {}
		self.idx2rankDict_ = {}
		return
	
	def Load(self, FileName, criteriaFileName):
		altcrtDomRoot = parse(FileName)
		self._LoadFromDomTree(altcrtDomRoot)
		
		crtDomRoot = None
		if criteriaFileName != None:
			crtDomRoot = parse(criteriaFileName)
		self._LoadCriteria(crtDomRoot)
		
		self.Compute()
	
	def Save(self, fileName):
		dom = getDOMImplementation().createDocument(None, self.altcrtRootTag, None)
		root = dom.documentElement
		self._SaveToDomTree(dom, root)
		ofile = open(fileName, 'w')
		dom.writexml(ofile, '', '\t', '\n')
		ofile.close()
		
	def _GetText(self, nodelist):
		rc = ""
		for node in nodelist:
			if node.nodeType == node.TEXT_NODE:
				rc = rc + node.data
		return rc.strip()

	def _LoadCriteria(self, domRoot):
		if domRoot == None:
			self.criteria_ = [0.0 for crtName in self.crtNames_]
			return
		root = domRoot.getElementsByTagName(self.crtRootTag)[0]
		criteriaDict = {}
		
		#解析
		for criterionNameNode in root.getElementsByTagName(self.criterionNameTag):
			criterionName = criterionNameNode.getAttribute(self.criteriaNameAttrTag)
			criterionWeight = float(self._GetText(criterionNameNode.childNodes))
			criteriaDict[criterionName] = criterionWeight
		
		self.criteria_ = [criteriaDict.get(crtName, 0) for crtName in self.crtNames_]
	
	def _LoadFromDomTree(self, domRoot):
		root  = domRoot.getElementsByTagName(self.altcrtRootTag)[0]
		criteriaNamesNode = root.getElementsByTagName(self.criterionNamesTag)[0]
		
		#解析评价指标名称
		self.crtNames_ = [self._GetText(criterionNameNode.childNodes) 
			for criterionNameNode in criteriaNamesNode.getElementsByTagName(self.criterionNameTag)]
		evalCount = len(self.crtNames_)
		
		#解析评价目标-评价指标矩阵
		altMatrixNode = root.getElementsByTagName(self.matrixTag)[0]
		altNodes = altMatrixNode.getElementsByTagName(self.altTag)
		altCount = len(altNodes)
		
		self.priorities_ = [0.0 for i in range(altCount)]
		self.mat_ = Matrix((altCount, evalCount))
		self.altNames_ = ["" for i in range(altCount)]
		
		#读取矩阵
		i_row = 0
		for altNode in altNodes:
			self.altNames_[i_row] = altNode.getAttribute(self.altNameAttrTag)
			#读取alternative对应每个criteria的值
			for altcrtFactorNode in altNode.getElementsByTagName(self.altcrtFactorTag):
				factor = float(self._GetText(altcrtFactorNode.childNodes))
				altcrtFactorName = altcrtFactorNode.getAttribute(self.altcrtFactorNameAttrTag)
				i_col = self.crtNames_.index(altcrtFactorName)
				self.mat_[i_row][i_col] = factor
			i_row += 1
			
	def _SaveToDomTree(self, dom, domRoot):
		#创建评价指标名称节点
		criteriaNamesNode = dom.createElement(self.criterionNamesTag)
		domRoot.appendChild(criteriaNamesNode)
		
		#添加名称项
		for evalName in self.crtNames_:
			evalNameNode = dom.createElement(self.criterionNameTag)
			evalNameTextNode = dom.createTextNode(evalName)
			evalNameNode.appendChild(evalNameTextNode)
			criteriaNamesNode.appendChild(evalNameNode)
		
		#创建评价矩阵节点
		altMatrixNode = dom.createElement(self.matrixTag)
		for altName in self.altNames_:
			altNode = dom.createElement(self.altTag)
			altNode.setAttribute(self.altNameAttrTag, altName)
			#创建每个目标的评价值列表
			for i_eval in range(len(self.crtNames_)):
				altcrtFactorNode = dom.createElement(self.altcrtFactorTag)
				altcrtFactorNode.setAttribute(self.altcrtFactorNameAttrTag, self.crtNames_[i_eval])
				i_alt = self.altNames_.index(altName)
				altcrtFactorTextNode = dom.createTextNode(str(self.mat_[i_alt][i_eval]))
				altcrtFactorNode.appendChild(altcrtFactorTextNode)
				altNode.appendChild(altcrtFactorNode)
			altMatrixNode.appendChild(altNode)
		domRoot.appendChild(altMatrixNode)
		return
		
	def Compute(self, priorityModelName = "WSM"):
		#self.priorities_ = self.mat_ * self.criteria_
		self.priorities_ = Priorities(self, priorityModelName)
		self.rank2idxDict_ = GetRank2IdxDict(self.priorities_)
		self.idx2rankDict_ = GetIdx2RankDict(self.priorities_)
		
	def Criteria(self):
		return self.criteria_
	def CrtPriority(self, crtIndex):
		return self.criteria_[crtIndex]
	def CriterionNames(self):
		return self.crtNames_
	
	def AlternativeNames(self):
		return self.altNames_
	
	def AltCrtValue(self, altIndex, crtIndex):
		try:	
			return self.mat_.arr2d_[altIndex][crtIndex]
		except:
			return None
	def Priorities(self):
		return self.priorities_
	
	def PriorityByName(self, altName):
		try:
			return self.priorities_[self.altNames_.index(altName)]
		except:
			return None
		
	def PriorityByIndex(self, altIndex):
		try:
			return self.priorities_[altIndex]
		except:
			return None
		
	def RankByIdx(self, altIndex):
		return self.idx2rankDict_.get(altIndex, None)
	
	def IdxByRank(self, rank):
		return self.rank2idxDict_.get(rank, None)