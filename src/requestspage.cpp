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
    addWidget(leftSideBar);
    setStretchFactor(0, 1);
    addWidget(requestContentPage);
    setStretchFactor(1, 4);
}

void RequestsPage::resizeEvent(QResizeEvent *e)
{
    QSplitter::resizeEvent(e);
    leftSideBar->setMaximumWidth(width()/ 2);
}
