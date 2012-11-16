#!/usr/bin/env python


from PyQt4 import QtGui, QtCore
import os, MainDocument
from AHP.AHPTreeRandGenEditor import *

from UI.BatchExpWnd_ui import *
from AHP.Logic.SensitiveAnalyst.AltCrtMatrix import *
from AHP.Logic.AHPTree import *
from GPHelper.FeatureClass import *

class BatchExpWindow(QtCore.QObject):
	def __init__(self):
		QtCore.QObject.__init__(self)
		
		self.dlg_ = QtGui.QDialog()
		self.ui_ = Ui_Dialog()
		self.ui_.setupUi(self.dlg_)
		
		self._SetupSlots()
		dir = MainDocument.mainDoc.ProjDir
	
		self.altCrtFileName_ = os.path.join(dir, "AlternativeCriteriaEvaluationTable.xml")
		self.crtFileName_ = os.path.join(dir, "Criteria.xml")
		ahpFileName = os.path.join(dir, "AHP.xml")
		self.ahpTree_ = AHPTree()
		self.ahpTree_.LoadXml(ahpFileName)
		
		self.altCrtMat_ = AltCrtMatrix()
		self.altCrtMat_.Load(self.altCrtFileName_, self.crtFileName_)
		
	def _SetupSlots(self):
		self.connect(self.ui_.btnOk, QtCore.SIGNAL("clicked(bool)"), self._OnOk)
		self.connect(self.ui_.btnExit, QtCore.SIGNAL("clicked(bool)"), self._OnExit)
		self.connect(self.ui_.btnSetRandGen, QtCore.SIGNAL("clicked(bool)"), self._OnSetRandGen)
		pass
	
	def ShowWidgetModal(self):
		self.dlg_.exec_()
		
	def ShowWidget(self):
		self.dlg_.show()
		
	def _ExtractFromRefLoc(self):
		fc = FeatureClass(os.path.join(sys.argv[1], "refloc"))
		refDatum = {}
		for feat in fc.Features():
			refDatum[str(feat.ID())] = float(feat["POP"])
		return refDatum
		
	def _SavePriorityToARFF(self, fileName, iterCount):
		altIds = self.altCrtMat_.AlternativeNames()
		datum = self.refDatum_
		
		f = open(fileName, "w")
		f.write("@Relation test%04d\n" % iterCount)
		#f.write("@attribute ID String\n")
		f.write("@attribute Geosuit Numeric\n")
		f.write("@attribute Pop {True, False}\n")
		f.write("@data\n")
		for altId in altIds:
			if datum[altId] > 0:
				isCity = "True"
			else:
				isCity = "False"
			f.write("%f, %s\n" % (self.altCrtMat_.PriorityByName(altId), isCity))
		
		f.close()
		
	def _SaveTreeNodeLocalPriority(self, node, local_value_lst, global_value_lst, key_lst):
		if not node:
			return
		
		local_value_lst.append(str(node.LocalWeight()))
		global_value_lst.append(str(node.GlobalWeight()))
		key_lst.append(str(node.Name()))
		
		for child in node.GetChildren():
			self._SaveTreeNodeLocalPriority(child, local_value_lst, global_value_lst, key_lst)
		
	def _OnSetRandGen(self):
		randGenWnd = AHPTreeRandGenEditor(self.ahpTree_)
		randGenWnd.ShowWidgetModal()
		self.curDist_ = randGenWnd.GetDistributor()
		
	def _OnOk(self, b):
		iterCount = self.ui_.spinExpTimes.value()
		baseFileName = str(self.ui_.edtBaseFileName.text())
		
		self.refDatum_ = self._ExtractFromRefLoc()
		
		ahpLocalValueLists = []
		ahpGlobalValueLists = []
		ahpKeyLists = []
		ahpCsvFile = os.path.join(MainDocument.mainDoc.ProjDir, "AHP.csv")
		
		for iterIdx in range(iterCount):
			
			nodes = self.ahpTree_.AllNodeList()
			for node in nodes:
				node.ahpMat_.RandomFill(self.curDist_)
			rootNode = self.ahpTree_.Root()
			rootNode.UpdateTree()
			
			ahpFile = os.path.join(MainDocument.mainDoc.ProjDir, "AHP%04d.xml" % iterIdx)
			crtFile = os.path.join(MainDocument.mainDoc.ProjDir, "Crt%04d.xml" % iterIdx)
			arffFile = os.path.join(MainDocument.mainDoc.ProjDir, "ARFF%04d.arff" % iterIdx)

			ahpLocalValueList = []
			ahpGlobalValueList = []
			ahpKeyList = []
			
			self._SaveTreeNodeLocalPriority(self.ahpTree_.Root(), ahpLocalValueList, ahpGlobalValueList, ahpKeyList)
			self.ahpTree_.SaveXml(ahpFile)
			self.ahpTree_.SaveCriteriaToXmlFile(crtFile)
			self.altCrtMat_.Load(self.altCrtFileName_, crtFile)
			self._SavePriorityToARFF(arffFile, iterIdx)
			
			ahpLocalValueLists.append(ahpLocalValueList)
			ahpGlobalValueLists.append(ahpGlobalValueList)
			ahpKeyLists.append(ahpKeyList)
		
		f = open(ahpCsvFile, "w")
		f.writelines([str(line)+"\n" for line in ahpLocalValueLists])
		f.write("\n")
		f.writelines([str(line)+"\n" for line in ahpGlobalValueLists])
		f.close()
		
		self.dlg_.accept()
		
	def _OnExit(self, b):
		self.dlg_.reject()