#ifndef REQUESTSPAGE_H
#define REQUESTSPAGE_H

#include <QSplitter>
#include <QVBoxLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QStackedWidget>
#include <QButtonGroup>
#include <QSysInfo>

#include "buttons.h"
#include "widgets.h"
#include "input.h"
#include <QDebug>

class HistoryWidget: public QWidget
{
    Q_OBJECT
public:
    HistoryWidget(QWidget* parent);
    void initUi();
    void setBackground(const QColor c = QColor(255, 255, 255));
private:
    QVBoxLayout *layout;
    FilterInput *searchInput;
    TextButton *deselectButton;
    TextButton *removeButton;
    TextButton *removeAllButton;
    UnFilledPrimaryButton *saveButton;
};

class CollectionWidget: public QWidget
{
    Q_OBJECT
public:
    CollectionWidget(QWidget* parent);
    void initUi();
    void setBackground(const QColor c = QColor(255, 255, 255));

};

class RealLeftSideBar: public BorderRadiusWidget
{
    Q_OBJECT
public:
    RealLeftSideBar(QWidget* parent=nullptr);
    void paintEvent(QPaintEvent*);
    void setLinex(int);
    void setColor(QColor);
private:
    int x;
    QColor color;
};


class LeftSideBar: public QWidget
{
    Q_OBJECT
signals:
    void afterHide();
public:
    LeftSideBar(QWidget* parent=nullptr);
    void initUi();
    void initSignals();
    void resizeEvent(QResizeEvent*);
    void setBackground(QColor c = QColor(255, 255, 255));
private:
    RealLeftSideBar* centralWidget;
    QHBoxLayout* centralWidgetLayout;

    QVBoxLayout* layout;
    LeftBarTabButton* historyBtn;
    LeftBarTabButton* collectionBtn;
    int buttonWidth;
    QButtonGroup* btnGroup;
    QStackedWidget* tabWidget;
    HistoryWidget* historyWidget;
    CollectionWidget* collectionWidget;
};


class RequestsContentPage: public QWidget
{
    Q_OBJECT
public:
    RequestsContentPage(QWidget* parent=nullptr);
};


class RequestsPage: public QWidget
{
    Q_OBJECT
public:
    RequestsPage(QWidget* parent=nullptr);
    void initUi();
    void initSignals();
    void resizeEvent(QResizeEvent*);
private:
    QSplitter* _requestsPage;
    QHBoxLayout* layout;
    LeftSideBar* leftSideBar;
    PopUpButton* leftSideBtn;
    RequestsContentPage* requestContentPage;
};
#endif // REQUESTSPAGE_H
