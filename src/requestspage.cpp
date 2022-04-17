#include "requestspage.h"

HistoryWidget::HistoryWidget(QWidget* parent)
{
    initUi();
}

void HistoryWidget::initUi()
{
    setBackground();
}

void HistoryWidget::setBackground(const QColor c)
{
    QPalette p;
    p.setColor(QPalette::Window, c);
    setAutoFillBackground(true);
    setPalette(p);
}


CollectionWidget::CollectionWidget(QWidget* parent)
{
    initUi();
}

void CollectionWidget::initUi()
{
    setBackground();
}

void CollectionWidget::setBackground(const QColor c)
{
    QPalette p;
    p.setColor(QPalette::Window, c);
    setAutoFillBackground(true);
    setPalette(p);
}


LeftSideBar::LeftSideBar(QWidget* parent)
    :layout(new QVBoxLayout(this))
    , historyBtn(new TitleBarTabButton(this))
    , collectionBtn(new TitleBarTabButton(this))
    , buttonHeight(45)
    , btnGroup(new QButtonGroup(this))
    , tabWidget(new QStackedWidget(this))
    , historyWidget(new HistoryWidget(this))
    , collectionWidget(new CollectionWidget(this))
{
    initUi();
    initSignals();
}

void LeftSideBar::initUi()
{
    setBackground();

    // history button
    historyBtn->setText(tr("HISTORY"));
    historyBtn->setFixedHeight(buttonHeight);
    historyBtn->setChecked(true);
    historyBtn->setButtonType(TitleBarTabButton::LeftSideBarTop);

    // collection button
    collectionBtn->setText(tr("COLLECTION"));
    collectionBtn->setFixedHeight(buttonHeight);
    collectionBtn->setButtonType(TitleBarTabButton::LeftSideBarTop);

    // add buttons to button group
    btnGroup->addButton(historyBtn);
    btnGroup->addButton(collectionBtn);
    btnGroup->setExclusive(true);

    // add buttons to layout
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(historyBtn);
    topLayout->addWidget(collectionBtn);

    topLayout->setSpacing(0);
    topLayout->setContentsMargins(0, 0, 0, 0);
    layout->addLayout(topLayout);

//    tabWidget->setDocumentMode(true);
    tabWidget->insertWidget(0, historyWidget);
    tabWidget->insertWidget(1, collectionWidget);
    collectionWidget->setBackground(Qt::red);
    tabWidget->setCurrentIndex(0);
    layout->addWidget(tabWidget);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
}

void LeftSideBar::initSignals()
{
    connect(historyBtn, &TitleBarTabButton::clicked, this, [&]{tabWidget->setCurrentIndex(0);});
    connect(collectionBtn, &TitleBarTabButton::clicked, this, [&]{tabWidget->setCurrentIndex(1);});
}

void LeftSideBar::setBackground(QColor c)
{
    QPalette p;
    p.setColor(QPalette::Window, c);
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
        _requestsPage->setSizes({2000, 7000});
    });
}

void RequestsPage::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    leftSideBar->setMaximumWidth(width()/ 2);
}
