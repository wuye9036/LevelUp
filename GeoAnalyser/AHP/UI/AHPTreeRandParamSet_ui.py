# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'AHPTreeRandParamSet.ui'
#
# Created: Sat Aug 02 22:26:55 2008
#      by: PyQt4 UI code generator 4.3.4-snapshot-20080328
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(QtCore.QSize(QtCore.QRect(0,0,259,396).size()).expandedTo(Dialog.minimumSizeHint()))

        self.vboxlayout = QtGui.QVBoxLayout(Dialog)
        self.vboxlayout.setObjectName("vboxlayout")

        self.hboxlayout = QtGui.QHBoxLayout()
        self.hboxlayout.setObjectName("hboxlayout")

        self.groupBox_2 = QtGui.QGroupBox(Dialog)
        self.groupBox_2.setObjectName("groupBox_2")

        self.vboxlayout1 = QtGui.QVBoxLayout(self.groupBox_2)
        self.vboxlayout1.setObjectName("vboxlayout1")

        self.hboxlayout1 = QtGui.QHBoxLayout()
        self.hboxlayout1.setObjectName("hboxlayout1")

        self.label = QtGui.QLabel(self.groupBox_2)
        self.label.setObjectName("label")
        self.hboxlayout1.addWidget(self.label)

        self.comboDistName = QtGui.QComboBox(self.groupBox_2)
        self.comboDistName.setObjectName("comboDistName")
        self.hboxlayout1.addWidget(self.comboDistName)
        self.vboxlayout1.addLayout(self.hboxlayout1)

        self.tblDistParams = QtGui.QTableView(self.groupBox_2)
        self.tblDistParams.setObjectName("tblDistParams")
        self.vboxlayout1.addWidget(self.tblDistParams)
        self.hboxlayout.addWidget(self.groupBox_2)
        self.vboxlayout.addLayout(self.hboxlayout)

        self.hboxlayout2 = QtGui.QHBoxLayout()
        self.hboxlayout2.setObjectName("hboxlayout2")

        spacerItem = QtGui.QSpacerItem(40,20,QtGui.QSizePolicy.Expanding,QtGui.QSizePolicy.Minimum)
        self.hboxlayout2.addItem(spacerItem)

        self.vboxlayout2 = QtGui.QVBoxLayout()
        self.vboxlayout2.setObjectName("vboxlayout2")

        self.hboxlayout3 = QtGui.QHBoxLayout()
        self.hboxlayout3.setObjectName("hboxlayout3")

        self.btnOK = QtGui.QPushButton(Dialog)
        self.btnOK.setObjectName("btnOK")
        self.hboxlayout3.addWidget(self.btnOK)

        self.btnCancel = QtGui.QPushButton(Dialog)
        self.btnCancel.setObjectName("btnCancel")
        self.hboxlayout3.addWidget(self.btnCancel)
        self.vboxlayout2.addLayout(self.hboxlayout3)
        self.hboxlayout2.addLayout(self.vboxlayout2)
        self.vboxlayout.addLayout(self.hboxlayout2)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(QtGui.QApplication.translate("Dialog", "Dialog", None, QtGui.QApplication.UnicodeUTF8))
        self.groupBox_2.setTitle(QtGui.QApplication.translate("Dialog", "Distribution Parameters", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("Dialog", "Random Generators:", None, QtGui.QApplication.UnicodeUTF8))
        self.btnOK.setText(QtGui.QApplication.translate("Dialog", "OK", None, QtGui.QApplication.UnicodeUTF8))
        self.btnCancel.setText(QtGui.QApplication.translate("Dialog", "Cancel", None, QtGui.QApplication.UnicodeUTF8))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    Dialog = QtGui.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())
