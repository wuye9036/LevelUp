#!/usr/bin/env python

import sys, os, traceback
from GPHelper.HelperFunctions import *

from LocationAltGenerator import ProximityBuilder
from LocationAltGenerator.ProximityBuilder import *
from LocationAltGenerator.UI import LinguisticEditor_ui
from GPHelper.Log import logger

if __name__ == "__main__":
	
	pointsFeatcls = sys.argv[1]
	linguisticFile = sys.argv[2]
	weightFile = None #sys.argv[3]
	
	try:
		proxBuilder = ArcGISProximityBuilder(pointsFeatcls)
		proxBuilder.Build(linguisticFile, weightFile)
		logger.WriteLog("Write to linguistic file...")
		proxBuilder.SaveToXMLFile("C:\\test.xml")
		
	except Exception, e:
		traceback.print_exc()
		os.system("pause")
		raise
	
	os.system("pause")
	