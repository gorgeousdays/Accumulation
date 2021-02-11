#include "Thermomter.h"
#include <QTimer>

Thermomter::Thermomter(QObject *parent, qreal minTemp, qreal maxTemp) : QObject(parent),
    m_min_temp(minTemp),m_max_temp(maxTemp)
{

}

void Thermomter::measureTemp()
{
    // 测量温度其实就是给当前的温度赋值
    // 随机化的处理
    srand(clock());
    m_current_temp = rand() % (int)(m_max_temp - m_min_temp) + m_min_temp;
}

qreal Thermomter::showCurrentTemp()
{
    return m_current_temp;
}

qreal Thermomter::showMinTemp()
{
    return m_min_temp;
}

qreal Thermomter::showMaxTemp()
{
    return m_max_temp;
}

void EThermometer::startUp()
{

    // 一秒钟产生一次数据 测量一次
    QTimer *t1 = new QTimer();

    // 信号与槽 某个事件发生会产生一个信号 槽处理信号的函数
    // 连接信号与槽
    connect(t1, SIGNAL(timeout()), this, SLOT(makeTemp()));

    t1->start(1000);
}

void EThermometer::makeTemp()
{
    measureTemp();
}
