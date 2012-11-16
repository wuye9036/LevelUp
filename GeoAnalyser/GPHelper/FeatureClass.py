#!/usr/bin/env python
# -*- coding: cp936 -*-

from HelperFunctions import *
from FeatureSet import *
from Enums import *

import os
import os.path

class FeatureClass:
	def __init__(self, featclsName):
		self._Reset()
		self.path_ = featclsName
		
		if pGP.Exists(featclsName):
			desc = pGP.Describe(featclsName)
			fcprops = get_featureclass_properties(featclsName)
			if desc.DatasetType.lower() != "featureclass":
				return
			
			self.isValid_ = True
			
			self.idFieldName_ = fcprops.sFID
			self.shapeFieldName_ = fcprops.sShapeField
			self.shapeType_ = fcprops.sShapeType
			self.spatialRef_ = fcprops.pSpatialRef
			
			self.dir_ = os.path.split(self.path_)[0]
			self.baseName_ = os.path.split(self.path_)[1]
			self.count_ = pGP.GetCount_management(self.path_)
			self.desc_ = desc
	
	def _Reset(self):
		self.isValid_ = False
		
		self.dir_ = None
		self.baseName_ = None
		self.count_ = None
		
		self.idFieldName_ = None
		self.shapeFieldName_ = None
		self.shapeType_ = None
		self.spatialRef_ = None
		
		self.desc_ = None
		
		self.currentFeatureSet_ = None
		
	def Directory(self):
		return self.dir_
	
	def BaseName(self):
		return self.baseName_
	
	def ShapeTypeName(self):
		return self.shapeType_
	
	def SetShapeTypeName(self, typeName):
		if self.isValid_:
			return False
		self.shapeType_ = typeName
		return True
	
	def ShapeFieldName(self):
		return self.shapeFieldName_
	
	def IDFieldName(self):
		return self.idFieldName_
	
	def SpatialRef(self):
		return self.spatialRef_
	
	def SetSpatialRef(self, spatialRef):
		self.spatialRef_ = spatialRef
		
	def ArcGISDescription(self):
		return self.desc_
	def AddField(self, field_name, data_type, *args):
                validFieldName = pGP.ValidateFieldName(field_name)
		pGP.AddField_management( self.path_, validFieldName, data_type, *args )
		return validFieldName
	def Features(self, mode = None, filterExpression = None):
		"""
		获取一个包含多个Feature的迭代器。
		参数：
			mode: 打开方式。
				OpenMode.ReadOnly: 以pGP.SearchCursor的方式打开
				OpenMode.WriteOnly: 以pGP.InsertCursor的方式打开
				OpenMode.ReadWrite: 以pGP.UpdateCursor的方式打开
			filter：集合过滤器。参见ESRI的WhereClause选项
		"""
		if not self.isValid_:
			return FeatureSet(None, OpenMode.Invalid, self)

		if self.currentFeatureSet_:
			self.currentFeatureSet_.SetInvalid()
		if mode == None:
			mode = OpenMode.ReadOnly
		if mode == OpenMode.ReadOnly:
			if filterExpression:
				rows = pGP.SearchCursor(self.path_, filterExpression)
			else:
				rows = pGP.SearchCursor(self.path_)
			self.currentFeatureSet_ = FeatureSet(rows, mode, self)
		elif mode == OpenMode.WriteOnly:
			if filterExpression:
				rows = pGP.InsertCursor(self.path_, filterExpression)
			else:
				rows = pGP.InsertCursor(self.path_)
			self.currentFeatureSet_ = FeatureSet(rows, mode, self)
		elif mode == OpenMode.ReadWrite:
			if filterExpression:
				rows = pGP.UpdateCursor(self.path_, filterExpression)
			else:
				rows = pGP.UpdateCursor(self.path_)
			self.currentFeatureSet_ = FeatureSet(rows, mode, self)
	
		return self.currentFeatureSet_
	
	def Flush(self):
		if self.currentFeatureSet_:
			self.currentFeatureSet_.Flush()
		
	def Count(self):
		if self.isValid_:
			return self.count_
