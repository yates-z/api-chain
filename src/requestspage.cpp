#include "requestspage.h"

LeftSideBar::LeftSideBar(QWidget* parent)
    :layout(new QVBoxLayout(this))
{
    initUi();
}

void LeftSideBar::initUi()
{
    QPalette p;
    p.setColor(QPalette::Window, QColor("#1a1a1a"));
    setAutoFillBackground(true);
    setPalette(p);
}


RequestsContentPage::RequestsContentPage(QWidget* parent)
{}


RequestsPage::RequestsPage(QWidget* parent)
    : leftSideBar(new LeftSideBar(this))
    , requestContentPage(new RequestsContentPage(this))
{
    initUi();
}

void RequestsPage::initUi()
{
    insertWidget(0, leftSideBar);
    insertWidget(1, requestContentPage);
    // 会自己剪裁
    setSizes({1000, 4000});
}

void RequestsPage::resizeEvent(QResizeEvent *e)
{
    QSplitter::resizeEvent(e);
    leftSideBar->setMaximumWidth(width()/ 2);
}
