#ifndef REQUESTSPAGE_H
#define REQUESTSPAGE_H

#include <QSplitter>
#include <QVBoxLayout>

class LeftSideBar: public QWidget
{
    Q_OBJECT
public:
    LeftSideBar(QWidget* parent=nullptr);
    void initUi();
private:
    QVBoxLayout* layout;
};


class RequestsContentPage: public QWidget
{
    Q_OBJECT
public:
    RequestsContentPage(QWidget* parent=nullptr);
};


class RequestsPage: public QSplitter
{
    Q_OBJECT
public:
    RequestsPage(QWidget* parent=nullptr);
    void initUi();
    void resizeEvent(QResizeEvent*);
private:
    LeftSideBar *leftSideBar;
    RequestsContentPage* requestContentPage;
};
#endif // REQUESTSPAGE_H
