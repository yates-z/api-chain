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
#include <QHBoxLayout>
#include "labels.h"
#include "constants.h"

class BasicButton:public QPushButton
{
    Q_OBJECT
public:
    BasicButton(QWidget* parent = nullptr);
    void enterEvent(QEnterEvent *);
    void leaveEvent(QEvent *);
protected:
    bool isEnter;
    QColor color;
    QColor background;
    QColor hoverBackground;
    QColor checkedBackground;
    QColor hoverColor;
    QColor checkedColor;
    QColor lineColor;
};

class SvgButton: public BasicButton
{
    Q_OBJECT
public:
    SvgButton(const QSize&, const QString&, QWidget* parent=nullptr);
    static void SetSVGColor(QDomElement elem, QString color);
    void initUi();
protected:
    void paintEvent(QPaintEvent *);
private:
    QSize size;
    QString path;
    QDomDocument doc;
};

class TitleBarTabButton: public BasicButton
{
    Q_OBJECT
public:
    TitleBarTabButton(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent *);
};

class LeftBarTabButton: public BasicButton
{
    Q_OBJECT
public:
    LeftBarTabButton(QWidget* parent = nullptr);
    enum ButtonType{
        History,
        Collection
    };
    void paintEvent(QPaintEvent *);
    void setButtonType(ButtonType);
private:
    QString svg_path;
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

class TextButton : public BasicButton
{
    Q_OBJECT
public:
    TextButton(QWidget *parent=nullptr);
    TextButton(QString s, QWidget *parent=nullptr);
    void setPlain();
};

class UnFilledPrimaryButton : public BasicButton
{
    Q_OBJECT
public:
    UnFilledPrimaryButton(QWidget *parent=nullptr);
    UnFilledPrimaryButton(QString s, QWidget *parent=nullptr);
    void initUi();
};

class RealSendButton : public BasicButton
{
    Q_OBJECT
public:
    RealSendButton(QWidget* parent=nullptr);
    RealSendButton(QString s, QWidget *parent=nullptr);
    void initUi();
    void setRightPart(bool);

    void paintEvent(QPaintEvent*);
private:
    QColor color;
    QColor hoverColor;
    int borderRadius;
    bool rightPart;
};

class SendButton: public QWidget
{
    Q_OBJECT
signals:
    void sendBtnClicked();
public:
    SendButton(QWidget* parent = nullptr);
    void initUi();
    void initSignals();
private:
    QHBoxLayout* layout;
    RealSendButton* sendBtn;
    RealSendButton* selector;
};

#endif // BUTTONS_H
