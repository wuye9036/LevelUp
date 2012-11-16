#!/usr/bin/env python
# -*- coding: cp936 -*-

import sys, os

from PyQt4 import QtGui, QtCore
from GPHelper.Workspace import *
from GPHelper.HelperFunctions import *
from MainDocument import mainDoc
from UI.NEGSimWnd_ui import *
from PyExtLib import PyNEGSimulator
from PyExtLib.DistanceMatrix import *

class NEGSimWindow(QtCore.QObject):
	def __init__(self, altCrtMat, ws):
		QtCore.QObject.__init__(self)
		
		self.altCrtMat_ = altCrtMat
		
		self.dlg_ = QtGui.QDialog()
		self.ui_ = Ui_Dialog()
		self.ui_.setupUi(self.dlg_)
	
		self._SetupSlots()
		self._SetupCombos()
		pass
	
	def ShowWidget(self):
		self.dlg_.show()
	
	def ShowWidgetModal(self):
		self.dlg_.exec_()
		
	def _InitProgressBar(self):
		self.ui_.pbCurrent.setEnable(False)
		self.ui_.pbtotal.setEnable(False)
		self.ui_.btnCancel.setEnabled(False)
		pass
	
	def _SetupCombos(self):
		pass
	
	def _SetupSlots(self):
		self.connect(self.ui_.btnCancel, QtCore.SIGNAL("clicked(bool)"), self._OnCancel)
		self.connect(self.ui_.btnExcute, QtCore.SIGNAL("clicked(bool)"), self._OnExecute)
		self.connect(self.ui_.btnExit, QtCore.SIGNAL("clicked(bool)"), self._OnExit)
		self.connect(self.ui_.btnResultPreview, QtCore.SIGNAL("clicked(bool)"), self._OnResultPreview)
		pass
	
	def _ExecuteOnce(self, sim, distMat):
		sim.Reset()
		sim.SetDistanceMatrix(distMat.Matrix())
		sim.SetWeights(self._GetWeights())

		self.ui_.btnExcute.setEnable(False)	
		sim.Run()
		
		while(sim.State() == PyNEGSimulator.RunState.Running):
			QApplication.processEvent()
			pass
		
		if (sim.State() == PySimulator.RunState.OK):
			# Save Result
			return True
		else:
			# Pass
			return False
		
	def _OnExecute(self, b):
		itcnt = self.ui_.sbExpcnt.value()
		self.ui_.pbCurrent.setEnable(True)
		self.ui_.pbtotal.setEnable(True)
		self.ui_.btnCancel.setEnabled(True)
		sim = PyNEGSimulator.Simulator()
		distMat = DistantMatrix()
		
		it = 0
		while (it < itcnt):
			if(self._ExecuteOnce(sim, distMat)):
				it += 1
		
		self.ui_.btnExcute.setEnable(True)
		self.ui_.btnCancel.setEnable(False)
		pass
	
	def _OnCancel(self, b):
		sim.Abort()
		pass
	
	def _OnExit(self, b):
		if(sim.State() == PyNEGSimulator.RunState.Running):
			sim.Abort()
			
		while(sim.State() != PyNEGSimulator.RunState.Aborted):
			pass
		
		self.dlg_.reject()
		pass
	
	def _OnResultPreview(self, b):
		if(sim.State() == PyNEGSimulator.RunState.Running):
			return
		pass
	
	def _GetWeights(self):
		weightModel = str(self.ui_.comboWeightModel.currentText())
		self.altCrtMat_.Compute(weightModel)
		retWeights = [1.0 for i in len(self.altCrtMat_.crtNames_)]
		for name in self.altCrtMat_.crtNames_:
			retWeights[int(name)] = self.altCrtMat_.PriorityByName(name)
		return retWeights