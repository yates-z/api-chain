#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>

class TopMenuTabButton: public QPushButton
{
    Q_OBJECT
public:
    TopMenuTabButton(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent *);
    void enterEvent(QEnterEvent *);
    void leaveEvent(QEvent *);
    void setBottomColor(const QColor);
private:
    bool isEnter;
    QColor color;
    QColor hoverColor;
    QColor checkedColor;
    QColor bottomColor;
};

class PopUpButton: public QWidget
{
    Q_OBJECT
signals:
    void clicked();
public:
    PopUpButton(QWidget* parent = nullptr);
    void mouseReleaseEvent(QMouseEvent*);
    void enterEvent(QEnterEvent *);
    void leaveEvent(QEvent *);
    void paintEvent(QPaintEvent*);
private:
    bool isEnter;
};
#endif // BUTTONS_H
