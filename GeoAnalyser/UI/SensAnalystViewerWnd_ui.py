# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'G:\Programming\Projects\Python\gey2008\UI\SensAnalystViewerWnd.ui'
#
# Created: Wed May 21 20:46:45 2008
#      by: PyQt4 UI code generator 4.3.4-snapshot-20080328
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(QtCore.QSize(QtCore.QRect(0,0,391,326).size()).expandedTo(Dialog.minimumSizeHint()))

        self.vboxlayout = QtGui.QVBoxLayout(Dialog)
        self.vboxlayout.setObjectName("vboxlayout")

        self.groupBox = QtGui.QGroupBox(Dialog)
        self.groupBox.setObjectName("groupBox")

        self.vboxlayout1 = QtGui.QVBoxLayout(self.groupBox)
        self.vboxlayout1.setObjectName("vboxlayout1")

        self.tableView = QtGui.QTableView(self.groupBox)
        self.tableView.setObjectName("tableView")
        self.vboxlayout1.addWidget(self.tableView)
        self.vboxlayout.addWidget(self.groupBox)

        self.hboxlayout = QtGui.QHBoxLayout()
        self.hboxlayout.setObjectName("hboxlayout")

        spacerItem = QtGui.QSpacerItem(40,20,QtGui.QSizePolicy.Expanding,QtGui.QSizePolicy.Minimum)
        self.hboxlayout.addItem(spacerItem)

        self.saveBtn = QtGui.QPushButton(Dialog)
        self.saveBtn.setObjectName("saveBtn")
        self.hboxlayout.addWidget(self.saveBtn)

        self.cancelBtn = QtGui.QPushButton(Dialog)
        self.cancelBtn.setObjectName("cancelBtn")
        self.hboxlayout.addWidget(self.cancelBtn)
        self.vboxlayout.addLayout(self.hboxlayout)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        self.groupBox.setTitle(QtGui.QApplication.translate("Dialog", "Viewer", None, QtGui.QApplication.UnicodeUTF8))
        self.saveBtn.setText(QtGui.QApplication.translate("Dialog", "Save As CSV...", None, QtGui.QApplication.UnicodeUTF8))
        self.cancelBtn.setText(QtGui.QApplication.translate("Dialog", "Exit", None, QtGui.QApplication.UnicodeUTF8))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    Dialog = QtGui.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())
