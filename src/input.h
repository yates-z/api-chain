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
protected:
    QString path;
    bool isFocus;
    int margin;
    int innerMargin;
    QString lineColor;
    QString focusColor;
};

class URLInput: public FilterInput
{
    Q_OBJECT
public:
    URLInput(QWidget *parent=nullptr);
    URLInput(QString text="", QWidget *parent=nullptr);
    void initSignals();
    void showIsSafe();
public Q_SLOTS:
    void setText(const QString &);
private:
    bool isSafe;
};

class PlainFilterInput:public FilterInput
{
    Q_OBJECT
public:
    PlainFilterInput(QWidget *parent=nullptr);

};
#endif // INPUT_H
