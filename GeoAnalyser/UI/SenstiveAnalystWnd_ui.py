# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'G:\Programming\Projects\Python\gey2008\UI\SenstiveAnalystWnd.ui'
#
# Created: Wed May 21 20:47:12 2008
#      by: PyQt4 UI code generator 4.3.4-snapshot-20080328
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(QtCore.QSize(QtCore.QRect(0,0,509,363).size()).expandedTo(Dialog.minimumSizeHint()))

        self.hboxlayout = QtGui.QHBoxLayout(Dialog)
        self.hboxlayout.setObjectName("hboxlayout")

        self.groupBox = QtGui.QGroupBox(Dialog)
        self.groupBox.setObjectName("groupBox")

        self.vboxlayout = QtGui.QVBoxLayout(self.groupBox)
        self.vboxlayout.setObjectName("vboxlayout")

        self.tableView = QtGui.QTableView(self.groupBox)
        self.tableView.setObjectName("tableView")
        self.vboxlayout.addWidget(self.tableView)
        self.hboxlayout.addWidget(self.groupBox)

        self.vboxlayout1 = QtGui.QVBoxLayout()
        self.vboxlayout1.setObjectName("vboxlayout1")

        self.groupBox_2 = QtGui.QGroupBox(Dialog)
        self.groupBox_2.setObjectName("groupBox_2")

        self.vboxlayout2 = QtGui.QVBoxLayout(self.groupBox_2)
        self.vboxlayout2.setObjectName("vboxlayout2")

        self.btnAbsChg = QtGui.QPushButton(self.groupBox_2)
        self.btnAbsChg.setObjectName("btnAbsChg")
        self.vboxlayout2.addWidget(self.btnAbsChg)

        self.btnRelChg = QtGui.QPushButton(self.groupBox_2)
        self.btnRelChg.setObjectName("btnRelChg")
        self.vboxlayout2.addWidget(self.btnRelChg)

        self.btnSensLst = QtGui.QPushButton(self.groupBox_2)
        self.btnSensLst.setObjectName("btnSensLst")
        self.vboxlayout2.addWidget(self.btnSensLst)
        self.vboxlayout1.addWidget(self.groupBox_2)

        spacerItem = QtGui.QSpacerItem(154,21,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Expanding)
        self.vboxlayout1.addItem(spacerItem)

        self.groupBox_3 = QtGui.QGroupBox(Dialog)
        self.groupBox_3.setObjectName("groupBox_3")

        self.vboxlayout3 = QtGui.QVBoxLayout(self.groupBox_3)
        self.vboxlayout3.setObjectName("vboxlayout3")

        self.btnThVal = QtGui.QPushButton(self.groupBox_3)
        self.btnThVal.setObjectName("btnThVal")
        self.vboxlayout3.addWidget(self.btnThVal)

        self.btnCrtDegs = QtGui.QPushButton(self.groupBox_3)
        self.btnCrtDegs.setObjectName("btnCrtDegs")
        self.vboxlayout3.addWidget(self.btnCrtDegs)

        self.btnSens = QtGui.QPushButton(self.groupBox_3)
        self.btnSens.setObjectName("btnSens")
        self.vboxlayout3.addWidget(self.btnSens)
        self.vboxlayout1.addWidget(self.groupBox_3)

        spacerItem1 = QtGui.QSpacerItem(154,16,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Expanding)
        self.vboxlayout1.addItem(spacerItem1)

        self.btnSave = QtGui.QPushButton(Dialog)
        self.btnSave.setObjectName("btnSave")
        self.vboxlayout1.addWidget(self.btnSave)

        self.btnCancel = QtGui.QPushButton(Dialog)
        self.btnCancel.setObjectName("btnCancel")
        self.vboxlayout1.addWidget(self.btnCancel)
        self.hboxlayout.addLayout(self.vboxlayout1)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        self.groupBox.setTitle(QtGui.QApplication.translate("Dialog", "Overall Results", None, QtGui.QApplication.UnicodeUTF8))
        self.groupBox_2.setTitle(QtGui.QApplication.translate("Dialog", "Most Critical Criteria", None, QtGui.QApplication.UnicodeUTF8))
        self.btnAbsChg.setText(QtGui.QApplication.translate("Dialog", "Abstract Change", None, QtGui.QApplication.UnicodeUTF8))
        self.btnRelChg.setText(QtGui.QApplication.translate("Dialog", "Related Change", None, QtGui.QApplication.UnicodeUTF8))
        self.btnSensLst.setText(QtGui.QApplication.translate("Dialog", "Sensitive List", None, QtGui.QApplication.UnicodeUTF8))
        self.groupBox_3.setTitle(QtGui.QApplication.translate("Dialog", "Most Critical Aij", None, QtGui.QApplication.UnicodeUTF8))
        self.btnThVal.setText(QtGui.QApplication.translate("Dialog", "Threshold Values", None, QtGui.QApplication.UnicodeUTF8))
        self.btnCrtDegs.setText(QtGui.QApplication.translate("Dialog", "Critically Degrees", None, QtGui.QApplication.UnicodeUTF8))
        self.btnSens.setText(QtGui.QApplication.translate("Dialog", "Sensitives", None, QtGui.QApplication.UnicodeUTF8))
        self.btnSave.setText(QtGui.QApplication.translate("Dialog", "Save As CSV ...", None, QtGui.QApplication.UnicodeUTF8))
        self.btnCancel.setText(QtGui.QApplication.translate("Dialog", "Exit", None, QtGui.QApplication.UnicodeUTF8))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    Dialog = QtGui.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())
