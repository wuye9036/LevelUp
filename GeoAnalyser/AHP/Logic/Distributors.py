#!/usr/bin/env python

import random

class DistributorCollection:
	def __init__(self):
		self.dists_ = {
			"Uniform" : UniformDistributor(),
			"Gauss" : GaussDistributor()
		}
	
	def GetDistributorNames(self):
		return self.dists_.keys()
	
	def GetDistributor(self, distName):
		return self.dists_[distName]
	
class UniformDistributor:
	def __init__(self):
		self.Min = 0.0
		self.Max = 1.0
	
	def GetParameterNames(self):
		return ["Min", "Max"]
	
	def GetRandom(self):
		return random.uniform(self.Min, self.Max)
	
class GaussDistributor:
	def __init__(self):
		self.Mu = 0.0
		self.Sigma = 1.0
		self.Min = 0.0
		self.Max = 1.0
		
	def GetParameterNames(self):
		return ["Mu", "Sigma", "Min", "Max"]
	
	def GetRandom(self):
		if self.Min >= self.Max :
			return self.Min
		
		ret = random.gauss(self.Mu, self.Sigma)
		while ( ret < self.Min or ret > self.Max):
			ret = random.gauss(self.Mu, self.Sigma)
		return ret