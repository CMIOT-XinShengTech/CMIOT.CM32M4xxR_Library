# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'wave_window.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(809, 608)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.centralwidget)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.frame = QtWidgets.QFrame(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame.sizePolicy().hasHeightForWidth())
        self.frame.setSizePolicy(sizePolicy)
        self.frame.setMinimumSize(QtCore.QSize(240, 240))
        self.frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame.setObjectName("frame")
        self.comboBox = QtWidgets.QComboBox(self.frame)
        self.comboBox.setGeometry(QtCore.QRect(10, 10, 221, 22))
        self.comboBox.setObjectName("comboBox")
        self.btn_refresh = QtWidgets.QPushButton(self.frame)
        self.btn_refresh.setGeometry(QtCore.QRect(10, 50, 111, 28))
        self.btn_refresh.setObjectName("btn_refresh")
        self.btn_openserial = QtWidgets.QPushButton(self.frame)
        self.btn_openserial.setGeometry(QtCore.QRect(10, 90, 111, 28))
        self.btn_openserial.setObjectName("btn_openserial")
        self.btn_closeserial = QtWidgets.QPushButton(self.frame)
        self.btn_closeserial.setGeometry(QtCore.QRect(130, 90, 101, 28))
        self.btn_closeserial.setObjectName("btn_closeserial")
        self.label = QtWidgets.QLabel(self.frame)
        self.label.setGeometry(QtCore.QRect(10, 130, 201, 16))
        self.label.setObjectName("label")
        self.btn_run = QtWidgets.QPushButton(self.frame)
        self.btn_run.setGeometry(QtCore.QRect(10, 230, 111, 28))
        self.btn_run.setObjectName("btn_run")
        self.btn_stop = QtWidgets.QPushButton(self.frame)
        self.btn_stop.setGeometry(QtCore.QRect(130, 230, 101, 28))
        self.btn_stop.setObjectName("btn_stop")
        self.lineEdit_update_interval = QtWidgets.QLineEdit(self.frame)
        self.lineEdit_update_interval.setGeometry(QtCore.QRect(100, 176, 91, 21))
        self.lineEdit_update_interval.setObjectName("lineEdit_update_interval")
        self.label_2 = QtWidgets.QLabel(self.frame)
        self.label_2.setGeometry(QtCore.QRect(10, 180, 72, 15))
        self.label_2.setObjectName("label_2")
        self.horizontalLayout.addWidget(self.frame)
        self.frame_2 = QtWidgets.QFrame(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame_2.sizePolicy().hasHeightForWidth())
        self.frame_2.setSizePolicy(sizePolicy)
        self.frame_2.setMinimumSize(QtCore.QSize(540, 540))
        self.frame_2.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_2.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_2.setObjectName("frame_2")
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout(self.frame_2)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.graphicsView = QtWidgets.QGraphicsView(self.frame_2)
        self.graphicsView.setObjectName("graphicsView")
        self.horizontalLayout_2.addWidget(self.graphicsView)
        self.horizontalLayout.addWidget(self.frame_2)
        self.frame_2.raise_()
        self.frame.raise_()
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 809, 26))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.btn_refresh.setText(_translate("MainWindow", "刷新串口"))
        self.btn_openserial.setText(_translate("MainWindow", "打开串口"))
        self.btn_closeserial.setText(_translate("MainWindow", "关闭串口"))
        self.label.setText(_translate("MainWindow", "串口未打开"))
        self.btn_run.setText(_translate("MainWindow", "运行"))
        self.btn_stop.setText(_translate("MainWindow", "停止"))
        self.lineEdit_update_interval.setText(_translate("MainWindow", "1"))
        self.label_2.setText(_translate("MainWindow", "刷新间隔"))
