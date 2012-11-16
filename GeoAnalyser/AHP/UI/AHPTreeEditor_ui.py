# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'AHPTreeEditor.ui'
#
# Created: Sat Aug 02 20:58:06 2008
#      by: PyQt4 UI code generator 4.3.4-snapshot-20080328
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_AHPEditor(object):
    def setupUi(self, AHPEditor):
        AHPEditor.setObjectName("AHPEditor")
        AHPEditor.setWindowModality(QtCore.Qt.ApplicationModal)
        AHPEditor.resize(QtCore.QSize(QtCore.QRect(0,0,427,329).size()).expandedTo(AHPEditor.minimumSizeHint()))

        self.vboxlayout = QtGui.QVBoxLayout(AHPEditor)
        self.vboxlayout.setObjectName("vboxlayout")

        self.ahpViewGroup = QtGui.QGroupBox(AHPEditor)
        self.ahpViewGroup.setObjectName("ahpViewGroup")

        self.hboxlayout = QtGui.QHBoxLayout(self.ahpViewGroup)
        self.hboxlayout.setObjectName("hboxlayout")

        self.aphTreeView = QtGui.QTreeView(self.ahpViewGroup)

        font = QtGui.QFont()
        font.setFamily("Palatino Linotype")
        font.setPointSize(10)
        self.aphTreeView.setFont(font)
        self.aphTreeView.setContextMenuPolicy(QtCore.Qt.ActionsContextMenu)
        self.aphTreeView.setEditTriggers(QtGui.QAbstractItemView.DoubleClicked|QtGui.QAbstractItemView.EditKeyPressed|QtGui.QAbstractItemView.NoEditTriggers|QtGui.QAbstractItemView.SelectedClicked)
        self.aphTreeView.setTabKeyNavigation(True)
        self.aphTreeView.setObjectName("aphTreeView")
        self.hboxlayout.addWidget(self.aphTreeView)
        self.vboxlayout.addWidget(self.ahpViewGroup)

        spacerItem = QtGui.QSpacerItem(407,10,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Fixed)
        self.vboxlayout.addItem(spacerItem)

        self.hboxlayout1 = QtGui.QHBoxLayout()
        self.hboxlayout1.setObjectName("hboxlayout1")

        spacerItem1 = QtGui.QSpacerItem(40,20,QtGui.QSizePolicy.Expanding,QtGui.QSizePolicy.Minimum)
        self.hboxlayout1.addItem(spacerItem1)

        self.btnRandGen = QtGui.QPushButton(AHPEditor)
        self.btnRandGen.setObjectName("btnRandGen")
        self.hboxlayout1.addWidget(self.btnRandGen)

        spacerItem2 = QtGui.QSpacerItem(10,20,QtGui.QSizePolicy.Preferred,QtGui.QSizePolicy.Minimum)
        self.hboxlayout1.addItem(spacerItem2)

        self.acceptBtn = QtGui.QPushButton(AHPEditor)
        self.acceptBtn.setObjectName("acceptBtn")
        self.hboxlayout1.addWidget(self.acceptBtn)

        spacerItem3 = QtGui.QSpacerItem(10,20,QtGui.QSizePolicy.Preferred,QtGui.QSizePolicy.Minimum)
        self.hboxlayout1.addItem(spacerItem3)

        self.cancelBtn = QtGui.QPushButton(AHPEditor)
        self.cancelBtn.setObjectName("cancelBtn")
        self.hboxlayout1.addWidget(self.cancelBtn)

        spacerItem4 = QtGui.QSpacerItem(10,20,QtGui.QSizePolicy.Preferred,QtGui.QSizePolicy.Minimum)
        self.hboxlayout1.addItem(spacerItem4)

        self.applyBtn = QtGui.QPushButton(AHPEditor)
        self.applyBtn.setObjectName("applyBtn")
        self.hboxlayout1.addWidget(self.applyBtn)
        self.vboxlayout.addLayout(self.hboxlayout1)

        self.retranslateUi(AHPEditor)
        QtCore.QObject.connect(self.cancelBtn,QtCore.SIGNAL("clicked()"),AHPEditor.reject)
        QtCore.QMetaObject.connectSlotsByName(AHPEditor)

    def retranslateUi(self, AHPEditor):
        AHPEditor.setWindowTitle(QtGui.QApplication.translate("AHPEditor", "AHP层次树编辑器", None, QtGui.QApplication.UnicodeUTF8))
        self.ahpViewGroup.setTitle(QtGui.QApplication.translate("AHPEditor", "AHP要素层次树", None, QtGui.QApplication.UnicodeUTF8))
        self.btnRandGen.setText(QtGui.QApplication.translate("AHPEditor", "随机化", None, QtGui.QApplication.UnicodeUTF8))
        self.acceptBtn.setText(QtGui.QApplication.translate("AHPEditor", "确定", None, QtGui.QApplication.UnicodeUTF8))
        self.cancelBtn.setText(QtGui.QApplication.translate("AHPEditor", "取消", None, QtGui.QApplication.UnicodeUTF8))
        self.applyBtn.setText(QtGui.QApplication.translate("AHPEditor", "应用", None, QtGui.QApplication.UnicodeUTF8))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    AHPEditor = QtGui.QDialog()
    ui = Ui_AHPEditor()
    ui.setupUi(AHPEditor)
    AHPEditor.show()
    sys.exit(app.exec_())
