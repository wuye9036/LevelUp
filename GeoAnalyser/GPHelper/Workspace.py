#!/usr/bin/env python

import os
from HelperFunctions import *

class Workspace:
	def __init__(self, workspace):
        	self.Load(workspace)
	
	def Load(self, workspace):
		if pGP.Exists(workspace):
			self.workspace_ = workspace
		else:
			self.workspace_ = None
			
	def EnumFeatureClass(self, wildCard = "", featType = "", isFullName = False):
		ret = []
		oldws = pGP.workspace
		pGP.workspace = self.workspace_
		featClsLst = pGP.ListFeatureClasses(wildCard, featType)
		featClsLst.reset()
		featClsName = featClsLst.next()
		while featClsName:
			ret.append(featClsName)
			featClsName = featClsLst.next()
			
		if isFullName:
			ret = [self.workspace_+item for item in ret]
		if oldws:
			pGP.workspace = oldws
		return ret
	
	def Path(self):
		return self.workspace_
	
	def FullName(self, featName):
		return os.path.join(self.workspace_, featName)
	
	def IsInclude(self, featclsName):
		return pGP.Exists(os.path.join(self.workspace_, featclsName))
		
	def Delete(self, featclsName):
		if self.IsInclude(featclsName):
			pGP.Delete_management( self.FullName(featclsName) )
			
	def CreateFeatureClass( self, featclsName, *args ):
		validFeatclsName = pGP.ValidateTableName(featclsName, self.workspace_)
		if pGP.describe(self.workspace_).WorkspaceType == "FileSystem":
			validFeatclsName = validFeatclsName + ".shp"
		self.Delete(validFeatclsName)
		pGP.CreateFeatureClass_management( self.workspace_, validFeatclsName, *args )
		return self.FullName( validFeatclsName )
