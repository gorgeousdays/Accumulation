#ifndef THERMOMTER_H
#define THERMOMTER_H

#include <QObject>

class Thermomter : public QObject
{
    Q_OBJECT
//    公有性封装 类外可以访问
public:
//    构造函数 创建对应的对象的方法
    explicit Thermomter(QObject *parent = nullptr, qreal minTemp = 0, qreal maxTemp = 100);

//    测量温度
    void measureTemp();

//    展示温度
    qreal showCurrentTemp();

    qreal showMinTemp();
    qreal showMaxTemp();

//    私有性封装 类外不能访问
private:
    qreal m_current_temp;
    qreal m_min_temp;
    qreal m_max_temp;

signals:

};

//电子体温计 -> 需要供电，开机
// 选择模式：体温模式，常温模式

// 继承，继承就是保留上层更加抽象的类的基本功能 无需重复再写
// 默认的继承方式，会让派生类无法访问基类的成员
class EThermometer :public Thermomter
{
    Q_OBJECT
public:
    void startUp();

    // 选择模式
//    void chooseMode(int mode);
private slots:
    void makeTemp();
};

#endif // THERMOMTER_H
