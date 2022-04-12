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

void LeftSideBar::resizeEvent(QResizeEvent* e)
{

    QWidget::resizeEvent(e);
    if (width() == 0)
        emit afterHide();
}



RequestsContentPage::RequestsContentPage(QWidget* parent)
{}


RequestsPage::RequestsPage(QWidget* parent)
    : _requestsPage(new QSplitter(this))
    , layout(new QHBoxLayout(this))
    , leftSideBar(new LeftSideBar(this))
    , leftSideBtn(new PopUpButton(this))
    , requestContentPage(new RequestsContentPage(this))
{
    initUi();
    initSignals();
}

void RequestsPage::initUi()
{
    leftSideBtn->hide();
    leftSideBtn->setFixedWidth(12);
    layout->addWidget(leftSideBtn);

    _requestsPage->insertWidget(0, leftSideBar);
    _requestsPage->insertWidget(1, requestContentPage);
    // 会自己剪裁
    _requestsPage->setSizes({1000, 4000});
    layout->addWidget(_requestsPage);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
}

void RequestsPage::initSignals()
{
    connect(leftSideBar, &LeftSideBar::afterHide, this, [&]{
        leftSideBar->hide();
        leftSideBtn->show();
    });
    connect(leftSideBtn, &PopUpButton::clicked, this, [&]{
        leftSideBtn->hide();
        leftSideBar->show();
        _requestsPage->setSizes({1000, 4000});
    });
}

void RequestsPage::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    leftSideBar->setMaximumWidth(width()/ 2);
}
