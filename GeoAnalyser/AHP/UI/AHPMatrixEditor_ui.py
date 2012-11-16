# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'AHPMatrixEditor.ui'
#
# Created: Sun Jul 27 20:50:08 2008
#      by: PyQt4 UI code generator 4.3.4-snapshot-20080328
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.setWindowModality(QtCore.Qt.WindowModal)
        Dialog.resize(QtCore.QSize(QtCore.QRect(0,0,654,384).size()).expandedTo(Dialog.minimumSizeHint()))

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Expanding,QtGui.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(Dialog.sizePolicy().hasHeightForWidth())
        Dialog.setSizePolicy(sizePolicy)

        self.vboxlayout = QtGui.QVBoxLayout(Dialog)
        self.vboxlayout.setObjectName("vboxlayout")

        self.hboxlayout = QtGui.QHBoxLayout()
        self.hboxlayout.setContentsMargins(0,-1,-1,-1)
        self.hboxlayout.setObjectName("hboxlayout")

        self.criteriaMatGroup = QtGui.QGroupBox(Dialog)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred,QtGui.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(4)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.criteriaMatGroup.sizePolicy().hasHeightForWidth())
        self.criteriaMatGroup.setSizePolicy(sizePolicy)
        self.criteriaMatGroup.setMinimumSize(QtCore.QSize(220,220))
        self.criteriaMatGroup.setObjectName("criteriaMatGroup")

        self.gridlayout = QtGui.QGridLayout(self.criteriaMatGroup)
        self.gridlayout.setObjectName("gridlayout")

        self.matrixView = QtGui.QTableView(self.criteriaMatGroup)

        font = QtGui.QFont()
        font.setFamily("Palatino Linotype")
        self.matrixView.setFont(font)
        self.matrixView.setObjectName("matrixView")
        self.gridlayout.addWidget(self.matrixView,0,0,1,1)
        self.hboxlayout.addWidget(self.criteriaMatGroup)

        spacerItem = QtGui.QSpacerItem(10,20,QtGui.QSizePolicy.Preferred,QtGui.QSizePolicy.Minimum)
        self.hboxlayout.addItem(spacerItem)

        self.matParamsGroup = QtGui.QGroupBox(Dialog)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred,QtGui.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.matParamsGroup.sizePolicy().hasHeightForWidth())
        self.matParamsGroup.setSizePolicy(sizePolicy)
        self.matParamsGroup.setObjectName("matParamsGroup")

        self.vboxlayout1 = QtGui.QVBoxLayout(self.matParamsGroup)
        self.vboxlayout1.setObjectName("vboxlayout1")

        self.propertiesView = QtGui.QTableView(self.matParamsGroup)

        font = QtGui.QFont()
        font.setFamily("Palatino Linotype")
        self.propertiesView.setFont(font)
        self.propertiesView.setObjectName("propertiesView")
        self.vboxlayout1.addWidget(self.propertiesView)

        self.hboxlayout1 = QtGui.QHBoxLayout()
        self.hboxlayout1.setObjectName("hboxlayout1")

        self.calcBtn = QtGui.QPushButton(self.matParamsGroup)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred,QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.calcBtn.sizePolicy().hasHeightForWidth())
        self.calcBtn.setSizePolicy(sizePolicy)
        self.calcBtn.setObjectName("calcBtn")
        self.hboxlayout1.addWidget(self.calcBtn)

        self.btnCancel = QtGui.QPushButton(self.matParamsGroup)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred,QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.btnCancel.sizePolicy().hasHeightForWidth())
        self.btnCancel.setSizePolicy(sizePolicy)
        self.btnCancel.setObjectName("btnCancel")
        self.hboxlayout1.addWidget(self.btnCancel)
        self.vboxlayout1.addLayout(self.hboxlayout1)

        self.vboxlayout2 = QtGui.QVBoxLayout()
        self.vboxlayout2.setObjectName("vboxlayout2")

        self.btnAutoGen = QtGui.QPushButton(self.matParamsGroup)
        self.btnAutoGen.setObjectName("btnAutoGen")
        self.vboxlayout2.addWidget(self.btnAutoGen)

        self.btnSave = QtGui.QPushButton(self.matParamsGroup)
        self.btnSave.setObjectName("btnSave")
        self.vboxlayout2.addWidget(self.btnSave)
        self.vboxlayout1.addLayout(self.vboxlayout2)
        self.hboxlayout.addWidget(self.matParamsGroup)
        self.vboxlayout.addLayout(self.hboxlayout)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(QtGui.QApplication.translate("Dialog", "Dialog", None, QtGui.QApplication.UnicodeUTF8))
        self.criteriaMatGroup.setTitle(QtGui.QApplication.translate("Dialog", "相对权重矩阵", None, QtGui.QApplication.UnicodeUTF8))
        self.matParamsGroup.setTitle(QtGui.QApplication.translate("Dialog", "矩阵参数", None, QtGui.QApplication.UnicodeUTF8))
        self.calcBtn.setText(QtGui.QApplication.translate("Dialog", "Compute", None, QtGui.QApplication.UnicodeUTF8))
        self.btnCancel.setText(QtGui.QApplication.translate("Dialog", "Cancel", None, QtGui.QApplication.UnicodeUTF8))
        self.btnAutoGen.setText(QtGui.QApplication.translate("Dialog", "Auto Gen", None, QtGui.QApplication.UnicodeUTF8))
        self.btnSave.setText(QtGui.QApplication.translate("Dialog", "Save As CSV ...", None, QtGui.QApplication.UnicodeUTF8))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    Dialog = QtGui.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())
