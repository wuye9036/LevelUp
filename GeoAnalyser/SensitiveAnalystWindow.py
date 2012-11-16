#!/usr/bin/env python
# -*- coding: cp936 -*-

import os, sys, traceback
from PyQt4 import QtCore, QtGui

from TableModelSaver import *

from Model.AltCrtModel import *
from Model.AltRankViewerModel import *
from Model.AbsChgViewerModel import *
from Model.RelChgViewerModel import *
from Model.SensListViewerModel import *
from Model.ThValViewerModel import *
from Model.CrtDegsViewerModel import *
from Model.SensViewerModel import *

from SensAnalystViewerWindow import *

from UI.SenstiveAnalystWnd_ui import *

class SensitiveAnalystWindow(QtCore.QObject):
	def __init__(self, altCrtMat, modelName, parent = None ):
		QtCore.QObject.__init__(self)
		
		self.dlg_ = QtGui.QDialog()
		self.ui_ = Ui_Dialog()
		self.ui_.setupUi(self.dlg_)
		
		self.altCrtMat_ = altCrtMat
		self.modelName_ = modelName
		
		self.model_ = AltCrtModel(altCrtMat)
		self._SetupSlots()
		
		self.ui_.tableView.setModel(self.model_)
		pass
	
	def _SetupSlots(self):
		self.connect(self.ui_.btnAbsChg, QtCore.SIGNAL("clicked(bool)"), self._OpenAbsChgWnd)
		self.connect(self.ui_.btnCrtDegs, QtCore.SIGNAL("clicked(bool)"), self._OpenCrtDegsWnd)
		self.connect(self.ui_.btnRelChg, QtCore.SIGNAL("clicked(bool)"), self._OpenRelChgWnd)
		self.connect(self.ui_.btnSens, QtCore.SIGNAL("clicked(bool)"), self._OpenSensWnd)
		self.connect(self.ui_.btnSensLst, QtCore.SIGNAL("clicked(bool)"), self._OpenSensListWnd)
		self.connect(self.ui_.btnThVal, QtCore.SIGNAL("clicked(bool)"), self._OpenThValWnd)
		
		self.connect(self.ui_.btnSave, QtCore.SIGNAL("clicked(bool)"), self._OnSave)
		self.connect(self.ui_.btnCancel, QtCore.SIGNAL("clicked(bool)"), self._OnCancel)

		pass
	
	def ShowWidget(self):
		self.dlg_.show()
		
	def ShowWidgetModal(self):
		self.dlg_.exec_()
		
	def _OpenAltRankWnd(self, b):
		self._OpenCommonSensViewerWnd(CreateAltRankViewerModel(self.modelName_), "Ranking of Alternatives")
	
	def _OpenAbsChgWnd(self, b):
		self._OpenCommonSensViewerWnd(CreateAbsChgViewerModel(self.modelName_), "Abstract Change Values")
	
	def _OpenRelChgWnd(self, b):
		self._OpenCommonSensViewerWnd(CreateRelChgViewerModel(self.modelName_), "Relative Change Values")
	
	def _OpenSensListWnd(self, b):
		self._OpenCommonSensViewerWnd(CreateSensListViewerModel(self.modelName_), "Sensitivity Coefficiencies")
	
	def _OpenThValWnd(self, b):
		self._OpenCommonSensViewerWnd(CreateThValViewerModel(self.modelName_), "Threshold Values")
		
	def _OpenCrtDegsWnd(self, b):
		self._OpenCommonSensViewerWnd(CreateCrtDegsViewerModel(self.modelName_), "Criteria Degrees")
	
	def _OpenSensWnd(self, b):
		self._OpenCommonSensViewerWnd(CreateSensViewerModel(self.modelName_), "Sensitivity coefficiencies")
		
	def _OpenCommonSensViewerWnd(self, model, windowName):
		altCrtMat = self.altCrtMat_
		try:
			model.Load(altCrtMat)
			sensViewerWnd = SensAnalystViewerWindow(model)
			sensViewerWnd.dlg_.setWindowTitle(windowName)
			sensViewerWnd.ShowWidgetModal()
		except:
			traceback.print_exc()
			QtGui.QMessageBox.information(
				self.dlg_,
				"错误".decode('cp936'),
				"Absolute Change Table在计算时出现错误。请使用Alternative - Criteria Table Viewer检查文件有效性；并且保证有2个以上的Alternative。".decode('cp936')
				)
		pass
	
	def _OnSave(self, b):
		SaveTableModel([self.model_], "", self.dlg_)
	
	def _OnCancel(self, b):
		self.dlg_.reject()