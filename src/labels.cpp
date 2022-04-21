#include "labels.h"

SplitLine::SplitLine(QWidget* parent, const QColor color)
    : QLabel(parent)
{
    this->setFixedWidth(2);
    QPalette p;
    p.setColor(QPalette::Window, color);
    this->setAutoFillBackground(true);
    this->setPalette(p);
}

void SplitLine::setHeight(int h)
{
    this->setFixedHeight(h);
}

TitleLabel::TitleLabel(QWidget *parent, const QString& text, const QColor color)
    : QLabel(parent)
{
    // 设置字体
    QFont font;
    font.setPointSize(14);
    font.setWeight(QFont::ExtraBold);
    font.setFamily("Bookman Old Style");
    setFont(font);

    // 设置文字颜色
    QPalette p;
    p.setColor(QPalette::WindowText, color);
    setPalette(p);

    // 居中对齐
    setAlignment(Qt::AlignCenter);

    setFixedWidth(100);

    setText(text);
}
