#!/usr/bin/env python
# -*- coding: cp936 -*-
import sys, os

if __name__ == "__main__":
	sys.path.append(os.path.join(os.path.dirname(sys.argv[0]), ".."))
	from AHPTreeEditor import *
	
	app = QtGui.QApplication(sys.argv)
	editor = AHPTreeEditor("C:/Documents and Settings/LightSky/桌面/TestProject/AHP.xml".decode('cp936'))
	editor.ShowWidgetModel()
	#sys.exit(app.exec_())