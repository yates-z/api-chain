#include "buttons.h"

TopMenuTabButton::TopMenuTabButton(QWidget* parent)
    : isEnter(false)
    , color(QColor(38, 55, 98))
    , hoverColor(QColor(54, 68, 96))
    , checkedColor(QColor(28, 44, 75))
    , bottomColor(QColor(102, 100, 202))
{
    setCheckable(true);
}

void TopMenuTabButton::setBottomColor(const QColor c)
{
    bottomColor = c;
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
    painter.fillRect(0, 0,width(), height(), color);
    if (this->isChecked())
        painter.fillRect(0, 0,width(), height(), checkedColor);
    if (isEnter)
        painter.fillRect(0, 0,width(), height(), hoverColor);
    if (this->isChecked())
    {
        QPen pen;
        pen.setColor(bottomColor);
        pen.setWidth(4);

        painter.setPen(pen);
        painter.drawLine(0, height()-2, width(), height()-2);
    }

    QPen pen(Qt::white);
    painter.setPen(pen);
    painter.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, this->text());
}


PopUpButton::PopUpButton(QWidget* parent)
{}


void PopUpButton::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
        emit clicked();
    QWidget::mousePressEvent(e);
}

void PopUpButton::enterEvent(QEnterEvent *e)
{
    QWidget::enterEvent(e);
    setCursor(Qt::PointingHandCursor);
    isEnter = true;
    repaint();
}

void PopUpButton::leaveEvent(QEvent *e)
{
    QWidget::leaveEvent(e);
    isEnter = false;
    repaint();
}

void PopUpButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (isEnter)
        painter.fillRect(0, 0,width(), height(), QColor(218,218,218));
    QRectF rect(0, (height() - 20)/2, width(), 20);
    painter.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, ">");
    QPen pen(QColor(170, 170, 170));
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawLine(width(), 0, width(), height());
}
