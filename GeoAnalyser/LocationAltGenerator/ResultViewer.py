#!/usr/bin/env python
# -*- coding: cp936 -*-

from HelperFunctions import *

class ArcGISPointsDisplay:
	def __init__(self, resultFile):
		self._LoadResultFile(resultFile)
		
	def _LoadResultFile(self, resultFile):
		f = open(resultFile, "r")
		comment = f.readline()
		if comment.strip().lower() == "unconvergence":
			return
		self.ptEcos_ = None
		ptcnt = int(f.readline())
		for ptId in range(1, ptcnt+1):
			ptEcos_[ptId] = float(f.readline())
		f.close()
		
	def SaveToFeatcls(self, oFeatcls, ecoField = "ECOINDEX"):
		if not self.ptEcos_:	return
		if not pGP.Exists(oFeatcls): return
		prop = get_featureclass_properties(oFeatcls)
		if prop.sShapeType != "point": return
		
		if ecoField not in prop.dcFields:
			pGP.AddField_management(oFeatcls, ecoField, "DOUBLE")
			
		rows = pGP.UpdateCursor(pFeatcls)
		row = rows.next()
		while row:
			ptId = int(row.GetValue(prop.sFID))
			if ptId not in self.ptEcos_:	break
			row.SetValue(oFeatcls, self.ptEcos_[ptId])
			row = rows.next()
			
		del row
		del rows
		
	def _LoadResultFile(self, resultFile):
		return