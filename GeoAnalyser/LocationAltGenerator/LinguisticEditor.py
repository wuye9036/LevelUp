#!/usr/bin/env python
# -*- coding: cp936 -*-

from Model.LinguisticEditorModel import *
from UI.LinguisticEditor_ui import *
from ProximityBuilderImpl.LinguisticTable import *

from PyQt4 import QtGui, QtCore

class LinguisticEditor(QtCore.QObject):
	def __init__(self, lingTbl):
		QtCore.QObject.__init__(self)
		
		self.lingTbl_ = lingTbl
		self.dlg_ = QtGui.QDialog()
		self.ui_ = Ui_Dialog()
		self.ui_.setupUi(self.dlg_)
		
		self.model_ = LinguisticEditorModel(self.lingTbl_)
		self.delegate_ = LinguisticEditorDelegate()
		
		self.ui_.tableView.setModel(self.model_)
		self.ui_.tableView.setItemDelegate(self.delegate_)
		
		self._SetupSlots()
		
	def ShowWidget(self):
		return self.dlg_.show()
	
	def _SetupSlots(self):
		self.connect(self.ui_.acceptBtn, QtCore.SIGNAL("clicked(bool)"), self._OnAccepted)
		self.connect(self.ui_.cancleBtn, QtCore.SIGNAL("clicked(bool)"), self._OnCancled)
		return
	
	def _OnAccepted(self, b):
		self.model_.lingTbl_.Save()
		self.dlg_.accept()
		return
	
	def _OnCancled(self, b):
		self.dlg_.reject()
		return