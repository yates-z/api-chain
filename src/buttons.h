#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>
#include <QPen>
#include <QPainter>

class TopMenuTabButton: public QPushButton
{
    Q_OBJECT
public:
    TopMenuTabButton(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent *);
    void enterEvent(QEnterEvent *);
    void leaveEvent(QEvent *);
private:
    bool isEnter;
    QString color;
    QString hoverColor;
    QString checkedColor;
};
#endif // BUTTONS_H
