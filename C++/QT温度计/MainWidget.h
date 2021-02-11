#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QChartView>
#include <QChart>
// 点状图
#include <QtCharts/QScatterSeries>
// 折线图
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    void resizeEvent(QResizeEvent *event) override;
private:
    QWidget *maskWidget;

};
#endif // MAINWIDGET_H
