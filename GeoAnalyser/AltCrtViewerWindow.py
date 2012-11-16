#!/usr/bin/env python

from PyQt4 import QtGui, QtCore
from UI.AltCrtViewerWindow_ui import *
from Model.AltCrtModel import *

class AltCrtViewerWindow(QtCore.QObject):
	def __init__(self, altCrtMat):
		QtCore.QObject.__init__(self)
		
		self.dlg_ = QtGui.QDialog()
		self.ui_ = Ui_Dialog()
		self.ui_.setupUi(self.dlg_)
		
		self.model_ = AltCrtModel(altCrtMat)
		self._SetupSlots()
		
		self.ui_.altCrtTblView.setModel(self.model_)
		
	def _SetupSlots(self):
		self.connect(self.ui_.btnSave, QtCore.QSIGNAL("clicked(bool)"), self._OnSave)
		#self.connect(self.ui_.btnCancel, QtCore.QSIGNAL("clicked(bool)"), self._OnCancel)
		pass
	
	def ShowWidgetModal(self):
		self.dlg_.exec_()
		
	def ShowWidget(self):
		self.dlg_.show()
		
	def _OnCancel(self, b):
		self.dlg_.reject()