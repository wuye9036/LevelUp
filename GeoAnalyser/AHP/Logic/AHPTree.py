#!/usr/bin/env python
# -*- coding: cp936 -*-
from PyQt4 import QtCore, QtGui, QtXml
from AHPTreeNode import AHPTreeNode
from xml.dom.minidom import *
from PyExtLib.Matrix import *

class AHPTree:
	"""
	AHP层次分析树。
	"""
	def __init__(self):
		self.root_ = AHPTreeNode(None, None, self)
		self.dict_ = {}
		return
	
	def _LoadNode(self, xmlElem):
		#构造属性
		nameAttr = xmlElem.attributeNode("name")
		wLocalAttr = xmlElem.attributeNode("local_weight")
		wGlobalAttr = xmlElem.attributeNode("global_weight")
		
		#构造AHPNode并给初值
		if nameAttr.isNull():	return
		retNode = AHPTreeNode(str(nameAttr.value()), None, self)
		if wLocalAttr.isNull():
			retNode.localWeight_ = 0.0
		else:
			retNode.localWeight_ = float(wLocalAttr.value())
		if wGlobalAttr.isNull():
			retNode.globalWeight_ = 0.0
		else:
			retNode.globalWeight_ = float(wGlobalAttr.value())
		
		#构造子节点
		arrFromDom = []
		childNodes = xmlElem.childNodes()
		for iChild in range(childNodes.length()):
			childNode = childNodes.at(iChild)
			if not childNode.isElement():
				continue
			
			#如果有矩阵则读取矩阵
			childElem = childNode.toElement()
			if str(childElem.tagName()).lower() == "matrix":
				matText = childElem.firstChild().toText().data()
				if not matText.isEmpty():
					arrFromDom = eval(str(matText))
				continue
			
			#忽略到未知的tag
			if str(childElem.tagName()).lower() != "feature":
				continue
			
			retNode.AddChild(self._LoadNode(childElem))
		
		#子树建成后更新矩阵	
		matSize = retNode.ahpMat_.GetMatrixSize()
		matFromDomSize = Matrix.GetArraySize(arrFromDom)
		if matSize == matFromDomSize:
			retNode.ahpMat_.SetComparisonMatrix(arrFromDom)
			retNode.ahpMat_.CalculateProperties()
		return retNode
	
	def _SaveNode(self, parentXmlNode, ahpNode, xmlDoc):
		xmlElem = xmlDoc.createElement("feature")
		if parentXmlNode:
			parentXmlNode.appendChild(xmlElem)
		
		xmlElem.setAttribute("name", ahpNode.name_)
		xmlElem.setAttribute("local_weight", str(ahpNode.localWeight_))
		xmlElem.setAttribute("global_weight", str(ahpNode.globalWeight_))

		if not ahpNode.IsLeaf():
			xmlMatElem = xmlDoc.createElement("Matrix")
			xmlMatText = xmlDoc.createTextNode(str(ahpNode.ahpMat_.mat_))
			xmlMatElem.appendChild(xmlMatText)
			xmlElem.appendChild(xmlMatElem)
			
		for ahpSubNode in ahpNode.GetChildren():
			self._SaveNode(xmlElem, ahpSubNode, xmlDoc)
		return xmlElem	
	
	def LoadXml(self, xmlFile):
		f = QtCore.QFile(xmlFile)
		if not f.open(QtCore.QIODevice.ReadOnly):
			return
		domDoc = QtXml.QDomDocument()
		if not domDoc.setContent(f):
			f.close()
			return
		f.close()
		
		domRoot = domDoc.documentElement()
		self.root_ = self._LoadNode(domRoot)
		
		#读完以后更新树
		self.root_.UpdateTree()
		
		self.dict_[self.root_.name_] = self.root_
		return
	
	def SaveXml(self, xmlFile):
		domDoc = QtXml.QDomDocument()
		rootElem = self._SaveNode(None, self.root_, domDoc)
		domDoc.appendChild(rootElem)
		f = open(xmlFile, "w")
		f.write(domDoc.toString())
		f.close()
			
	def SaveCriteriaToXmlFile(self, xmlFile):
		impl = DOMImplementation()
		dom = impl.createDocument(None, "Criteria", None)
		domElem = dom.documentElement
		
		for crt in self.dict_.values():
			if crt.IsLeaf():
				crtElem = dom.createElement("Criterion")
				domElem.appendChild(crtElem)
				crtElem.setAttribute("name", crt.name_)
				crtElem.appendChild(dom.createTextNode(str(crt.GlobalWeight())))
		
		f = open(xmlFile, 'w')
		dom.writexml(f, '', '\t', '\n')
		f.close()
		
	def SaveListFile(self, listFile):
		f = open(listFile, "w")
		for feat in self.dict_.values():
			if feat.IsLeaf():
				f.write("%s %f\n" % (feat.name_, feat.GlobalWeight()))
		f.close()
		
	def Root(self):
		return self.root_
		
	def FindNode(self, nodeName):
		return self.dict_[nodeName]
	def AllNodeList(self):
		return self.dict_.values()