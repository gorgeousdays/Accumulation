#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QLabel>

class DashBoard : public QWidget
{
    Q_OBJECT
public:
    explicit DashBoard(QWidget *parent = nullptr);

    void setValue(qreal value){
        m_DashValue = value;
        update();
    }
    void setBackGroundColor(QColor color){
        m_BgColor=color;
        update();
    }
    void setFrontColor(QColor color){
        m_FrontColor=color;
        update();
    }
    void setBorderColor(QColor color){
        m_BorderColor=color;
        update();
    }
    void setUnitString(QString str){
        m_StrUnit=str;
        update();
    }

    void setInfomation(QString displayInfoName, QString displayUnit)
    {
        m_displayInfoName = displayInfoName;
        displayInfoLabel->setText(m_displayInfoName);
        m_displayUnit = displayUnit;
        update();
    }
    void configsValues(qreal maxValue,qreal minValue,
                   qreal safevalue, qreal warningValue, qreal dangerValue)
    {
        m_MaxValue = maxValue;
        m_MinValue = minValue;
        m_safeValue = safevalue;
        m_warningValue = warningValue;
        m_dangerValue = dangerValue;
        update();
    }

    void drawBackGround(QPainter *painter, qreal hlafWidth);
    void drawScaleDials(QPainter *painter, qreal hlafWidth);
    void drawIndicator(QPainter *painter, qreal hlafWidth);
signals:

public slots:
protected:
    virtual void paintEvent(QPaintEvent * event);

private:
    int m_StartAngle;
    int m_EndAngle;

    qreal m_LineLength;
    qreal m_DashValue;
    qreal m_DashNum;

    qreal m_MaxValue;
    qreal m_MinValue;
    qreal m_safeValue;
    qreal m_warningValue;
    qreal m_dangerValue;

    QColor m_BgColor;
    QColor m_FrontColor;
    QColor m_BorderColor;
    QString m_StrUnit;

    qreal m_MaxBorderRadius;
    qreal m_MinBorderRadius;
    qreal m_DialsRadius;

    QString m_displayInfoName;
    QString m_displayUnit;

    QLabel *displayInfoLabel;
    QLabel *displayUnitLabel;
};

#endif // DASHBOARD_H
