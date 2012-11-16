#!/usr/bin/env python
# -*- coding: cp936 -*-

import sys

from LocationAltGenerator.Model.LinguisticEditorModel import *
from LocationAltGenerator.UI.LinguisticEditor_ui import *
from LocationAltGenerator.LinguisticEditor import *

from LocationAltGenerator.ProximityBuilderImpl.LinguisticTable import *

if __name__ == "__main__":
	app = QtGui.QApplication(sys.argv)
	lingTbl = LinguisticTable("J:\\YangtzeDelta\\Geodatabase\\weights.txt")
	editor = LinguisticEditor(lingTbl)
	editor.ShowWidget()
	sys.exit(app.exec_())