#!/usr/bin/env python
# -*- coding: cp936 -*-

from PyExtLib.Matrix import *
	
class ChangeMatrix:
	epsilon = 1e-12
	def __init__(self, altCrtMatrix):
		self.altCrtMatrix_ = altCrtMatrix
		self.absCrtChangeMat_ = {}
		self.relCrtChangeMat_ = {}
		self.absAltChangeMat_ = {}
		self.relAltChangeMat_ = {}
		return

	def Compute(self):
		#计算Priorities并排序
		self.altCrtMatrix_.Compute()
		
		altNames = self.altCrtMatrix_.AlternativeNames()
		crtNames = self.altCrtMatrix_.CriterionNames()
		
		priors = self.altCrtMatrix_.Priorities()
		rank2idxDict = GetRank2IdxDict(priors)
		priors.sort(cmp=lambda lhs, rhs: cmp(rhs, lhs))
		sortedPriors = priors
		
		#两两比较，计算反转所需的绝对差值
		altCount = len(altNames)
		crtCount = len(crtNames)
		
		for hiAltRank in range(1, altCount):
			for lowAltRank in range(hiAltRank+1, altCount+1):
				#分配空间
				self.absCrtChangeMat_[(hiAltRank, lowAltRank)] = [None for i in range(crtCount)]
				self.relCrtChangeMat_[(hiAltRank, lowAltRank)] = [None for i in range(crtCount)]
				self.absAltChangeMat_[(hiAltRank, lowAltRank)] = [None for i in range(crtCount)]
				self.relAltChangeMat_[(hiAltRank, lowAltRank)] = [None for i in range(crtCount)]
				self.absAltChangeMat_[(lowAltRank, hiAltRank)] = [None for i in range(crtCount)]
				self.relAltChangeMat_[(lowAltRank, hiAltRank)] = [None for i in range(crtCount)]
				
				hiRankIdx = rank2idxDict[hiAltRank]
				lowRankIdx = rank2idxDict[lowAltRank]
				priorDiff = priors[lowAltRank-1] - priors[hiAltRank-1]
				
				for criteriaIdx in range(len(crtNames)):
					
					#计算准则上的差值
					lowRankAltCrtVal = self.altCrtMatrix_.AltCrtValue(lowRankIdx, criteriaIdx)
					hiRankAltCrtVal = self.altCrtMatrix_.AltCrtValue(hiRankIdx, criteriaIdx)
					crtDiff = lowRankAltCrtVal - hiRankAltCrtVal
					
					#求出解算评价要素敏感性所需要的绝对变化与相对变化量
					crtWeight = self.altCrtMatrix_.CrtPriority(criteriaIdx)
					absCrtChange = self._ComputeCrtAbsoluteChange(priorDiff, crtDiff, crtWeight)
					relCrtChange = None
					if absCrtChange != None: relCrtChange = absCrtChange / crtWeight * 100.0
					
					self.absCrtChangeMat_[(hiAltRank, lowAltRank)][criteriaIdx] = absCrtChange
					self.relCrtChangeMat_[(hiAltRank, lowAltRank)][criteriaIdx] = relCrtChange
					
					#求出解算评价目标敏感性所需要的绝对变化与相对变化量
					absAltChange = self._ComputeAltAbsoluteChangeForAHP(-priorDiff, crtWeight, hiRankAltCrtVal, lowRankAltCrtVal)
					absAltChangeRev = self._ComputeAltAbsoluteChangeForAHP(priorDiff, crtWeight, lowRankAltCrtVal, hiRankAltCrtVal)
					self.absAltChangeMat_[(hiAltRank, lowAltRank)][criteriaIdx] = absAltChange
					self.absAltChangeMat_[(lowAltRank, hiAltRank)][criteriaIdx] = absAltChangeRev
					relAltChange = None
					relAltChangeRev = None
					if absAltChange != None: relAltChange = absAltChange /  hiRankAltCrtVal * 100.0
					if absAltChangeRev != None: relAltChangeRev = absAltChangeRev / lowRankAltCrtVal * 100.0
					
					self.relAltChangeMat_[(hiAltRank, lowAltRank)][criteriaIdx] = relAltChange
					self.relAltChangeMat_[(lowAltRank, hiAltRank)][criteriaIdx] = relAltChangeRev
	
	def AbstractCriteriaChangeMatrix(self):
		return self.absCrtChangeMat_
	
	def AbstractAlternativeChangeMatrix(self):
		return self.absAltChangeMat_
	
	def RelatedCriteriaChangeMatrix(self):
		return self.relCrtChangeMat_
	
	def RelatedAlternativeChangeMatrix(self):
		return self.relAltChangeMat_
	
	def CriteriaNames(self):
		return self.altCrtMatrix_.CriterionNames()
	
	def AlternativeNames(self):
		return self.altCrtMatrix_.AlternativeNames()
	
	def _ComputeCrtAbsoluteChange(self, priorDiff, crtDiff, crtWeight):
		#criteria的差值接近0时不可反转
		if abs(crtDiff) < self.epsilon: return None
		deltaWeight = priorDiff / crtDiff
		#delta比criteria的weight大时，不可反转
		if deltaWeight > crtWeight: return None
		return deltaWeight
	
	#Formula from: Traintaphyllow(1997), 16a, p.30
	def _ComputeAltAbsoluteChangeForWSM(self, priorDiff, crtWeight, altCrtValue0, altCrtValue1):
		if abs(altCrtValue0) < self.epsilon: return None
		deltaWeight = priorDiff / crtWeight
		if deltaWeight > altCrtValue0: return None
		return deltaWeight
	
	#Formula from: Traintaphyllow(1997), 17a, p.30
	def _ComputeAltAbsoluteChangeForAHP(self, priorDiff, crtWeight, altCrtValue0, altCrtValue1):
		if abs(altCrtValue0) < self.epsilon or abs(altCrtValue1) < self.epsilon:
			return None
		deltaWeight = priorDiff / (priorDiff + crtWeight*(altCrtValue1 - altCrtValue0 + 1))
		if deltaWeight > altCrtValue0: return None
		return deltaWeight
	
	def Output(self):
		#for key in self.absCrtChangeMat_:
		#	print "%s : %s" % (key, self.absCrtChangeMat_[key])
		#print "\n\n"
		#for key in self.relCrtChangeMat_:
		#	print "%s : %s" % (key, self.relCrtChangeMat_[key])
		#for key in self.absAltChangeMat_:
			#print "%s: %s" % (key, self.absAltChangeMat_[key])
		#print "\n\n"
		#for key in self.relAltChangeMat_:
			#print "%s: %s" % (key, self.relAltChangeMat_[key])
		pass