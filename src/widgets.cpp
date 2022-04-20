#include "widgets.h"

BorderRadiusWidget::BorderRadiusWidget(QWidget* parent)
    : QWidget(parent)
    , radius(8)
    , color(Qt::white)
{
    setObjectName("BorderRadiusWidget");
    initUi();
}

void BorderRadiusWidget::initUi()
{
    QString qss(QString("QWidget#BorderRadiusWidget{border-radius: %1px;background-color: %2;}").arg(
                    radius).arg(color.name()));
    setStyleSheet(qss);
}

void BorderRadiusWidget::setRadius(int r)
{
    radius = r;
    initUi();
}

void BorderRadiusWidget::setBackgoundColor(QColor c)
{
    color = c;
    initUi();
}


void BorderRadiusWidget::paintEvent(QPaintEvent *event)
{
    /* 直接继承自Qidget的类无法使用QSS*/
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}
