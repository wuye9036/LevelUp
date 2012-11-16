#!/usr/bin/env python
# -*- coding: cp936 -*-
import copy

class AlternativeSensitive:
	epsilon = 1e-307
	def __init__(self, changeMatrix):
		self.chgMat_ = changeMatrix
		self.altCriticallyDegrees_ = []
		self.altSens_ = []
		return

	def Compute(self):
		relChgMat = self.chgMat_.RelatedAlternativeChangeMatrix()
		crtCount = len(self.chgMat_.CriteriaNames())
		altCount = len(self.chgMat_.AlternativeNames())
		
		self.altCriticallyDegrees_ = [[None for i in range(crtCount)] for j in range(altCount)]
		self.altSens_ = [[0.0 for i in range(crtCount)] for j in range(altCount)]
		
		#更新sens和critically degrees
		for rankPair in relChgMat.keys():
			majorRank = rankPair[0]
			secondRank = rankPair[1]
			for crtIndex in range(crtCount):
				if relChgMat[rankPair][crtIndex] == None:
					continue
				if self.altCriticallyDegrees_[majorRank-1][crtIndex] == None\
				or abs(self.altCriticallyDegrees_[majorRank-1][crtIndex][0]) > abs(relChgMat[rankPair][crtIndex]):
					criticalDeg = abs(relChgMat[rankPair][crtIndex])
					self.altCriticallyDegrees_[majorRank-1][crtIndex] = (criticalDeg, secondRank)
					criticalDeg += self.epsilon
					self.altSens_[majorRank-1][crtIndex] = (1.0 / criticalDeg, secondRank)
	
	def AlternativeSensitives(self):
		return self.altSens_
	
	def CriticalDegrees(self):
		return self.altCriticallyDegrees_
	
class CriteriaSensitive:
	"""
	评价要素的敏感性分析
	"""
	epsilon = 1e-307
	def __init__(self, changeMatrix):
		self.chgMat_ = changeMatrix
		self.crtSens_ = []
		
	def Compute(self):
		relChgMat = self.chgMat_.RelatedCriteriaChangeMatrix()
		crtCount = len(self.chgMat_.CriteriaNames())
		altCount = len(self.chgMat_.AlternativeNames())
		self.crtSens_ = [None for i in range(crtCount)]
		
		for altPair in relChgMat.keys():
			for i_crt in range(crtCount):
				self._UpdateCriteriaSens(relChgMat, altPair, i_crt)
	
	def CriteriaSensitives(self):
		return self.crtSens_
	
	def _UpdateCriteriaSens(self, relatedChangeMatrix, altPair, crtIdx):
		if relatedChangeMatrix[altPair][crtIdx] != None:
			relChg = abs(relatedChangeMatrix[altPair][crtIdx]) + self.epsilon
			if self.crtSens_[crtIdx] == None:
				self.crtSens_[crtIdx] = 1.0 / relChg
			else:
				self.crtSens_[crtIdx] = max(self.crtSens_[crtIdx], 1.0 / relChg)