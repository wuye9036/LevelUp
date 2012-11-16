#!/usr/bin/env python
# -*- coding: cp936 -*-

import unittest, sys, os

if __name__ == "__main__":
	sys.path.append(os.path.join(os.path.dirname(sys.argv[0]), ".."))

from AHP.Logic.GoalsComparisonTable import GoalsComparisonTable
from PyExtLib.Matrix import *

class AHPMatrixTestCase(unittest.TestCase):
	def setUp(self):
		self.setUp_1()
	
	def setUp_1(self):
		self.goalCmpTbl_ = GoalsComparisonTable(["Item1", "Item2", "Item3", "Item4", "Item5", "Item6", "Item7"])
		self.comMat_ = [[0.0 for i in range(7) ] for j in range(7)]
		self.refs_ = [0.092, 0.129, 0.123, 0.097, 0.169, 0.169, 0.022]
		
		#初始化矩阵
		self.comMat_[0][1] = 0.746
		self.comMat_[0][2] = 0.707
		self.comMat_[0][3] = 1.046
		self.comMat_[0][4] = 0.493
		self.comMat_[0][5] = 0.456
		self.comMat_[0][6] = 0.488
		
		self.comMat_[1][2] = 0.923
		self.comMat_[1][3] = 1.561
		self.comMat_[1][4] = 0.802
		self.comMat_[1][5] = 0.794
		self.comMat_[1][6] = 0.542
		
		self.comMat_[2][3] = 1.188
		self.comMat_[2][4] = 0.804
		self.comMat_[2][5] = 0.624
		self.comMat_[2][6] = 0.523
		
		self.comMat_[3][4] = 0.511
		self.comMat_[3][5] = 0.611
		self.comMat_[3][6] = 0.545
		
		self.comMat_[4][5] = 1.119
		self.comMat_[4][6] = 0.642
		
		self.comMat_[5][6] = 0.697
		
		self.goalCmpTbl_.SetComparisonMatrix(self.comMat_)
		self.comMat_ = self.goalCmpTbl_.mat_
		self.isCalculated_ = False
	
	def setUp_2(self):
		self.goalCmpTbl_ = GoalsComparisonTable(["Item1", "Item2", "Item3", "Item4", "Item5", "Item6"])
		self.comMat_ = self.goalCmpTbl_.mat_
		self.refs_ = [0.1947, 0.1479, 0.2373, 0.0738, 0.0471, 0.2992]
		
		#初始化矩阵
		self.comMat_[0][1] = 2.0
		self.comMat_[0][2] = 0.5
		self.comMat_[0][3] = 3.0
		self.comMat_[0][4] = 5.0
		self.comMat_[0][5] = 0.5
		
		self.comMat_[1][2] = 0.5
		self.comMat_[1][3] = 3.0
		self.comMat_[1][4] = 4.0
		self.comMat_[1][5] = 0.5
		
		self.comMat_[2][3] = 3.0
		self.comMat_[2][4] = 4.0
		self.comMat_[2][5] = 0.5
		
		self.comMat_[3][4] = 2.0
		self.comMat_[3][5] = 1.0/3
		
		self.comMat_[4][5] = 0.25
		
		self.isCalculated_ = False
		
	def setUp_random(self):
		self.goalCmpTbl_ = GoalsComparisonTable(["Item1", "Item2", "Item3", "Item4", "Item5", "Item6", "Item7"])
		self.goalCmpTbl_.AutoFill()
	
	def testUpdateByUTri(self):
		self.goalCmpTbl_._UpdateByUTri()
		
		for iRow in range(self.comMat_.Size()[0]):
			for iCol in range(self.comMat_.Size()[1]):
				self.assertAlmostEqual(self.comMat_[iRow][iCol] * self.comMat_[iCol][iRow], 1.0, 15)
		pass
	
	def calculateProperties(self):
		if not self.isCalculated_:
			self.goalCmpTbl_._UpdateByUTri()
			self.goalCmpTbl_.CalculateProperties()
			self.isCalculated_ = True
			
	def testPriorities(self):
		self.calculateProperties()
		self.assertAlmostEqual(sum(self.goalCmpTbl_.weights_), 1.0, 15)
		
	def testPrioritiesSum(self):
		self.calculateProperties()
		self.assertEqual([round(w, 3) for w in self.goalCmpTbl_.weights_], self.refs_)
	
if __name__ == "__main__":
	goalCmpTbl = GoalsComparisonTable(["Item1", "Item2", "Item3", "Item4", "Item5", "Item6", "Item7"])
	goalCmpTbl.AutoFill()
	print goalCmpTbl.ComparisonMatrix()
	#unittest.main()