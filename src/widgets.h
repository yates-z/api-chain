#ifndef WIDGETS_H
#define WIDGETS_H
#include <QWidget>
#include <QStyleOption>
#include <QPainter>

class BorderRadiusWidget: public QWidget
{
    Q_OBJECT
public:
    BorderRadiusWidget(QWidget* parent=nullptr);
    void initUi();
    void setRadius(int);
    void setBackgoundColor(QColor);
    void paintEvent(QPaintEvent*);
private:
    int radius;
    QColor color;
};
#endif // WIDGETS_H
