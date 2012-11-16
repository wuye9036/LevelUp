#!/usr/bin/env python
# -*- coding: cp936 -*-
import sys, os

from PyQt4 import QtGui, QtCore
from AHP.Logic.SensitiveAnalyst.AltCrtMatrix import *
from GPHelper.Workspace import *
from GPHelper.HelperFunctions import *

from MainDocument import mainDoc

from UI.ResultImportWnd_ui import *

class ResultImportWindow(QtCore.QObject):
	def __init__(self, ws):
		QtCore.QObject.__init__(self)
		
		self.ws_ = Workspace(ws)
		self.dlg_ = QtGui.QDialog()
		self.ui_ = Ui_Dialog()
		self.ui_.setupUi(self.dlg_)
		
		altCrtFullName = os.path.join(mainDoc.ProjDir, "AlternativeCriteriaEvaluationTable.xml")
		crtFullName = os.path.join(mainDoc.ProjDir, "Criteria.xml")
		
		self.altCrtMat_ = AltCrtMatrix()
		self.altCrtMat_.Load(altCrtFullName, crtFullName)
		
		self.SetupSlots()
		self.SetupCombo()
		pass
	
	def ShowWidget(self):
		self.dlg_.show()
	
	def ShowWidgetModal(self):
		self.dlg_.exec_()
	
	def SetupSlots(self):
		self.connect(self.ui_.btnImport, QtCore.SIGNAL("clicked(bool)"), self._OnImport)
		pass
	
	def SetupCombo(self):
		ptFeatclss = self.ws_.EnumFeatureClass("*", "POINT")
		for featcls in ptFeatclss:
			self.ui_.comboFeatcls.addItem(featcls)
		pass
	
	def _OnImport(self, b):
		featclsName = str(self.ui_.comboFeatcls.currentText())
		fullName = self.ws_.FullName(featclsName)
		#获得所有字段
		crtNames = self.altCrtMat_.CriterionNames()
		altNames = self.altCrtMat_.AlternativeNames()
		
		props = get_featureclass_properties(fullName)
		
		#添加字段
		for crtNameU in crtNames:
			crtName = str(crtNameU)
			if crtName.upper() not in props.dcFields:
				print crtName
				pGP.AddField_management(fullName, crtName, "DOUBLE")
		if "Priority".upper() not in props.dcFields:
			pGP.AddField_management(fullName, "Priority", "DOUBLE")
			
		idFieldName = props.sFID

		#写入数据
		print altNames
		rows = pGP.UpdateCursor(fullName)
		row = rows.next()
		while row:
			row_id = row.GetValue(idFieldName)
			print row_id
			altIndex = altNames.index(str(row_id))
			
			for crtNameU in crtNames:
				crtName = str(crtNameU)
				crtIndex = crtNames.index(crtName)
				val = self.altCrtMat_.AltCrtValue(altIndex, crtIndex)
				row.SetValue(crtName, val)
				
			row.SetValue("Priority", self.altCrtMat_.PriorityByIndex(altIndex))
			
			rows.UpdateRow(row)
			row = rows.next()
		pass
	
		QtGui.QMessageBox.information(
			None,
			"成功".decode('cp936'),
			"已经成功导入数据。".decode('cp936')
			)