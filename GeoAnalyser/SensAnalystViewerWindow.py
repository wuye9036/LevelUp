#!/usr/bin/env python
# -*- coding: cp936 -*-

from PyQt4 import QtGui, QtCore
from UI.SensAnalystViewerWnd_ui import *
from TableModelSaver import *

class SensAnalystViewerWindow(QtCore.QObject):
	def __init__(self, model):
		QtCore.QObject.__init__(self)
		
		self.dlg_ = QtGui.QDialog()
		self.ui_ = Ui_Dialog()
		self.ui_.setupUi(self.dlg_)
		
		self.model_ = model
		self.ui_.tableView.setModel(self.model_)
		
		self._SetupSlots()
		
	def _SetupSlots(self):
		self.connect(self.ui_.cancelBtn, QtCore.SIGNAL("clicked(bool)"), self._OnCancel)
		self.connect(self.ui_.saveBtn, QtCore.SIGNAL("clicked(bool)"), self._OnSave)
		
	def ShowWidget(self):
		self.dlg_.show()
		
	def ShowWidgetModal(self):
		self.dlg_.exec_()
		
	def _OnCancel(self, b):
		self.dlg_.reject()
		
	def _OnSave(self, b):
		SaveTableModel([self.model_], "", self.dlg_)
	