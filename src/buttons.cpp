#include "buttons.h"

TopMenuTabButton::TopMenuTabButton(QWidget* parent)
    : isEnter(false)
    , color("#263762")
    , hoverColor("#364460")
    , checkedColor("#1c2c4b")
{
    setCheckable(true);
}

void TopMenuTabButton::enterEvent(QEnterEvent *e)
{
    QPushButton::enterEvent(e);
    setCursor(Qt::PointingHandCursor);
    isEnter = true;
    repaint();
}

void TopMenuTabButton::leaveEvent(QEvent *e)
{
    QPushButton::leaveEvent(e);
    isEnter = false;
    repaint();
}

void TopMenuTabButton::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    QRectF rect(0, (height() - 20)/2 - 2, width(), 20);
    painter.fillRect(0, 0,width(), height(), QColor(color));
    if (this->isChecked())
        painter.fillRect(0, 0,width(), height(), QColor(checkedColor));
    if (isEnter)
        painter.fillRect(0, 0,width(), height(), QColor(hoverColor));
    if (this->isChecked())
    {
        QPen pen;
        pen.setColor(QColor("#6664ca"));
        pen.setWidth(4);

        painter.setPen(pen);
        painter.drawLine(0, height()-2, width(), height()-2);
    }

    QPen pen(Qt::white);
    painter.setPen(pen);
    painter.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, this->text());
}
