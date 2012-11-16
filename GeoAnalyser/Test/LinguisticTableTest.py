#!/usr/bin/env python
#

import sys, os
if __name__ == "__main__":
	sys.path.append(os.path.join(os.path.dirname(sys.argv[0]), ".."))

from PyExtLib.Matrix import *
from LocationAltGenerator.ProximityBuilderImpl.LinguisticTable import *

if __name__ == "__main__":
	lt = LinguisticTable("C:/Documents and Settings/LightSky/×ÀÃæ/TestProject/linguistic file.txt")
	lt.Save("C:/Documents and Settings/LightSky/×ÀÃæ/TestProject/linguistic file2.txt")
	pass