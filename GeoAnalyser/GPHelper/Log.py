#!/usr/bin/env python
# -*- coding: cp936 -*-

from HelperFunctions import *

class AGSLog:
	def __init__(self):
		pass
	
	def WriteLog(self, str):
		pGP.AddMessage(str)
		
	def WriteErr(self, str):
		pGP.AddError(str)
		
	def WriteWarn(self, str):
		pGP.AddWarning(str)

class NullLog:
	def __init__(self):
		pass
	
	def WriteLog(self, str):
		pass
	
	def WriteErr(self, str):
		pass
	
	def WriteWarn(self, str):
		pass
	
class ConsoleLog:
	def __init__(self):
		pass
	
	def WriteLog(self, str):
		print "Log: %s" % str
		
	def WriteErr(self, str):
		print "Error: %s" % str
	
	def WriteWarn(self, str):
		print "Warning: %s" % str
		
logger = AGSLog()