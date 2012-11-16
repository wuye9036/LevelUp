#!/usr/bin/env python
# -*- coding: cp936 -*-
import traceback

from MainDocument import *

import UI.ProximityBuilderWnd_ui
from PyQt4 import QtGui, QtCore
from LocationAltGenerator.ProximityBuilder import *
from GPHelper.Workspace import *
from GPHelper.HelperFunctions import *
from LocationAltGenerator.ProximityBuilderImpl.LinguisticTable import *

from AHP.Logic.SensitiveAnalyst.AltCrtMatrix import *
from AHP.Logic.AltCmpTable import *
from AHP.AHPCmpTblEditor import *
from AHP.Model.GoalsCmpTblModel import *

from Model.AltCmpTblModel import *

from UI.ProximityBuilderWnd_ui import *

class ProximityBuilderWindow(QtCore.QObject):
	def __init__(self, dataset, lingFile):
		QtCore.QObject.__init__(self)
		
		self.dlg_ = QtGui.QDialog()
		self.ui_ = Ui_Dialog()
		self.ui_.setupUi(self.dlg_)
		
		self.dataset_ = dataset
		self.ws_ = Workspace(self.dataset_)
		
		self.lingFile_ = lingFile
		
		self._SetupComboBoxes()
		self._SetupSlots()
		
	def ShowWidget(self):
		self.dlg.show()
	
	def ShowWidgetModal(self):
		self.dlg_.exec_()
		
	def _SetupSlots(self):
		self.connect(self.ui_.btnProxAnalystAll, QtCore.SIGNAL("clicked(bool)"), self._OnProxAnalystAll)
		self.connect(self.ui_.btnCancel, QtCore.SIGNAL("clicked(bool)"), self._OnCancel)
		self.connect(self.ui_.btnAltCmp, QtCore.SIGNAL("clicked(bool)"), self._OnAltCmp)
		pass
	
	def _SetupComboBoxes(self):
		#设置临近算法
		algoList = EnumProximityBuilders()
		for algoName in algoList:
			self.ui_.comboProxAlgoName.addItem(algoName)
		
		#设置可做临近分析的要素类（点要素）
		ws = Workspace(self.dataset_)
		featclsNames = ws.EnumFeatureClass('*', 'POINT')
		for featclsName in featclsNames:
			self.ui_.comboLocFeatcls.addItem(featclsName)

		#设置Criteria要素类
		lt = self.lingTbl_ = LinguisticTable(self.lingFile_)
		crtNames = lt.Data().keys()
		for crtName in crtNames:
			self.ui_.comboCrtName.addItem(crtName)
			
	def _OnProxAnalystAll(self, b):
		#长时警告
		warnResult = QtGui.QMessageBox.warning(self.dlg_,
								  "警告".decode('cp936'),
								  "执行该命令需要较长的时间。\n执行进度可以在ArcToolBox的执行窗口中观察。是否继续？".decode('cp936'),
								  QtGui.QMessageBox.Yes | QtGui.QMessageBox.No
								  )
		if warnResult != QtGui.QMessageBox.Yes:
			return
		
		algoName = self.ui_.comboProxAlgoName.currentText()
		ptFeatclsName = os.path.join(self.dataset_, str(self.ui_.comboLocFeatcls.currentText()))
		if algoName and ptFeatclsName:
			try:
				proxBuilder = CreateProximityBuilder(algoName, ptFeatclsName)
				errs = proxBuilder.Check(self.lingTbl_)
				if errs:
					QtGui.QMessageBox.information(
						self.dlg_,
						"错误！".decode('cp936'),
						reduce(lambda s, info: s + '\n' + str(info) ,
							   	errs)
						)
					return
				
				proxBuilder.Build(self.lingTbl_)
				proxBuilder.SaveToXMLFile(
					os.path.join(os.path.dirname(self.lingFile_), "AlternativeCriteriaEvaluationTable.xml")
					)
				
				self._SaveToFeatureClass(str(self.ui_.comboLocFeatcls.currentText()))
				
				QtGui.QMessageBox.information(
					self.dlg_,
					"成功".decode('cp936'),
					"临近分析已成功执行".decode('cp936')
					)
				
			except:
				traceback.print_exc()
				QtGui.QMessageBox.information(
					self.dlg_,
					"错误".decode('cp936'),
					"临近分析执行中出现异常。可能是由于要素不存在。".decode('cp936')
					)
	
	def _OnAltCmp(self, b):
		altCrtFileName = os.path.join(os.path.dirname(self.lingFile_), "AlternativeCriteriaEvaluationTable.xml")
		altCrtMat = AltCrtMatrix()
		altCrtMat.Load(altCrtFileName, None)
		
		crtName = str(self.ui_.comboCrtName.currentText())
		if crtName not in altCrtMat.CriterionNames():
			QtGui.QMessageBox.information(
				self.dlg_,
				"错误！".decode('cp936'),
				("Criterion " + crtName + " 对应的临近分析数据不存在！").decode('cp936')
				)
			return

		altCmpTbl = AltCmpTable.FromAltCrtTable(altCrtMat, crtName)

		altMdl = AltCmpTblModel(altCmpTbl)
		propMdl = AltCmpTblPropsModel(altCmpTbl)
		
		editor = AHPCmpTblEditor.FromModel(altMdl, None, propMdl, altCmpTbl)
		editor.dlg_.setWindowTitle('Pairwise comparison of industries w.r.t. the criterion " %s " ' % crtName )
		editor.ShowWidgetModal()
	
	def _SaveToFeatureClass(self, featclsName):
		altCrtFullName = os.path.join(mainDoc.ProjDir, "AlternativeCriteriaEvaluationTable.xml")
		
		try:
			crtFullName = os.path.join(mainDoc.ProjDir, "Criteria.xml")
		except:
			crtFullName = None
			
		altCrtMat = AltCrtMatrix()
		altCrtMat.Load(altCrtFullName, crtFullName)
		
		fullName = self.ws_.FullName(featclsName)
		
		#获得所有字段
		crtNames = altCrtMat.CriterionNames()
		altNames = altCrtMat.AlternativeNames()
		
		props = get_featureclass_properties(fullName)
		
		#添加字段	
		for crtNameU in crtNames:
			crtName = str(crtNameU)
			if crtName.upper() not in props.dcFields:
				print crtName
				pGP.AddField_management(fullName, crtName, "DOUBLE")
		if "Fuzzy_Grade".upper() not in props.dcFields:
			pGP.AddField_management(fullName, "Fuzzy_Grade", "DOUBLE")
			
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
				val = altCrtMat.AltCrtValue(altIndex, crtIndex)
				row.SetValue(crtName, val)
				
			row.SetValue("Fuzzy_Grade", altCrtMat.PriorityByIndex(altIndex))
			
			rows.UpdateRow(row)
			row = rows.next()
		pass
		
	def _OnCancel(self, b):
		self.dlg_.reject()