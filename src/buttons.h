#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>

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
#endif // BUTTONS_H
