#ifndef INPUT_H
#define INPUT_H
#include <QLineEdit>
#include <QSvgRenderer>
#include <QPainter>
#include <QFile>
#include <QDomDocument>

#include "buttons.h"
#include "constants.h"


class FilterInput:public QLineEdit
{
    Q_OBJECT
public:
    FilterInput(QWidget *parent=nullptr);
private slots:
    void paintEvent(QPaintEvent *);
//    void enterEvent(QEvent *);
//    void leaveEvent(QEvent *);
    void focusInEvent(QFocusEvent *);
    void focusOutEvent(QFocusEvent *);
private:
    QString path;
    bool isFocus;
    int margin;
};

class PlainFilterInput:public FilterInput
{
    Q_OBJECT
public:
    PlainFilterInput(QWidget *parent=nullptr);

};
#endif // INPUT_H
