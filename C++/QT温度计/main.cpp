#include "MainWidget.h"

// 主程序所在的目录
#include <QApplication>

int main(int argc, char *argv[])
{
    // 生成一个主程序对象 公开的一些配置 完成外部信号的接收
    QApplication a(argc, argv);
    // 这是主显示界面
    MainWidget w;
    // 显示功能
    w.show();
    return a.exec();
}
