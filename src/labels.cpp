#include "labels.h"

SplitLine::SplitLine(QWidget* parent, const QColor color)
{
    this->setFixedWidth(1);
    QPalette p;
    p.setColor(QPalette::Window, color);
    this->setAutoFillBackground(true);
    this->setPalette(p);
//    this->setStyleSheet("background-color: white");
}

void SplitLine::setHeight(int h)
{
    this->setFixedHeight(h);
}
