#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QStackedWidget>
#include <QSpacerItem>
#include "labels.h"
#include "buttons.h"
#include "requestspage.h"
#include "chainpage.h"

class TitleBar: public QWidget
{
    Q_OBJECT
signals:
    void moved(QPoint);
public:
    TitleBar(QWidget* parent = nullptr);
    void initUi();
private:
    QHBoxLayout* layout;
    QLabel* logo;
    TitleLabel* title;
    QButtonGroup* btnGroup;
public:
    TitleBarTabButton* apiPageButton;
    TitleBarTabButton* apiChainButton;
    SvgButton* settingsButton;
private:
    const int fixedHeight;
};


/*
 * 这里选择QStackedWidget而不是QTabwidget，是因为QTabwidget会导致原生titlebar的透明属性失效
 * 原因未知，子类中有QTabwidget也不可以。
 */
class BaseContent: public QStackedWidget
{
    Q_OBJECT
public:
    BaseContent(QWidget* parent = nullptr);
    void initUi();
private:
    RequestsPage* requestsPage;
    ChainPage* chainPage;
};

#ifdef Q_OS_WIN
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initUi();
    void initSignals();
public:
    QWidget* mainWindow;
    QVBoxLayout* mainLayout;
    TitleBar* titleBar;
    BaseContent* content;
};

#elif defined Q_OS_MAC
class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void initUi();
    void initSignals();

    // 隐藏原生的titlebar，OS X10.10及以后才支持保留红绿灯、窗口圆角以及大小调整。
    void hideTitleBar();

    // 重载zoom按钮，使其最大化而非全屏，类似chrome的效果
    void reloadZoomButton();

    /*
     红绿灯默认位于左上角，自定义titlebar后与新titlebar的高度不搭配，需要调整。
     红绿灯的位置受制于原生titlebar的高度，因此需要先调整titlebar的高度。
     常用的做法是继承NSWindow，重新定义标题栏的frame
     参考：https://github.com/duoluo/WFCustomTitleBar/tree/master/WFCustomTitleBar/WFCustomTitleBar
     然而测试过程中发现对ViewController操作也可以使titlebar变高，但是无法控制其高度，原因还需要进一步研究
    */
    void setTitleButtonPos();
public:
    QWidget* mainWindow;
    QVBoxLayout* mainLayout;
    TitleBar* titleBar;
    BaseContent* content;
protected:
    void showEvent(QShowEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    bool    m_bWinMoving;
    bool    m_bMousePressed;
    QPoint  m_MousePos;
    QPoint  m_WindowPos;
    bool m_bCloseBtnQuit;
    bool m_bNativeSystemBtn;
    bool m_bIsCloseBtnEnabled, m_bIsMinBtnEnabled, m_bIsZoomBtnEnabled;
};
#endif

#endif // MAINWINDOW_H
