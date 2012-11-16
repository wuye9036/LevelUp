#!/usr/bin/env python
# -*- coding: cp936 -*-

import sys, os
if __name__ == "__main__":
	sys.path.append(os.path.join(os.path.dirname(sys.argv[0]), ".."))

from PyExtLib.Matrix import *

class T:
	def __init__(self):
		self.mat_ = Matrix.FromArray2D([[1.0, 2.0],[3.0, 4.0]])
		
	def SetMatrix(self, arr):
		if True:
			self.mat_ = Matrix.FromArray2D(arr)
if __name__ == "__main__":
	t = T()
	t.SetMatrix([[3.0, 2.0],[3.0, 4.0]])
	
	print t.mat_