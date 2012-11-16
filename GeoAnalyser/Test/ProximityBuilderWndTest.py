#!/usr/bin/env python
# -*- coding: cp936 -*-

import sys, os
if __name__ == "__main__":
	sys.path.append(os.path.join(os.path.dirname(sys.argv[0]), ".."))
from ProximityBuilderWindow import *

from PyQt4 import QtCore, QtGui

if __name__ == "__main__":
	app = QtGui.QApplication(sys.argv)
	wnd = ProximityBuilderWindow("J:/YangtzeDelta/Geodatabase/Zhejiang.mdb/Landscapes", 'C:/Documents and Settings/LightSky/桌面/TestProject/linguistic file.txt')
	wnd.ShowWidgetModal()