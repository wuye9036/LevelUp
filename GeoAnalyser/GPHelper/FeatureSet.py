#!/usr/bin/env python
# -*- coding: cp936 -*-

from Feature import *
from Enums import *

class FeatureSet:
	def __init__(self, cursor, openMode, owner):
		self.isValid_ = False
		
		if openMode not in OpenMode.EnumList(): return
		if cursor == None:	return
		
		self.owner_ = owner
		self.openMode_ = openMode
		self.cursor_ = cursor
		self.currentFeature_ = None
		self.isCurrentFeatureFresh_ = False #判断是否为新写入的Featureclass。只允许一次写入。
		self.isValid_ = True
		
	def Owner(self):
		return self.owner_
	def Flush(self):
		self.isCurrentFeatureFresh_ = False
		self._NextFeature()
			
	def SetInvalid(self):
		self.Flush()
		self.isValid_ = False
		self.cursor_ = None
		self.currentFeature_ = None
		self.isCurrentFeatureFresh_ = False
		
	def __iter__(self):
		return self
	
	def _NextWithSaveNothing(self):
		return self.cursor_.next()
	
	def _NextWithOverwritten(self):
		if self.currentFeature_:
			row = self.currentFeature_.row_
			if self.currentFeature_.isOverwritten_ :
				self.cursor_.UpdateRow(row)
		return self.cursor_.next()
	
	def _NextWithCreated(self):
		if self.currentFeature_:
			row = self.currentFeature_.row_
			if self.currentFeature_.isOverwritten_:
				self.cursor_.InsertRow(row)
		return self.cursor_.NewRow()
	
	def _NextFeature(self):
		#更新Row
		procChangedFunctions = {
			OpenMode.ReadOnly: self._NextWithSaveNothing,
			OpenMode.ReadWrite: self._NextWithOverwritten,
			OpenMode.WriteOnly: self._NextWithCreated
			}
		if self.isCurrentFeatureFresh_:
			return
		row = procChangedFunctions[self.openMode_]()
		self.isCurrentFeatureFresh_ = True
		if not row:
			self.currentFeature_ = None
		else:
			self.currentFeature_ = Feature(row, self)
	
	def next(self):
		if (not self.isValid_) or (not self.cursor_):
			self.SetInvalid()
			raise StopIteration
		
		self.isCurrentFeatureFresh_ = False
		self._NextFeature()
		if not self.currentFeature_:
			self.SetInvalid()
			raise StopIteration
		
		return self.currentFeature_
		