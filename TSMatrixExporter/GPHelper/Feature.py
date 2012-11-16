#!/usr/bin/env python
# -*- coding: cp936 -*-
from Enums import *
class Feature:
	def __init__(self, row, ownerSet):
		self.row_ = row
		self.ownerSet_ = ownerSet
		self.openMode_  = ownerSet.openMode_
		self.isOverwritten_ = False
		
		self.ownerFeatcls_ = ownerSet.owner_
		
	def __getitem__(self, key):
		try:
			return self.row_.GetValue(key)
		except:
			return None
	
	def __setitem__(self, key, value):	
		if self.openMode_ == OpenMode.ReadOnly:
			return
		try:
			self.row_.SetValue(key, value)
			self.isOverwritten_ = True
		except:
			pass
		
	def Shape(self):
		return self.__getitem__(self.ownerFeatcls_.ShapeFieldName())
	
	def ShapeTypeName(self):
		return self.ownerFeatcls_.ShapeTypeName()
	
	def ID(self):
		return self.__getitem__(self.ownerFeatcls_.IDFieldName())
	
	def SetShape(self, shape):
		self.__setitem__(self.ownerFeatcls_.ShapeFieldName(), shape)