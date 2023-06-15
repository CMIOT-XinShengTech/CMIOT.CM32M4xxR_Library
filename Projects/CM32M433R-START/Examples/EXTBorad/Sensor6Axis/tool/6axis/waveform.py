from PyQt5.QtWidgets import QApplication, QMainWindow, QHBoxLayout
from PyQt5.QtCore import QThread, pyqtSignal
import sys
import traceback
import serial
import serial.tools.list_ports
from wave_window import *
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg

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
        try:
            self.ser.read(self.ser.inWaiting())
            self.ser.readline()
            x_rad=0
            y_rad=0
            z_rad=0
            x_acc=0
            y_acc=0
            z_acc=0
            while True:
                try:
                    data = self.ser.readline().decode('utf-8', "ignore")
                    print(data)
                    tmp_str = str(data)
                    if '{GYRO}' in tmp_str:
                        start_index = tmp_str.index('{GYRO}') + 6
                        gyro_str = tmp_str[start_index:-2]
                        gyro_list = gyro_str.replace('rad/s', '').replace(' ', '').split(',')
                        x_rad = float(gyro_list[0])
                        y_rad = float(gyro_list[1])
                        z_rad = float(gyro_list[2])
                        self.runtest_signal.emit((x_rad, y_rad, z_rad, x_acc, y_acc, z_acc))

                    if '{ACC}' in tmp_str:
                        start_index = tmp_str.index('{ACC}') + 5
                        acc_str = tmp_str[start_index:-2]
                        acc_list = acc_str.replace('m/s2', '').replace(' ', '').split(',')
                        x_acc = float(acc_list[0])
                        y_acc = float(acc_list[1])
                        z_acc = float(acc_list[2])

                except Exception as main_error:
                    print(traceback.format_exc())

        except Exception as main_error:
            print(traceback.format_exc())
            exit(0)

class MainWindow(QMainWindow, Ui_MainWindow):
    serial_list = None
    ser = None
    ser_state = False
    ser_com = ''
    update_count = 0
    update_interval = 1
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)
        self.x_values = [x for x in range(200)]
        self.rad_values_1 = [0] * 200
        self.rad_values_2 = [0] * 200
        self.rad_values_3 = [0] * 200
        self.acc_values_1 = [0] * 200
        self.acc_values_2 = [0] * 200
        self.acc_values_3 = [0] * 200
        self.x_tick = range(0,201,10)
        self.y_tick = range(-20,21,5)

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

        self.setWindowTitle("6轴传感器波形_V1.0")


    def set_matplotlib(self):
        # 创建画布
        self.fig = plt.figure()
        self.canvas = FigureCanvasQTAgg(self.fig)

        # 把画布放进widget组件,设定位置
        self.hlayout = QHBoxLayout(self.graphicsView)
        self.hlayout.addWidget(self.canvas)

        self.ax1 = self.fig.add_subplot(211)
        self.ax2 = self.fig.add_subplot(212)
        self.ax1.grid(color='#E5E5E5')
        self.ax2.grid(color='#E5E5E5')
        self.ax1.set_ylim(-20,20)
        self.ax2.set_ylim(-20,20)

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
        x_rad, y_rad, z_rad, x_acc, y_acc, z_acc = update_plot
        del (self.acc_values_1[0])
        del (self.acc_values_2[0])
        del (self.acc_values_3[0])
        self.acc_values_1.append(x_acc)
        self.acc_values_2.append(y_acc)
        self.acc_values_3.append(z_acc)
        del (self.rad_values_1[0])
        del (self.rad_values_2[0])
        del (self.rad_values_3[0])
        self.rad_values_1.append(x_rad)
        self.rad_values_2.append(y_rad)
        self.rad_values_3.append(z_rad)
        
        self.update_count += 1
        if self.update_count < self.update_interval:
            return
        self.update_count = 0
        
        self.ax1.cla()
        self.ax1.set_ylim((-20, 20))
        self.ax1.plot(self.x_values, self.acc_values_1, label='x轴加速度', color='#FF0000', linewidth=2.0)
        self.ax1.plot(self.x_values, self.acc_values_2, label='y轴加速度', color='#76EE00', linewidth=2.0)
        self.ax1.plot(self.x_values, self.acc_values_3, label='z轴加速度', color='#7B68EE', linewidth=2.0)
        self.ax1.legend(loc='lower left')
        plt.subplot(2, 1, 1)
        plt.yticks(self.y_tick, self.y_tick, fontsize=12)
        self.ax1.grid(color='#E5E5E5')
        self.ax1.set_ylim(-20, 20)
        
        self.ax2.cla()
        self.ax2.set_ylim((-20, 20))
        self.ax2.plot(self.x_values, self.rad_values_1, label='x轴角速度', color='#FF0000', linewidth=2.0)
        self.ax2.plot(self.x_values, self.rad_values_2, label='y轴角速度', color='#76EE00', linewidth=2.0)
        self.ax2.plot(self.x_values, self.rad_values_3, label='z轴角速度', color='#7B68EE', linewidth=2.0)
        self.ax2.legend(loc='lower left')
        plt.subplot(2, 1, 2)
        plt.yticks(self.y_tick, self.y_tick, fontsize=12)
        self.ax2.grid(color='#E5E5E5')
        self.ax2.set_ylim(-20, 20)

        self.fig.canvas.draw()  # 画布重绘，self.figs.canvas


if __name__ == '__main__':
    app = QApplication(sys.argv)
    win = MainWindow()
    win.show()
    sys.exit(app.exec_())
    plt.ion()
