#!/usr/bin/env python
# -*- coding: cp936 -*-

import sys, os

sys.path.append(os.path.join(os.path.dirname(sys.argv[0]), ".."))
from AHPCmpTblEditor import *
from Logic.GoalsComparisonTable import *


if __name__ == "__main__":
	mat = GoalsComparisonTable(["item1", "item2", "item3", "item4", "item5", "item6", "item7"])
	app = QtGui.QApplication(sys.argv)
	editor = AHPCmpTblEditor(mat)
	editor.ShowWidget()
	sys.exit(app.exec_())