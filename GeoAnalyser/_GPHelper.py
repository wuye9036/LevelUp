#!/usr/bin/env python
# -*- coding: cp936 -*-

import GPHelper
from GPHelper.HelperFunctions import *
from GPHelper import FeatureClass

if __name__ == "__main__":
	featClsName = 'J:\\YangtzeDelta\\Geodatabase\\Zhejiang.mdb\\Landscapes\\a_clipped'
	featCls = GPHelper.FeatureClass.FeatureClass(featClsName)
	if featCls.isValid_:
		print [feat.ID() for feat in featCls.Features()]
	else:
		print "Error!"