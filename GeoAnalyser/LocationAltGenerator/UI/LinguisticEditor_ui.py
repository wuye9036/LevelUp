# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'G:\Programming\Projects\Python\gey2008\LocationAltGenerator\UI\LinguisticEditor.ui'
#
# Created: Wed May 07 20:21:55 2008
#      by: PyQt4 UI code generator 4.3.4-snapshot-20080328
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(QtCore.QSize(QtCore.QRect(0,0,711,450).size()).expandedTo(Dialog.minimumSizeHint()))

        self.vboxlayout = QtGui.QVBoxLayout(Dialog)
        self.vboxlayout.setObjectName("vboxlayout")

        self.groupBox = QtGui.QGroupBox(Dialog)

        font = QtGui.QFont()
        font.setFamily("Palatino Linotype")
        font.setPointSize(10)
        self.groupBox.setFont(font)
        self.groupBox.setObjectName("groupBox")

        self.vboxlayout1 = QtGui.QVBoxLayout(self.groupBox)
        self.vboxlayout1.setObjectName("vboxlayout1")

        self.tableView = QtGui.QTableView(self.groupBox)
        self.tableView.setContextMenuPolicy(QtCore.Qt.ActionsContextMenu)
        self.tableView.setSelectionMode(QtGui.QAbstractItemView.SingleSelection)
        self.tableView.setObjectName("tableView")
        self.vboxlayout1.addWidget(self.tableView)
        self.vboxlayout.addWidget(self.groupBox)

        spacerItem = QtGui.QSpacerItem(20,15,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Fixed)
        self.vboxlayout.addItem(spacerItem)

        self.hboxlayout = QtGui.QHBoxLayout()
        self.hboxlayout.setObjectName("hboxlayout")

        spacerItem1 = QtGui.QSpacerItem(40,20,QtGui.QSizePolicy.Expanding,QtGui.QSizePolicy.Minimum)
        self.hboxlayout.addItem(spacerItem1)

        self.checkBtn = QtGui.QPushButton(Dialog)

        font = QtGui.QFont()
        font.setFamily("Palatino Linotype")
        self.checkBtn.setFont(font)
        self.checkBtn.setObjectName("checkBtn")
        self.hboxlayout.addWidget(self.checkBtn)

        self.acceptBtn = QtGui.QPushButton(Dialog)

        font = QtGui.QFont()
        font.setFamily("Palatino Linotype")
        self.acceptBtn.setFont(font)
        self.acceptBtn.setObjectName("acceptBtn")
        self.hboxlayout.addWidget(self.acceptBtn)

        self.cancleBtn = QtGui.QPushButton(Dialog)

        font = QtGui.QFont()
        font.setFamily("Palatino Linotype")
        self.cancleBtn.setFont(font)
        self.cancleBtn.setObjectName("cancleBtn")
        self.hboxlayout.addWidget(self.cancleBtn)
        self.vboxlayout.addLayout(self.hboxlayout)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(QtGui.QApplication.translate("Dialog", "Dialog", None, QtGui.QApplication.UnicodeUTF8))
        self.groupBox.setTitle(QtGui.QApplication.translate("Dialog", "Linguistic Value Table", None, QtGui.QApplication.UnicodeUTF8))
        self.checkBtn.setText(QtGui.QApplication.translate("Dialog", "检查", None, QtGui.QApplication.UnicodeUTF8))
        self.acceptBtn.setText(QtGui.QApplication.translate("Dialog", "确认", None, QtGui.QApplication.UnicodeUTF8))
        self.cancleBtn.setText(QtGui.QApplication.translate("Dialog", "取消", None, QtGui.QApplication.UnicodeUTF8))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    Dialog = QtGui.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())
