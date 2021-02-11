#!/usr/bin/python3
# -*- coding: utf-8 -*-

import socket
from struct import unpack
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import *
from PyQt5 import QtCore
from PyQt5.QtGui import *
from PyQt5 import QtWidgets
from PyQt5 import QtGui
from PyQt5.QtCore import *
#抓包与解析报头代码
def start():
    s=socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_TCP)
    while True:
        raw_packet = s.recvfrom(65565)
        packet = raw_packet[0]
        raw_iph = packet[0:20]
        # unpack(fmt, buffer) - 根据指定的格式化字符串来拆解给定的buffer
        # B 单字节的整型
        # H 双字节的整型
        # s bytes，前加数字表示取4字节的bytes
        iph = unpack("!BBHHHBBH4s4s", raw_iph)
        fields = {}
        fields["Version"] = iph[0] >> 4    # 版本字段与IP数据报头部共享一个字节，通过右移操作取得单独的版本字段
        fields["IP Header Length"] = (iph[0] & 0xF) * 4    # 首部长度字段的1代表4个字节
        fields["Type of Service"] = iph[1]    # 区分服务，一般情况下并不使用
        fields["Total Length"] = iph[2]    # IP首部+数据的总长度，即len(packet)
        fields["Identification"] = iph[3]    # 标识
        flags = iph[4] >> 13    # 标识位与片偏移共享2个字节，且最高位并且未使用
        fields["MF"] = 1 if flags & 1 else 0    # 测试最低位
        fields["DF"] = 1 if flags & 1 else 0    # 测试中间位
        fields["Fragment Offset"] = iph[4] & 0x1FFF    # 位与操作取得片偏移
        fields["Time to Live"] = iph[5]    # 生存时间，单位是跳数
        fields["Protocol"] = iph[6]    # 数据报携带的数据使用的协议，TCP为6
        fields["Header Checksum"] = iph[7]    # 首部校验和
        # socket.inet_ntoa(..)
        # - convert an ip address from 32-bit packed binary format to string format
        fields["Source Address"] = socket.inet_ntoa(iph[8])
        fields["Destination Address"] = socket.inet_ntoa(iph[9])

        for k, v in fields.items():    # 遍历打印，由于是dict，因此打印是无序的
            print(k, ':', v)
        print("")

class MainWindow(QMainWindow):
    #界面设置
    def __init__(self, *args, **kwargs):
        super(MainWindow, self).__init__(*args, **kwargs)
        # 设置窗口名称
        self.setWindowTitle("Package analyse")
        self.setFixedSize(1000, 600)
        self.center()
        self.status = self.statusBar()
        self.status.showMessage("gorgeousdays")
        # 设置整体布局 左右显示
        pagelayout = QHBoxLayout()
        # 创建左侧主窗口
        top_left_frame = QFrame(self)  
        # 绘制矩形面板
        top_left_frame.setFrameShape(QFrame.StyledPanel)
        top_left_frame.setFixedHeight(600)
        top_left_frame.setFixedSize(220,600)
        #　左边按钮为垂直布局
        button_layout = QVBoxLayout(top_left_frame)
     
        label1 = QLabel(self)
        label1.setFixedSize(200,60)
        label1.setText("MENU")
        label1.setAlignment(Qt.AlignCenter) #设置居中
        label1.setFont(QFont("Century",20,QFont.Bold))
        button_layout.addWidget(label1)
        pe = QPalette()
        pe.setColor(QPalette.WindowText,QColor(139,147, 194, 250))
        label1.setPalette(pe)
        
        # 开始按钮
        self.start_btn = QPushButton("开始抓包")
        self.start_btn.setFixedSize(200, 60)
        button_layout.addWidget(self.start_btn)
        self.start_btn.clicked.connect(self._start)
        self.start_btn.setStyleSheet('''QPushButton{background:rgb(106,118,200);border-radius:5px;color:white;font-family:AdobeHeitiStd;font-size:25px}
                                        QPushButton:hover{background:rgb(93,156,236);}
                                        QPushButton:pressed{background-color:rgb(74,137,220)}''')             
        # 清空列表按钮
        self.clear_btn=QPushButton("清空列表")
        self.clear_btn.setFixedSize(200, 60)
        button_layout.addWidget(self.clear_btn)
        self.clear_btn.clicked.connect(self._clear)
        self.clear_btn.setStyleSheet('''QPushButton{background:rgb(106,118,200);border-radius:5px;color:white;font-family:AdobeHeitiStd;font-size:25px}
                                        QPushButton:hover{background:rgb(93,156,236);}
                                        QPushButton:pressed{background-color:rgb(74,137,220)}''')     
        # 退出程序 按钮
        self.quit_btn = QPushButton("退出程序")
        self.quit_btn.setFixedSize(200, 60)
        button_layout.addWidget(self.quit_btn)
        self.quit_btn.clicked.connect(self._quit)
        self.quit_btn.setStyleSheet('''QPushButton{background:rgb(106,118,200);border-radius:5px;color:white;font-family:AdobeHeitiStd;font-size:25px}
                                        QPushButton:hover{background:rgb(93,156,236);}
                                        QPushButton:pressed{background-color:rgb(74,137,220)}''')

        self.tableWidget = QtWidgets.QTableWidget(self)

        self.tableWidget.setObjectName("tableWidget")
        self.tableWidget.setHorizontalScrollMode(QAbstractItemView.ScrollPerPixel)

        self.tableWidget.setColumnCount(10)
        self.tableWidget.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.tableWidget.setRowCount(0) # 8行4列
        
        self.tableWidget.setHorizontalHeaderLabels(["Version","IP Header Length","Total Length","MF","DF","Identification","Protocol","Header Checksum","Source Address","Destination Address"])
        #self.tableWidget.setItem(0, 0, QTableWidgetItem(str(query.value(8))))# 位置为第0行，第0列，后面为QTableWidgetItem对象，可以为str类型，int类型
        self.tableWidget.setItem(0, 1, QTableWidgetItem('Package analyse').setTextAlignment(Qt.AlignCenter))# 调用setTextAlignment()方法，设置文本居中显示
        #self.tableWidget.setItem(0, 2, QTableWidgetItem(int(query.value(4))))
        # self.tableWidget.setColumnWidth(1,200)
        # self.tableWidget.setColumnWidth(7,200)
        # self.tableWidget.setColumnWidth(8,200)
        # self.tableWidget.setColumnWidth(9,200)
        self.tableWidget.resizeColumnsToContents()
        self.tableWidget.resizeRowsToContents()

        
        right_frame = QFrame(self)
        right_frame.setFrameShape(QFrame.StyledPanel)
        right_frame.setStyleSheet('background-color:rgb(239,242,249);')

        #self.tableWidget.insertRow(0) #插入到第一行
        #right_frame.setFrameShadow(QFrame.Sunken) #设置阴影
        right_frame.setFixedSize(700,570)#right_frame.setLineWidth(600)
        self.right_layout = QVBoxLayout(right_frame)
        self.right_layout.addWidget(self.tableWidget)
        #right_frame.(self.tableWidget)
        

        widget = QWidget()
        pagelayout.addWidget(top_left_frame)
        pagelayout.addWidget(right_frame)
        widget.setLayout(pagelayout)
        self.setCentralWidget(widget)
        # self.right_layout.addWidget(self.tableWidget)
        # pagelayout.addWidget(top_left_frame)
        # pagelayout.setLayout(self.right_layout)
        

        self.flag=False
        items=["Version","IP Header Length","Total Length","MF","DF","Identification","Protocol","Header Checksum","Source Address","Destination Address"]
        row = self.tableWidget.rowCount()
        self.tableWidget.insertRow(row)
        for j in range(len(items)):
            item = QTableWidgetItem(str(items[j]))
            self.tableWidget.setItem(row,j,item)

        items=["Version","IP Header Length","Total Length","MF","DF","Identification","Protocol","Header Checksum","Source Address","Destination Address"]
        row = self.tableWidget.rowCount()
        self.tableWidget.insertRow(row)
        k=-1
        for j in items:
            k=k+1
            item = QTableWidgetItem(j)
            self.tableWidget.setItem(row,k,item)

    def center(self):
        #获取桌面长宽  获取窗口长宽 计算位置 移动
        screen = QDesktopWidget().screenGeometry()
        size = self.geometry()
        self.move((screen.width() - size.width()) / 2, (screen.height() - size.height()) / 2)
    def _show(self):
        self.flag=1-self.flag
        if self.flag:
            self.start_btn.setText("停止抓包")
        else:
            self.start_btn.setText("开始抓包")

    def _clear(self):
        rowPosition = self.tableWidget.rowCount()
        for rP in range(0, rowPosition)[::-1]:      
            self.tableWidget.removeRow(rP)
        pass
    def set_start(self):
        self.flag=1-self.flag
        if self.flag:
            self.start_btn.setText("停止抓包")
            #self.s=socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_TCP)
        else:
            self.start_btn.setText("开始抓包")
            self.s.close()
    def _start(self):
        s=socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_TCP)
            #with socket.socket(socket.AF_PACKET, socket.SOCK_RAW, socket.ntohs(0x0003)) as s:
        while True:
                raw_packet = self.s.recvfrom(65565)
                packet = raw_packet[0]
                raw_iph = packet[0:20]
                # unpack(fmt, buffer) - 根据指定的格式化字符串来拆解给定的buffer
                # B 单字节的整型
                # H 双字节的整型
                # s bytes，前加数字表示取4字节的bytes
                iph = unpack("!BBHHHBBH4s4s", raw_iph)
                fields = {}
                fields["Version"] = iph[0] >> 4    # 版本字段与IP数据报头部共享一个字节，通过右移操作取得单独的版本字段
                fields["IP Header Length"] = (iph[0] & 0xF) * 4    # 首部长度字段的1代表4个字节
                #fields["Type of Service"] = iph[1]    # 区分服务，一般情况下并不使用
                fields["Total Length"] = iph[2]    # IP首部+数据的总长度，即len(packet)
                fields["Identification"] = iph[3]    # 标识
                flags = iph[4] >> 13    # 标识位与片偏移共享2个字节，且最高位并且未使用
                fields["MF"] = 1 if flags & 1 else 0    # 测试最低位
                fields["DF"] = 1 if flags & 1 else 0    # 测试中间位
                fields["Fragment Offset"] = iph[4] & 0x1FFF    # 位与操作取得片偏移
                fields["Time to Live"] = iph[5]    # 生存时间，单位是跳数
                fields["Protocol"] = iph[6]    # 数据报携带的数据使用的协议，TCP为6
                fields["Header Checksum"] = iph[7]    # 首部校验和
                #socket.inet_ntoa(..)
                #- convert an ip address from 32-bit packed binary format to string format
                fields["Source Address"] = socket.inet_ntoa(iph[8])
                fields["Destination Address"] = socket.inet_ntoa(iph[9])
                p=-1
                item=QTableWidgetItem(v)
                self.tableWidget.setItem(row,p,item)
                row = self.tableWidget.rowCount()
                self.tableWidget.insertRow(row)
                for k, v in fields.items():    # 遍历打印，由于是dict，因此打印是无序的
                    p=p+1
                    item=QTableWidgetItem(v)
                    self.tableWidget.setItem(row,p,item)
                    print(k, ':', v)
                print("")

        #with socket.socket(socket.AF_PACKET, socket.SOCK_RAW, socket.ntohs(0x0003)) as s:
        
    def _quit(self):
        self.close()

if __name__ == "__main__":
    app=QtWidgets.QApplication([])
    my_gui= MainWindow()
    #win=cure.Windows(gui(),'name',True) #实现对窗口的美化
    my_gui.show()
    app.exec_()