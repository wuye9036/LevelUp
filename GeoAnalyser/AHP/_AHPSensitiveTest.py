#!/usr/bin/env python
# -*- coding: cp936 -*-

import sys, os
sys.path.append(os.path.normpath(os.path.dirname(sys.argv[0]) + "/../"))

from Logic.SensitiveAnalyst.AltCrtMatrix import *
from Logic.SensitiveAnalyst.WSM.ChangeMatrix import *
from Logic.SensitiveAnalyst.WSM.Sensitive import *

if __name__ == "__main__":
	mat = AltCrtMatrix()
	mat.Load("C:/Documents and Settings/LightSky/桌面/TestProject/AlternativeCriteriaEvaluationTable.xml", "C:/Documents and Settings/LightSky/桌面/TestProject/Criteria.xml")
	
	cmat = ChangeMatrix(mat)
	cmat.Compute()
	print cmat.absCrtChangeMat_[(1,13)]
	
	sens = CriteriaSensitive(cmat)
	sens.Compute()
	print sens.crtSens_
	#print sens.altCriticallyDegrees_
	