#!/usr/bin/env python
# -*- coding: cp936 -*-
if __name__ == "__main__":
	import sys, os
	sys.path.append(os.path.join(os.path.dirname(sys.argv[0]), ".."))
from AHP.Logic.SensitiveAnalyst.AltCrtMatrix import *
from AHP.Logic.SensitiveAnalyst import WPM

	
if __name__ == "__main__":
	mat = AltCrtMatrix()
	path = "C:/Documents and Settings/LightSky/桌面/TestProj/"
	mat.Load(path+"AlternativeCriteriaEvaluationTable.xml", path + 'Criteria.xml')
	cmat = WPM.ChangeMatrix.ChangeMatrix(mat)
	cmat.Compute()
	print cmat.RelatedAlternativeChangeMatrix()
	