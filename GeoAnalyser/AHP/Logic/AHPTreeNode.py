#!/usr/bin/env python
# -*- coding: cp936 -*-
from copy import *

from GoalsComparisonTable import GoalsComparisonTable
class AHPTreeNode:
	def __init__(self, name, parent, owner = None):
		self.parent_ = parent
		self.owner_ = owner
		self.children_ = {}
		self.name_ = name
		self.localWeight_ = 0.0
		self.globalWeight_ = 0.0
		self.rank_ = 0
		self.ahpMat_ = GoalsComparisonTable([])
		self.indexesDict_  =\
					  {
					"name": (self.Name, self.SetName),
					"overall weight": (self.GlobalWeight, None),
					"local weight": (self.LocalWeight, None),
					"rank":(self.Rank, None)
					   }
		self.indexesNames_ =\
			[
			"Name",
			"Local Weight",
			"Overall Weight",
			"Rank"
			 ]
		return
	
	def Update(self):
		"""
		更新当前节点（不计算矩阵）
		"""
		parent = self.parent_
		
		if not parent:
			#顶层节点的局部和全局权重均为1
			self.localWeight_ = 1
			self.globalWeight_ = 1
		else:	
			parentAHPMat = parent.ahpMat_
			self.localWeight_ = parentAHPMat.Weight(self.name_)
			self.rank_ = parentAHPMat.Rank(self.name_)
			self.globalWeight_ = parent.globalWeight_ * self.localWeight_
	
	def UpdateTree(self):
		"""
		更新以该节点为根的子树
		"""
		self.Update()
		if not self.IsLeaf():
			childNodes = self.GetChildren()
			for childNode in childNodes:
				childNode.UpdateTree()
				
	def IsNodeNameExists(self, nodeName):
		return nodeName in self.owner_.dict_
	
	def AddChild(self, node):
		node.parent_ = self
		node.owner_ = self.owner_
		if not self.IsNodeNameExists(node.name_):
			self.children_[node.name_] = node
			self.owner_.dict_[node.name_] = node
			self.ahpMat_.AddItem(node.name_)
		
	def RemoveChild(self, nodeName):
		if self.IsNodeNameExists(nodeName):
			del self.children_[nodeName]
			del self.owner_.dict_[nodeName]
			self.ahpMat_.RemoveItem(nodeName)
	
	def SwapChildById(self, lhsId, rhsId):
		names = deepcopy(self.ahpMat_.GetItemNames())
		self.ahpMat_.SwapItem(names[lhsId], names[rhsId])
		
	def SwapChildByItem(self, lhsItem, rhsItem):
		self.ahpMat_.SwapItem(lhsItem, rhsItem)
		
	def GetChild(self, nodeName, hasIndirectChild = False):
		if nodeName in self.children_:
			return self.children_[nodeName]
		
		if hasIndirectChild:
			for node in self.children_.values():
				retNode = node.FindChild(self, nodeName, hasIndirectChild)
				if retNode: return retNode

		return
	
	def RenameChild(self, oldName, newName):
		if newName == oldName\
			or (newName in self.owner_.dict_)\
			or (oldName not in self.children_):
			return
		
		curNode = self.GetChild(oldName)
		#修改node自身的名字
		curNode.name_ = newName
		
		#修改本地子节点索引
		del self.children_[oldName]
		del self.owner_.dict_[oldName]
		
		self.children_[newName] = curNode
		self.owner_.dict_[newName] = curNode
		
		self.ahpMat_.RenameItem(oldName, newName)
		
	def Rename(self, newName):
		if newName == self.name_\
			or (newName in self.owner_.dict_):
			return False
		
		if self.parent_ != None:
			self.parent_.RenameChild(self.name_, newName)
		else:
			del self.owner_.dict_[self.name_]
			self.owner_.dict_[newName] = self
			self.name_ = newName
		
		return True
	
	def GetChildNames(self):
		return self.ahpMat_.items_
	
	def GetChildren(self, childNames = None):
		try:
			if childNames == None: childNames = self.GetChildNames()
			retChildren =  map(lambda item: self.children_[item], childNames)
			return retChildren
		except:
			return
		
	def LocalWeight(self):
		return self.localWeight_
	
	def GlobalWeight(self):
		return self.globalWeight_
	def GoalsCmpTblText(self):
		return str(self.ahpMat_.mat_)
	
	def Name(self):
		return self.name_
	def Rank(self):
		return self.rank_
	def SetName(self, name):
		try:
			return self.Rename(name)
		except:
			return False
	
	def IsLeaf(self):
		return len(self.children_) == 0
	
	def GetPropertyName(self, indexId):
		return self.indexesNames_[indexId]
	
	def GetPropertyNames(self):
		return self.indexesNames_
	
	def GetPropertiesCount(self):
		return len(self.indexesDict_)
	
	def GetPropertyById(self, indexId):
		return GetPropertyByName(self.indexesNames_[indexId])
	
	def GetPropertyByName(self, indexName):
		return self.indexesDict_[indexName.lower()][0]()
	
	def SetPropertyById(self, indexId, value):
		self.SetPropertyByName(self.indexesNames_[indexId], value)
		
	def SetPropertyByName(self, indexName, value):
		self.indexesDict_[indexName.lower()][1](value)