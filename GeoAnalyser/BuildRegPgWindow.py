#!/usr/bin/env python
# -*- coding: cp936 -*-

from PyQt4 import QtCore, QtGui

from UI.BuildRegPgWnd_ui import *
from GPHelper.Workspace import *
from LocationAltGenerator.LocationFilter import *
from LocationAltGenerator.LocationBuilder import *
from LocationAltGenerator.PostAdjacencyBuilder import *

import traceback

class BuildRegPgWindow(QtCore.QObject):
	def __init__(self, dataset, parent = None):
		QtCore.QObject.__init__(self, parent)
		
		self.dataset_ = dataset
		
		self.dlg_ = QtGui.QDialog()
		self.ui_ = Ui_Dialog()
		self.ui_.setupUi(self.dlg_)
	
		self._SetupSlots()
		self._SetupControls()
		
	def ShowWidget(self):
		self.dlg_.show()
		
	def ShowWidgetModal(self):
		self.dlg_.exec_()
		
	def _SetupSlots(self):
		#self.connect(self.ui_.genCloudBtn, QtCore.SIGNAL("clicked(bool)"), self._OnGenCloudMap)
		#self.connect(self.ui_.clipBtn, QtCore.SIGNAL("clicked(bool)"), self._OnClip)
		#self.connect(self.ui_.genNetworkBtn, QtCore.SIGNAL("clicked(bool)"), self._OnGenNetwork)
		self.connect(self.ui_.cancelBtn, QtCore.SIGNAL("clicked(bool)"), self._OnCancel)
		self.connect(self.ui_.btnExecute,  QtCore.SIGNAL("clicked(bool)"), self._OnExecute)
		
	def _SetupControls(self):
		ws = Workspace(self.dataset_)
		boundaryFeatclsLst = ws.EnumFeatureClass("*", "POLYGON")
		allFeat = [name.lower() for name in ws.EnumFeatureClass("*", "")]
		
		#初始化输入点要素与边界要素
		for boundaryFeatcls in boundaryFeatclsLst:
			self.ui_.comboBoundary.addItem(boundaryFeatcls)
			
		#设置点要素类名
		baseName = "Location"
		id = 0
		newName = "%s%d" % (baseName, id)
		while newName.lower() in allFeat:
			id += 1
			newName = "%s%d" % (baseName, id)

		self.ui_.editFeatclsName.setText(newName)
		self.ui_.editClipped.setText(newName + "_clipped")
		self.ui_.editNetwork.setText(newName + "_network")
		
		#设置布局算法名称
		layoutAlgoNames = EnumLocationBuilders()
		for layoutAlgo in layoutAlgoNames:
			self.ui_.comboShape.addItem(layoutAlgo)
			
		#设置Interval
		self.ui_.editSize.setText("80000")
		pass
	
	def _OnExecute(self, b):
		if self._OnGenCloudMap(b) != None: return
		if self._OnClip(b) != None: return
		if self._OnGenNetwork(b) != None: return
		self._Success("成功创建镶嵌！")
		
	def _OnGenCloudMap(self, b):
		locationFeatcls = str(self.ui_.editFeatclsName.text())
		boundaryFeatcls = str(self.ui_.comboBoundary.currentText())
		if not locationFeatcls:
			QtGui.QMessageBox.information(
				self.dlg_,
				"错误".decode('cp936'),
				"点要素类名称错误。".decode('cp936')
				)
			return
		
		#检查要素类名称存在性并确认覆盖
		locationFeatcls = os.path.join(self.dataset_, locationFeatcls)
		boundaryFeatcls = os.path.join(self.dataset_, boundaryFeatcls)
		if pGP.Exists(locationFeatcls):
			warnResult = QtGui.QMessageBox.warning(
				self.dlg_,
				"警告".decode('cp936'),
				"输出要素类已存在。是否覆盖？".decode('cp936'),
				QtGui.QMessageBox.Yes | QtGui.QMessageBox.No
				)
			if warnResult == QtGui.QMessageBox.Yes:
				pGP.Delete_management(locationFeatcls)
			else:
				return
			
		#用户交互警告，执行具体操作
		shapeName = str(self.ui_.comboShape.currentText());
		
		if shapeName == "Eight-Neighbor-Square" or shapeName == "Four-Neighbor-Square":
			shapeName = "Square"
			#QtGui.QMessageBox.information(
			#	self.dlg_,
			#	"错误".decode('cp936'),
			#	"您选择的几何形状暂时未实现。".decode('cp936')
			#	)
			#return
		
		locBuilder = ArcGISPointsBuilder(boundaryFeatcls)
		try:
			locBuilder.Build(
				shapeName,#str(self.ui_.comboShape.currentText()),
				float(str(self.ui_.editSize.text()))
				)
			warnResult = QtGui.QMessageBox.warning(
				self.dlg_,
				"警告".decode('cp936'),
				"接下来的操作需要较长的时间，请耐心等候。是否继续？".decode('cp936'),
				QtGui.QMessageBox.Yes | QtGui.QMessageBox.No
				)
			if warnResult != QtGui.QMessageBox.Yes:
				return
			locBuilder.Save(locationFeatcls)
			#QtGui.QMessageBox.information(
			#	self.dlg_,
			#	"成功".decode('cp936'),
			#	"已成功创建区位信息。".decode('cp936')
			#	)
		except:
			traceback.print_exc()
			QtGui.QMessageBox.information(
				self.dlg_,
				"错误".decode('cp936'),
				"输入参数有误。请检查并修改后再次执行".decode('cp936')
				)
			return False
	
	def _OnClip(self, b):
		ws = Workspace(self.dataset_)
		
		inputFeatcls = str(self.ui_.editFeatclsName.text())
		boundaryFeatcls = str(self.ui_.comboBoundary.currentText())
		outputFeatcls = str(self.ui_.editClipped.text())
		
		if not (outputFeatcls and inputFeatcls and boundaryFeatcls):
			QtGui.QMessageBox.information(
				self.dlg_,
				"错误！".decode('cp936'),
				"输入参数中存在空项。请检查输入参数并确定。".decode('cp936')
				)
			return False
		
		if not self._AssertExist(ws, inputFeatcls): return False
		
		if outputFeatcls == inputFeatcls:
			QtGui.QMessageBox.information(
				self.dlg_,
				"错误！".decode('cp936'),
				"输出要素不可与输入要素重名。".decode('cp936')
				)
			return False
		
		if not self._WarnOverwrite(ws, outputFeatcls): return False
		
		clipFilter = ArcGISLocationClipFilter(os.path.join(self.dataset_, boundaryFeatcls))
		clipFilter.Filtrate(
			os.path.join(self.dataset_, inputFeatcls),
			os.path.join(self.dataset_, outputFeatcls)
			)
		#self._Success("成功过滤要素类！")
	
	def _OnGenNetwork(self, b):
		ws = Workspace(self.dataset_)
		inputFeatcls = str(self.ui_.editClipped.text())
		outputFeatcls = str(self.ui_.editNetwork.text())
		dist = float(str(self.ui_.editSize.text()))
		shape = str(self.ui_.comboShape.currentText())
		
		if shape == "Eight-Neighbor-Square":
			thVal = dist * 1.5
		else:
			thVal = dist * 1.01
		
		if not (inputFeatcls and outputFeatcls):
			QtGui.QMessageBox.information(
				self.dlg_, "错误".decode('cp936'),
				"输入参数有误。请检查输入参数的正确性。".decode('cp936'))
			return False
		
		if not self._AssertExist(ws, inputFeatcls): return False
		if not self._WarnOverwrite(ws, outputFeatcls): return False
		
		adjBuilder = ArcGISPostAdjBuilder(os.path.join(self.dataset_, inputFeatcls))
		adjBuilder.Build(thVal)
		adjBuilder.Save(os.path.join(self.dataset_, outputFeatcls))
	
	def _OnCancel(self, b):
		self.dlg_.reject()
		pass
	
	def _AssertNotExist(self, ws, featName):
		pass
	
	def _AssertExist(self, ws, featcls):
		if not ws.IsInclude(featcls):
			QtGui.QMessageBox.information(
				self.dlg_,
				"错误！".decode('cp936'),
				"输入要素不存在！".decode('cp936')
				)
			return False
		return True
	
	def _Success(self, successDesc):
		QtGui.QMessageBox.information(
			self.dlg_,
			"成功".decode('cp936'),
			successDesc.decode('cp936')
			)
		pass
	
	def _WarnOverwrite(self, ws, featcls):
		if ws.IsInclude(featcls):
			warnResult = QtGui.QMessageBox.warning(
				self.dlg_,
				"警告！".decode('cp936'),
				"输出要素在要素集中已存在，是否覆盖原有要素类？".decode('cp936'),
				QtGui.QMessageBox.Yes | QtGui.QMessageBox.No
				)
			if warnResult != QtGui.QMessageBox.Yes:
				return False
			pGP.Delete_management(os.path.join(self.dataset_, featcls))
		return True