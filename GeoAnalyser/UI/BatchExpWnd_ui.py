# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'BatchExpWnd.ui'
#
# Created: Sun Aug 03 19:26:21 2008
#      by: PyQt4 UI code generator 4.3.4-snapshot-20080328
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(QtCore.QSize(QtCore.QRect(0,0,460,190).size()).expandedTo(Dialog.minimumSizeHint()))

        self.gridlayout = QtGui.QGridLayout(Dialog)
        self.gridlayout.setObjectName("gridlayout")

        self.label = QtGui.QLabel(Dialog)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred,QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label.sizePolicy().hasHeightForWidth())
        self.label.setSizePolicy(sizePolicy)
        self.label.setObjectName("label")
        self.gridlayout.addWidget(self.label,0,0,1,1)

        self.edtAltCrtFilePath = QtGui.QLineEdit(Dialog)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred,QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.edtAltCrtFilePath.sizePolicy().hasHeightForWidth())
        self.edtAltCrtFilePath.setSizePolicy(sizePolicy)
        self.edtAltCrtFilePath.setObjectName("edtAltCrtFilePath")
        self.gridlayout.addWidget(self.edtAltCrtFilePath,0,1,1,1)

        self.btnOpen = QtGui.QPushButton(Dialog)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred,QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btnOpen.sizePolicy().hasHeightForWidth())
        self.btnOpen.setSizePolicy(sizePolicy)
        self.btnOpen.setObjectName("btnOpen")
        self.gridlayout.addWidget(self.btnOpen,0,2,1,1)

        self.label_3 = QtGui.QLabel(Dialog)
        self.label_3.setObjectName("label_3")
        self.gridlayout.addWidget(self.label_3,1,0,1,1)

        self.spinExpTimes = QtGui.QSpinBox(Dialog)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred,QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.spinExpTimes.sizePolicy().hasHeightForWidth())
        self.spinExpTimes.setSizePolicy(sizePolicy)
        self.spinExpTimes.setMinimum(1)
        self.spinExpTimes.setMaximum(10000)
        self.spinExpTimes.setObjectName("spinExpTimes")
        self.gridlayout.addWidget(self.spinExpTimes,1,1,1,1)

        self.label_2 = QtGui.QLabel(Dialog)
        self.label_2.setObjectName("label_2")
        self.gridlayout.addWidget(self.label_2,2,0,1,1)

        self.edtBaseFileName = QtGui.QLineEdit(Dialog)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred,QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.edtBaseFileName.sizePolicy().hasHeightForWidth())
        self.edtBaseFileName.setSizePolicy(sizePolicy)
        self.edtBaseFileName.setObjectName("edtBaseFileName")
        self.gridlayout.addWidget(self.edtBaseFileName,2,1,1,1)

        self.lblNameShower = QtGui.QLabel(Dialog)
        self.lblNameShower.setObjectName("lblNameShower")
        self.gridlayout.addWidget(self.lblNameShower,2,2,1,1)

        self.btnOk = QtGui.QPushButton(Dialog)
        self.btnOk.setObjectName("btnOk")
        self.gridlayout.addWidget(self.btnOk,3,2,1,1)

        self.btnExit = QtGui.QPushButton(Dialog)
        self.btnExit.setObjectName("btnExit")
        self.gridlayout.addWidget(self.btnExit,4,2,1,1)

        self.btnSetRandGen = QtGui.QPushButton(Dialog)
        self.btnSetRandGen.setObjectName("btnSetRandGen")
        self.gridlayout.addWidget(self.btnSetRandGen,3,1,1,1)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(QtGui.QApplication.translate("Dialog", "Batch Experiment", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("Dialog", "AltCrt File:", None, QtGui.QApplication.UnicodeUTF8))
        self.btnOpen.setText(QtGui.QApplication.translate("Dialog", "Open...", None, QtGui.QApplication.UnicodeUTF8))
        self.label_3.setText(QtGui.QApplication.translate("Dialog", "Experiment Times", None, QtGui.QApplication.UnicodeUTF8))
        self.label_2.setText(QtGui.QApplication.translate("Dialog", "Base File Name:", None, QtGui.QApplication.UnicodeUTF8))
        self.lblNameShower.setText(QtGui.QApplication.translate("Dialog", "Name Shower", None, QtGui.QApplication.UnicodeUTF8))
        self.btnOk.setText(QtGui.QApplication.translate("Dialog", "OK", None, QtGui.QApplication.UnicodeUTF8))
        self.btnExit.setText(QtGui.QApplication.translate("Dialog", "Exit", None, QtGui.QApplication.UnicodeUTF8))
        self.btnSetRandGen.setText(QtGui.QApplication.translate("Dialog", "Set Random Generator...", None, QtGui.QApplication.UnicodeUTF8))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    Dialog = QtGui.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())
