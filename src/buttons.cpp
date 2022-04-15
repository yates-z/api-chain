#include "buttons.h"

TopMenuTabButton::TopMenuTabButton(QWidget* parent)
    : btnType(AppTop)
    , isEnter(false)
    , color(QColor(255, 255, 255))
    , background(QColor(38, 55, 98))
    , hoverBackground(QColor(54, 68, 96))
    , checkedBackground(QColor(28, 44, 75))
    , hoverColor(QColor(255, 255, 255))
    , checkedColor(QColor(255, 255, 255))
    , bottomColor(QColor(102, 100, 202))
{
    setCheckable(true);
    initUi();
}

void TopMenuTabButton::initUi()
{
    if (btnType == AppTop)
    {
        color = QColor(255, 255, 255);
        background = QColor(38, 55, 98);
        hoverBackground = QColor(54, 68, 96);
        checkedBackground = QColor(28, 44, 75);
        hoverColor = QColor(255, 255, 255);
        checkedColor = QColor(255, 255, 255);
        bottomColor = QColor(102, 100, 202);
    }
    else if (btnType == LeftSideBarTop)
    {
        color = QColor(138, 138, 138);
        background = QColor(26, 26, 26);
        hoverBackground = QColor(26, 26, 26);
        checkedBackground = QColor(26, 26, 26);
        hoverColor = QColor(189, 189, 189);
        checkedColor = QColor(247, 248, 249);
        bottomColor = QColor(247, 248, 249);
    }
}

void TopMenuTabButton::setButtonType(const ButtonType t)
{
    btnType = t;
    initUi();
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
    // 先处理背景色
    painter.fillRect(0, 0,width(), height(), background);
    if (this->isChecked())
        painter.fillRect(0, 0,width(), height(), checkedBackground);
    if (isEnter)
        painter.fillRect(0, 0,width(), height(), hoverBackground);
    // 再处理底部划线
    if (this->isChecked())
    {
        QPen pen;
        pen.setColor(bottomColor);
        if (btnType == AppTop)
            pen.setWidth(4);
        else
            pen.setWidth(3);

        painter.setPen(pen);
        painter.drawLine(0, height()-2, width(), height()-2);
    }
    else if (btnType == LeftSideBarTop)
    {
        QPen pen;
        pen.setColor(color);
        painter.setPen(pen);
        painter.drawLine(0, height()-2, width(), height()-2);
    }
    // 最后处理文字
    QPen pen;
    if (this->isChecked())
        pen.setColor(checkedColor);
    else if (isEnter)
        pen.setColor(hoverColor);
    else
        pen.setColor(color);
    painter.setPen(pen);
    QRectF rect(0, (height() - 20)/2 - 2, width(), 20);
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
