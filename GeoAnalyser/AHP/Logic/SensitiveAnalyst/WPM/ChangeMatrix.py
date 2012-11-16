#!/usr/bin/env python
# -*- coding: cp936 -*-

from PyExtLib.Matrix import *
import math

class RatioTable:
	def __init__(self, altCrtMatrix):
		self.altCrtMatrix_ = altCrtMatrix
		self.WPMPriority_ = []
		self.pairRatio_ = {}
	
	def Compute(self):
		#Update WPM Priority
		altNames = self.altCrtMatrix_.AlternativeNames()
		crtNames = self.altCrtMatrix_.CriterionNames()
		
		self.WPMPriority_ = [1.0 for i in range(len(altNames))]
		for idxAlt in range(0, len(self.WPMPriority_)):
			self.WPMPriority_[idxAlt] = reduce(
				lambda rslt, item: rslt * item,
				[self.altCrtMatrix_.AltCrtValue(idxAlt, idxCrt) ** self.altCrtMatrix_.CrtPriority(idxCrt)
					for idxCrt in range(len(crtNames))]
				)
			
		rank2IdxDict = GetRank2IdxDict(self.WPMPriority_)
		idx2RankDict = GetIdx2RankDict(self.WPMPriority_)
		
		self.rank2Idx_ = rank2IdxDict
		self.idx2Rank_ = idx2RankDict
		
		#Update Pair PriorityRatio
		for hiRank in range(1, len(altNames)+1):
			for lowRank in range(hiRank+1, len(altNames)+1):
				hiRankIdx = rank2IdxDict[hiRank]
				lowRankIdx = rank2IdxDict[lowRank]
				self.pairRatio_[(hiRank, lowRank)] = self.WPMPriority_[hiRankIdx] / self.WPMPriority_[lowRankIdx]
	
	def WPMPriorities(self):
		return self.WPMPriority_
	
	def RatioByRank(self, hiRank, lowRank):
		return self.pairRatio_[(hiRank, lowRank)]
	
	def RatioByIdx(self, idx0, idx1):
		return self.pairRatio_[(self.idx2Rank_[idx0], self.idx2Rank_[idx1])]
	
	def Idx2Rank(self, idx):
		return self.idx2Rank[idx]
	
	def Rank2Idx(self, rank):
		return self.rank2Idx_[rank]
	
class ChangeMatrix:
	epsilon = 1e-12
	def __init__(self, altCrtMatrix):
		self.ratioTable_ = RatioTable(altCrtMatrix)
		self.altCrtMatrix_ = altCrtMatrix
		
		self.absCrtChangeMat_ = {}
		self.relCrtChangeMat_ = {}
		self.absAltChangeMat_ = {}
		self.relAltChangeMat_ = {}
		return

	def Compute(self):
		#计算Priorities并排序
		self.altCrtMatrix_.Compute()
		self.ratioTable_.Compute()
		
		altNames = self.altCrtMatrix_.AlternativeNames()
		crtNames = self.altCrtMatrix_.CriterionNames()
		
		priors = self.ratioTable_.WPMPriorities()
		rank2idxDict = self.ratioTable_.rank2Idx_
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
				
				for criteriaIdx in range(len(crtNames)):
					crtWeight = self.altCrtMatrix_.CrtPriority(criteriaIdx)
					
					# logPRatio 为公式上部比乘方连积的对数 logRatio为公式下方比的对数
					logPRatio = math.log(self.ratioTable_.RatioByIdx(hiRankIdx, lowRankIdx))
					logRatio = math.log(self.altCrtMatrix_.AltCrtValue(hiRankIdx, criteriaIdx) / self.altCrtMatrix_.AltCrtValue(lowRankIdx, criteriaIdx))
					absCrtChange =  logPRatio / logRatio
					relCrtChange = absCrtChange / crtWeight * 100.0
					
					if relCrtChange > 100:
						absCrtChange = None
						relCrtChange = None
						
					self.absCrtChangeMat_[(hiAltRank, lowAltRank)][criteriaIdx] = absCrtChange
					self.relCrtChangeMat_[(hiAltRank, lowAltRank)][criteriaIdx] = relCrtChange
					
					#求出解算评价目标敏感性所需要的绝对变化与相对变化量
					hiLowRatio = 1.0 / self.ratioTable_.RatioByIdx(hiRankIdx, lowRankIdx)
					relAltChange = (1.0 - hiLowRatio ** (1.0 / crtWeight) )  * 100.0
					relAltChangeRev = (1.0 - 1.0 / (hiLowRatio ** (1.0 / crtWeight))) * 100.0
					
					if relAltChange > 100:
						relAltChange = None
					if relAltChangeRev > 100:
						relAltChangeRev = None
						
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
	def RatioTable(self):
		return self.ratioTable_
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