#!/usr/bin/env python

from math import *

class Envelope:
	def __init__(self, minx, miny, maxx, maxy):
		self.MinX = minx
		self.MinY = miny
		self.MaxX = maxx
		self.MaxY = maxy
	
	def Width(self):
		return self.MaxX - self.MinX
	
	def Height(self):
		return self.MaxY - self.MinY
	
	def Area(self):
		return self.Width() * self.Height()
	
	def MaxExtent(self):
		return max(self.Width(), self.Height())
	
	def MinExtent(self):
		return min(self.Width(), self.Height())