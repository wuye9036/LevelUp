#!/usr/bin/env python
# -*- coding: cp936 -*-

class LinguisticValue:
	def __init__(self, vals):
		if len(vals) != 5 and len(vals) != 7:
			logger.WriteErr("Linguistic 文件有误！")
			sys.exit(-1)
		self.FeatCls = vals[0]
		self.FeatType = vals[1]
		self.FuzzyType = vals[2]
		self.a1 = float(vals[3])
		self.r1 = float(vals[4])
		if len(vals) > 5:
			self.a2 = float(vals[5])
			self.r2 = float(vals[6])
		return
	
	@staticmethod
	def DefaultValue(name):
		return LinguisticValue([name, "Vector", "Near", 0.0, 0.0])

class LinguisticTable:
	def __init__(self, linguisticFile):
		self.Load(linguisticFile)
	
	def Load(self, linguisticFile = None):
		if not linguisticFile:
			linguisticFile = self.lingFileName_
			
		self.lingTbl_ = {}
		f = open(linguisticFile, "r")
		lines = f.readlines()
		f.close()
		
		for line in lines:
			lineItems = [lineItem for lineItem in line.split(" ") if lineItem]
			self.lingTbl_[lineItems[0]] = LinguisticValue(lineItems)
		
		self.lingFileName_ = linguisticFile
		
	def Save(self, linguisticFile = None):
		if not linguisticFile:
			linguisticFile = self.lingFileName_
		
		f = open(linguisticFile, "w")
		for lingVal in self.lingTbl_.values():
			lingValList = [lingVal.FeatCls, lingVal.FeatType, lingVal.FuzzyType, lingVal.a1, lingVal.r1]
			if lingVal.FuzzyType == "CloseTo":
				lingValList += [lingVal.a2, lingVal.r2]
			f.write(reduce(lambda item, s: str(item) + " " + str(s), lingValList) + "\n")
		f.close()
		
		self.lingFileName_ = linguisticFile
		
	def Data(self):
		return self.lingTbl_
		