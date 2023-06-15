from PyQt5.QtWidgets import QApplication, QMainWindow, QHBoxLayout
from PyQt5.QtCore import QThread, pyqtSignal
import sys
import traceback
import serial
import serial.tools.list_ports
from mainwindow import *
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg
import numpy

plt.rcParams["font.sans-serif"] = ["Simhei"]  # 设置默认字体
plt.rcParams["axes.unicode_minus"] = False  # 坐标轴正确显示正负号

# ============ 运行前设置变量 ============


# ============ 设置变量结束 ============
class ThreadRunTest(QThread):
    runtest_signal = pyqtSignal(tuple)
    def __init__(self, ser):
        super(ThreadRunTest, self).__init__()
        self.ser = ser
    def run(self):
        self.ser.read(self.ser.inWaiting())
        self.ser.readline()
        while True:
            try:
                data = self.ser.readline()
                print(data)
                if data != '':
                    list1 = str(data)[2:-7].split(' ')
                    x_data = int(list1[0])
                    y_data = int(list1[1])
                    self.runtest_signal.emit((x_data,y_data))
            except Exception as main_error:
                print(traceback.format_exc())


class MainWindow(QMainWindow, Ui_MainWindow):
    serial_list = None
    ser = None
    ser_state = False
    ser_com = ''
    x_max = 4095
    y_max = 4095
    update_count = 0
    update_interval = 1
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)
        # 调用set_matplotlib方法将matplotlib嵌入进来（该方法需要自己写进来，后边会写方法）
        self.set_matplotlib()

        
        # 获取所有打开的串口及信息
        self.serial_list = list(serial.tools.list_ports.comports())

        for item in self.serial_list:
            self.comboBox.addItem('%s:%s'%(str(item).split(' - ')[0],str(item).split(' - ')[1].split(' (')[0]))

        self.ser_com = self.comboBox.currentText().split(':')[0]

        self.comboBox.currentIndexChanged.connect(self.selectionchange)
        self.btn_run.clicked.connect(self.slot_btn_run)
        self.btn_run.setEnabled(True)
        self.btn_stop.clicked.connect(self.slot_btn_stop)
        self.btn_stop.setEnabled(False)
        self.btn_openserial.clicked.connect(self.slot_btn_ser_on)
        self.btn_openserial.setEnabled(True)
        self.btn_closeserial.clicked.connect(self.slot_btn_ser_off)
        self.btn_closeserial.setEnabled(True)
        self.btn_refresh.clicked.connect(self.slot_btn_refresh)
        self.btn_refresh.setEnabled(True)

        self.setWindowTitle("摇杆演示_V1.0")


    def set_matplotlib(self):
        # 创建画布
        self.fig = plt.figure()
        self.canvas = FigureCanvasQTAgg(self.fig)
 
        # 把画布放进widget组件,设定位置
        self.hlayout = QHBoxLayout(self.graphicsView)
        self.hlayout.addWidget(self.canvas)
 
        # 初始化matplotlib显示区域
        self.ax = self.fig.subplots()
        self.ax.set_xlim(0, self.x_max)
        self.ax.set_ylim(0, self.y_max)
        self.ax.set_yticks(numpy.arange(0,self.x_max,self.x_max))
        self.ax.set_xticks(numpy.arange(0,self.y_max,self.y_max))
        self.ax.set_title('示例')
        self.ax.set_xlabel('x轴')
        self.ax.set_ylabel('y轴')
        self.ax.scatter(2048, 2048, s=4000)
        self.fig.canvas.draw()  # 画布重绘，self.figs.canvas
        
            
    def slot_btn_ser_on(self):
        try:
            self.ser = serial.Serial(self.ser_com, 115200, timeout=0.5, stopbits=1, parity=serial.PARITY_NONE)
            self.label.setText('串口已打开')
            self.ser_state = True
        except Exception as main_error:
            print(traceback.format_exc())

    def slot_btn_ser_off(self):
        try:
            self.ser.close()
            self.label.setText('串口未打开')
            self.ser_state = False
        except Exception as main_error:
            print(traceback.format_exc())

    def slot_btn_refresh(self):
        self.comboBox.clear()
        self.serial_list = list(serial.tools.list_ports.comports())
        for item in self.serial_list:
            self.comboBox.addItem('%s:%s'%(str(item).split(' - ')[0],str(item).split(' - ')[1].split(' (')[0]))

    def selectionchange(self, i):
        self.ser_com = self.comboBox.currentText().split(':')[0]

    def slot_btn_run(self):
        tmp_text = self.label.text()
        try:
            self.update_interval = int(self.lineEdit_update_interval.text())
        except:
            self.label.setText(tmp_text + '  刷新间隔需要为正整数')

        try:
            if not self.ser_state:
                self.label.setText(tmp_text + '  需要先打开串口！')
                return
            self.x_max = int(self.lineEdit_xmax.text())
            self.y_max = int(self.lineEdit_ymax.text())
            self.thread_run = ThreadRunTest(self.ser)
            self.thread_run.runtest_signal.connect(self.update_plot)
            self.thread_run.start()

            self.btn_run.setEnabled(False)
            self.btn_stop.setEnabled(True)
        except Exception as main_error:
            print(traceback.format_exc())

    def slot_btn_stop(self):
        self.thread_run.terminate()
        self.thread_run.wait()
        self.thread_run.deleteLater()
        self.btn_run.setEnabled(True)
        self.btn_stop.setEnabled(False)
        
    def update_plot(self, update_plot):
        self.update_count += 1
        if self.update_count < self.update_interval:
            return
        self.update_count = 0
        
        x_position = update_plot[0]
        y_position = update_plot[1]
        # 绘图
        self.ax.cla()
        self.ax.set_xlim(0, self.x_max)
        self.ax.set_ylim(0, self.y_max)
        self.ax.set_yticks(numpy.arange(0,self.x_max,self.x_max))
        self.ax.set_xticks(numpy.arange(0,self.y_max,self.y_max))
        self.ax.set_title('示例')
        self.ax.set_xlabel('x轴')
        self.ax.set_ylabel('y轴')
        self.ax.scatter(x_position, y_position, s=4000)
        self.fig.canvas.draw()  # 画布重绘，self.figs.canvas


if __name__ == '__main__':
    app = QApplication(sys.argv)
    win = MainWindow()
    win.show()
    sys.exit(app.exec_())
    plt.ion()  # 开启一个画图的窗口
