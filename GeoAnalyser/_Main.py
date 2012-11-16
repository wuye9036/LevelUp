#!/usr/bin/env python


import sys, traceback, os
try:
	from MainWindow import *

	# read arguments
	datasetPath = sys.argv[1]
	
	app = QtGui.QApplication(sys.argv)
	
	mainDlg = MainWindow(datasetPath)
	mainDlg.ShowWidgets()
	
	app.exec_()
	#raise Exception

except:
	traceback.print_exc()
	os.system("pause")
	raise