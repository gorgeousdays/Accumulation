#include "MainWidget.h"
#include "Thermomter.h"
#include <QDebug>
#include <QTimer>
#include "DashBoard.h"
#include <QMediaPlayer>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QTime>
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),chartView(new QChartView(this))
{
    // 生成对象 隐式生成，对象内容存放在栈区 所有的属性采取默认值
//    Thermomter t1;
//    qDebug() << t1.showMinTemp();
//    qDebug() << t1.showMaxTemp();
//    t1.measureTemp();
//    qDebug() << t1.showCurrentTemp();

//    // 显示调用
//    Thermomter t2(this,20,60);
//    qDebug() << t2.showMinTemp();
//    qDebug() << t2.showMaxTemp();
//    t2.measureTemp();
//    qDebug() << t2.showCurrentTemp();

//    // 隐式在堆区创建，都是默认值
//    Thermomter *t3 = new Thermomter;
//    qDebug() << t3->showMinTemp();
//    qDebug() << t3->showMaxTemp();
//    t3->measureTemp();
//    qDebug() << t3->showCurrentTemp();

    // 构造函数不会直接继承下来
    EThermometer *t4 = new EThermometer();
    qDebug() << t4->showMinTemp();
    qDebug() << t4->showMaxTemp();
    t4->startUp();
    qDebug() << t4->showCurrentTemp();

    createChart(t4->showMinTemp(),t4->showMaxTemp(),20,60,80);
    chartView->setGeometry(310,0,600,400);
    chartView->setChart(mainChart);

    // 创建仪表盘数据 一般对于可以显示的内容，this代表添加到界面上
    DashBoard *dash = new DashBoard(this);
    // 设置坐标与大小
    dash->setGeometry(0,0,300,300);
    // 设置基本的展示内容
    dash->configsValues(t4->showMaxTemp(),t4->showMinTemp(),20,60,80);
    // 设置显示的图例和单位
    dash->setInfomation("温度", "℃");

    // 报警音配置
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/alertResource/alert2.mp3"));

    // 光配置
    maskWidget = new QWidget(this);
    maskWidget->setGeometry(0,0,1000,800);
    maskWidget->setStyleSheet("background-color:red");

    // 转换widget到图片
    QGraphicsOpacityEffect *ope = new QGraphicsOpacityEffect;
    maskWidget->setGraphicsEffect(ope);
    ope->setOpacity(0);

    QPropertyAnimation *pAni = new QPropertyAnimation(ope, "opacity");
    pAni->setDuration(300);
    pAni->setLoopCount(6);
    pAni->setStartValue(1);
    pAni->setEndValue(0);

    qreal passMinute = QTime::currentTime().minute();

    QTimer *timer = new QTimer;
    connect(timer,&QTimer::timeout,[t4,dash,player,pAni,this,passMinute]()mutable{
        qDebug() << t4->showCurrentTemp();
        dash->setValue(t4->showCurrentTemp());

        if(passMinute != QTime::currentTime().minute())
        {
            dotSeries->clear();
            connectLineSeries->clear();
            passMinute = QTime::currentTime().minute();
        }

        connectLineSeries->append(QTime::currentTime().second(), t4->showCurrentTemp());
        dotSeries->append(QTime::currentTime().second(), t4->showCurrentTemp());

        if(t4->showCurrentTemp() > 80)
        {
            pAni->start();
            player->play();
        }
    });

    timer->start(1000);
}

MainWidget::~MainWidget()
{
}

void MainWidget::resizeEvent(QResizeEvent *event)
{
    // 背景优化
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap("/Users/wy/Desktop/TempatureDisplay/sky.jpg").scaled(this->size())));
    this->setPalette(palette);

    maskWidget->setGeometry(0,0,this->width(),this->height());
}

