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
    : QWidget(parent)
    , layout(new QVBoxLayout(this))
    , centralWidget(new BorderRadiusWidget)
    , centralWidgetLayout(new QHBoxLayout(centralWidget))
    , historyBtn(new LeftBarTabButton(centralWidget))
    , collectionBtn(new LeftBarTabButton(centralWidget))
    , buttonWidth(55)
    , btnGroup(new QButtonGroup(centralWidget))
    , tabWidget(new QStackedWidget(centralWidget))
    , historyWidget(new HistoryWidget(centralWidget))
    , collectionWidget(new CollectionWidget(centralWidget))
{
    initUi();
    initSignals();
}

void LeftSideBar::initUi()
{
    layout->addWidget(centralWidget);
    layout->setContentsMargins(15, 30, 0, 30);

    // history button
    historyBtn->setText(tr("HISTORY"));
    historyBtn->setFixedSize(buttonWidth, buttonWidth);
    historyBtn->setButtonType(LeftBarTabButton::History);
    historyBtn->setChecked(true);

    // collection button
    collectionBtn->setText(tr("COLLECTION"));
    collectionBtn->setButtonType(LeftBarTabButton::Collection);
    collectionBtn->setFixedSize(buttonWidth, buttonWidth);

    // add buttons to button group
    btnGroup->addButton(historyBtn);
    btnGroup->addButton(collectionBtn);
    btnGroup->setExclusive(true);

    // add buttons to layout
    QVBoxLayout *topLayout = new QVBoxLayout();
    topLayout->addStretch(1);
    topLayout->addWidget(historyBtn);
    topLayout->addWidget(collectionBtn);
    topLayout->addStretch(1);

    topLayout->setSpacing(0);
    topLayout->setContentsMargins(0, 0, 0, 0);
    centralWidgetLayout->addLayout(topLayout);

    tabWidget->insertWidget(0, historyWidget);
    tabWidget->insertWidget(1, collectionWidget);
    collectionWidget->setBackground(Qt::red);
    tabWidget->setCurrentIndex(0);
    centralWidgetLayout->addWidget(tabWidget);
    centralWidgetLayout->setSpacing(0);
    centralWidgetLayout->setContentsMargins(0, 8, 0, 8);
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
    : QWidget(parent)
{}


RequestsPage::RequestsPage(QWidget* parent)
    : QWidget(parent)
    , _requestsPage(new QSplitter(this))
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
    _requestsPage->setSizes({1000, 3000});
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
