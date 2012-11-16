# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'G:\Programming\Projects\Python\gey2008\UI\ProximityBuilderWnd.ui'
#
# Created: Wed May 21 20:46:19 2008
#      by: PyQt4 UI code generator 4.3.4-snapshot-20080328
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(QtCore.QSize(QtCore.QRect(0,0,333,198).size()).expandedTo(Dialog.minimumSizeHint()))

        self.vboxlayout = QtGui.QVBoxLayout(Dialog)
        self.vboxlayout.setObjectName("vboxlayout")

        self.hboxlayout = QtGui.QHBoxLayout()
        self.hboxlayout.setObjectName("hboxlayout")

        self.label_2 = QtGui.QLabel(Dialog)
        self.label_2.setObjectName("label_2")
        self.hboxlayout.addWidget(self.label_2)

        self.comboLocFeatcls = QtGui.QComboBox(Dialog)
        self.comboLocFeatcls.setObjectName("comboLocFeatcls")
        self.hboxlayout.addWidget(self.comboLocFeatcls)
        self.vboxlayout.addLayout(self.hboxlayout)

        self.hboxlayout1 = QtGui.QHBoxLayout()
        self.hboxlayout1.setObjectName("hboxlayout1")

        self.label_3 = QtGui.QLabel(Dialog)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred,QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_3.sizePolicy().hasHeightForWidth())
        self.label_3.setSizePolicy(sizePolicy)
        self.label_3.setObjectName("label_3")
        self.hboxlayout1.addWidget(self.label_3)

        self.comboCrtName = QtGui.QComboBox(Dialog)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred,QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.comboCrtName.sizePolicy().hasHeightForWidth())
        self.comboCrtName.setSizePolicy(sizePolicy)
        self.comboCrtName.setObjectName("comboCrtName")
        self.hboxlayout1.addWidget(self.comboCrtName)
        self.vboxlayout.addLayout(self.hboxlayout1)

        self.hboxlayout2 = QtGui.QHBoxLayout()
        self.hboxlayout2.setObjectName("hboxlayout2")

        self.label = QtGui.QLabel(Dialog)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred,QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label.sizePolicy().hasHeightForWidth())
        self.label.setSizePolicy(sizePolicy)
        self.label.setObjectName("label")
        self.hboxlayout2.addWidget(self.label)

        self.comboProxAlgoName = QtGui.QComboBox(Dialog)

        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred,QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.comboProxAlgoName.sizePolicy().hasHeightForWidth())
        self.comboProxAlgoName.setSizePolicy(sizePolicy)
        self.comboProxAlgoName.setObjectName("comboProxAlgoName")
        self.hboxlayout2.addWidget(self.comboProxAlgoName)
        self.vboxlayout.addLayout(self.hboxlayout2)

        self.gridlayout = QtGui.QGridLayout()
        self.gridlayout.setObjectName("gridlayout")

        self.btnProxAnalystAll = QtGui.QPushButton(Dialog)
        self.btnProxAnalystAll.setObjectName("btnProxAnalystAll")
        self.gridlayout.addWidget(self.btnProxAnalystAll,0,0,1,1)

        self.btnAltCmp = QtGui.QPushButton(Dialog)
        self.btnAltCmp.setObjectName("btnAltCmp")
        self.gridlayout.addWidget(self.btnAltCmp,0,1,1,1)

        self.btnCancel = QtGui.QPushButton(Dialog)
        self.btnCancel.setObjectName("btnCancel")
        self.gridlayout.addWidget(self.btnCancel,1,1,1,1)
        self.vboxlayout.addLayout(self.gridlayout)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(QtGui.QApplication.translate("Dialog", "Dialog", None, QtGui.QApplication.UnicodeUTF8))
        self.label_2.setText(QtGui.QApplication.translate("Dialog", "Location Feature Class:", None, QtGui.QApplication.UnicodeUTF8))
        self.label_3.setText(QtGui.QApplication.translate("Dialog", "Criteria Name:", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("Dialog", "Proximity Method:", None, QtGui.QApplication.UnicodeUTF8))
        self.btnProxAnalystAll.setText(QtGui.QApplication.translate("Dialog", "Proximity Analyst All", None, QtGui.QApplication.UnicodeUTF8))
        self.btnAltCmp.setText(QtGui.QApplication.translate("Dialog", "Alt. Comparison", None, QtGui.QApplication.UnicodeUTF8))
        self.btnCancel.setText(QtGui.QApplication.translate("Dialog", "Exit", None, QtGui.QApplication.UnicodeUTF8))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    Dialog = QtGui.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())
