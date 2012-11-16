# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'G:\Programming\Projects\Python\gey2008\UI\ResultImportWnd.ui'
#
# Created: Tue May 20 16:08:56 2008
#      by: PyQt4 UI code generator 4.3.4-snapshot-20080328
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(QtCore.QSize(QtCore.QRect(0,0,294,201).size()).expandedTo(Dialog.minimumSizeHint()))

        self.vboxlayout = QtGui.QVBoxLayout(Dialog)
        self.vboxlayout.setObjectName("vboxlayout")

        self.hboxlayout = QtGui.QHBoxLayout()
        self.hboxlayout.setObjectName("hboxlayout")

        self.label = QtGui.QLabel(Dialog)
        self.label.setObjectName("label")
        self.hboxlayout.addWidget(self.label)

        self.comboFeatcls = QtGui.QComboBox(Dialog)
        self.comboFeatcls.setObjectName("comboFeatcls")
        self.hboxlayout.addWidget(self.comboFeatcls)
        self.vboxlayout.addLayout(self.hboxlayout)

        self.hboxlayout1 = QtGui.QHBoxLayout()
        self.hboxlayout1.setObjectName("hboxlayout1")

        self.btnImport = QtGui.QPushButton(Dialog)
        self.btnImport.setObjectName("btnImport")
        self.hboxlayout1.addWidget(self.btnImport)

        self.btnCancel = QtGui.QPushButton(Dialog)
        self.btnCancel.setObjectName("btnCancel")
        self.hboxlayout1.addWidget(self.btnCancel)
        self.vboxlayout.addLayout(self.hboxlayout1)

        self.retranslateUi(Dialog)
        QtCore.QObject.connect(self.btnCancel,QtCore.SIGNAL("clicked(bool)"),Dialog.reject)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        self.label.setText(QtGui.QApplication.translate("Dialog", "Feature Class:", None, QtGui.QApplication.UnicodeUTF8))
        self.btnImport.setText(QtGui.QApplication.translate("Dialog", "Import", None, QtGui.QApplication.UnicodeUTF8))
        self.btnCancel.setText(QtGui.QApplication.translate("Dialog", "Exit", None, QtGui.QApplication.UnicodeUTF8))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    Dialog = QtGui.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())
