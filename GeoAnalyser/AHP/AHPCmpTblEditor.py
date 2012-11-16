# -*- coding: cp936 -*-

import MainDocument

from AHPAutoCmpTblEditor import *
from UI.AHPMatrixEditor_ui import *
from Model.GoalsCmpTblModel import *
from TableModelSaver import *

from PyQt4 import QtCore, QtGui

#对话框对应的代码
class AHPCmpTblEditor(QtCore.QObject):
    @staticmethod
    def FromModel(mdl, delegate, propsMdl, cmpTbl):
        retEditor = AHPCmpTblEditor()
        
        retEditor.matModel_ = mdl
        retEditor.delegate_ = delegate
        retEditor.matPropModel_ = propsMdl
        
        retEditor.ui_.matrixView.setModel(retEditor.matModel_)
        if delegate: self.ui_.matrixView.setItemDelegate(retEditor.delegate_)
        retEditor.ui_.propertiesView.setModel(retEditor.matPropModel_)
        retEditor.cmpTbl_ = cmpTbl
        
        return retEditor
    
    def __init__(self, cmpTbl = None):
        QtCore.QObject.__init__(self)
       
        self.dlg_ = QtGui.QDialog()
        self.ui_ = Ui_Dialog()
        self.ui_.setupUi(self.dlg_)
        
        if cmpTbl != None:
            self.cmpTbl_= cmpTbl
            
            self.matModel_ = GoalsCmpTblModel(cmpTbl, None)
            self.delegate_ = GoalsCmpTblDelegate(None)
            self.matPropModel_ = GoalsCmpTblPropsModel(cmpTbl)
            
            self.ui_.matrixView.setModel(self.matModel_)
            self.ui_.matrixView.setItemDelegate(self.delegate_)
            self.ui_.propertiesView.setModel(self.matPropModel_)
        
        self._SetupSlots()
        
    def _SetupSlots(self):
        self.connect(self.ui_.calcBtn, QtCore.SIGNAL("clicked(bool)"), self._CaculateProperties)
        self.connect(self.ui_.btnCancel, QtCore.SIGNAL("clicked(bool)"), self._OnCancel)
        self.connect(self.ui_.btnSave, QtCore.SIGNAL("clicked(bool)"), self._OnSave)
        self.connect(self.ui_.btnAutoGen, QtCore.SIGNAL("clicked(bool)"), self._OnAutoGen)    
        return
        
    def ShowWidget(self):
        return self.dlg_.show()
    
    def ShowWidgetModal(self):
        return self.dlg_.exec_()
    
    def _CaculateProperties(self, bool = 0):
        self.cmpTbl_.CalculateProperties()
        self.matPropModel_.reset()
        self.matModel_.reset()
        
    def UI(self):
        return self.ui_
    
    def Widget(self):
        return self.dlg_
       
    def _OnCancel(self, b):
        self.dlg_.reject()
        
    def _OnSave(self, b):
        SaveTableModel([self.matModel_, self.matPropModel_], MainDocument.mainDoc.ProjDir, self.dlg_)
        
    def _OnAutoGen(self, b):
        autoEditor = AHPAutoCmpTblEditor(self.cmpTbl_)
        autoEditor.ShowWidgetModal()