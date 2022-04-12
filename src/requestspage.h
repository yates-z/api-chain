#ifndef REQUESTSPAGE_H
#define REQUESTSPAGE_H

#include <QSplitter>
#include <QVBoxLayout>
#include <QPushButton>
#include <QResizeEvent>
#include "buttons.h"
#include <QDebug>

class LeftSideBar: public QWidget
{
    Q_OBJECT
signals:
    void afterHide();
//    void afterShow();
public:
    LeftSideBar(QWidget* parent=nullptr);
    void initUi();
    void resizeEvent(QResizeEvent*);
private:
    QVBoxLayout* layout;
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
