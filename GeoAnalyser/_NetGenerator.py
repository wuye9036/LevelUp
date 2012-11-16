#!/usr/bin/env python
from distance_mat import *
from postadjbuilder import *
from distance_mat import *
import sys

if __name__ == "__main__":
	pointFeatcls = sys.argv[1]
	lineFeatcls = sys.argv[2]
	matFile = sys.argv[3]
	
	distMatMaker = NetworkDistanceMatrix()
	ptCnt = distMatMaker.GetFeatureCount(pointFeatcls)
	distMatMaker.Build(lineFeatcls)
	distMatMaker.Save(ptCnt, matFile)
	
	#adjBuilder = ArcGISPostAdjBuilder(pointFeatcls)
	#adjBuilder.Build(80000)
	#adjBuilder.Save()