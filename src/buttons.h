#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>
#include <QSvgRenderer>
#include <QFile>
#include <QDomDocument>
#include "constants.h"

class TitleBarTabButton: public QPushButton
{
    Q_OBJECT
public:
    TitleBarTabButton(QWidget* parent = nullptr);
    enum ButtonType{
        AppTop,
        LeftSideBarTop,
    };
    void initUi();
    void paintEvent(QPaintEvent *);
    void enterEvent(QEnterEvent *);
    void leaveEvent(QEvent *);
    void setButtonType(const ButtonType);
private:
    ButtonType btnType;
    bool isEnter;
    QColor color;
    QColor background;
    QColor hoverBackground;
    QColor checkedBackground;
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

class SvgButton: public QPushButton
{
    Q_OBJECT
public:
    SvgButton(const QSize&, const QString&, QWidget* parent=nullptr);
protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEnterEvent *);
    void leaveEvent(QEvent *);
    void SetSVGColor(QDomElement elem, QString color);
private:
    QSize size;
    QString path;
    QColor color;
    QColor hoverColor;
    bool isEnter;
    QDomDocument doc;
};
#endif // BUTTONS_H
