#include "requestspage.h"

HistoryWidget::HistoryWidget(QWidget* parent)
    : QWidget(parent)
    , layout (new QVBoxLayout(this))
    , searchInput(new FilterInput(this))
    , deselectButton(new TextButton(tr("Deselect"), this))
    , removeButton(new TextButton(tr("Remove"), this))
    , removeAllButton(new TextButton(tr("Remove all"), this))
    , saveButton(new UnFilledPrimaryButton(tr("Save to collections"), this))
{
    initUi();
}

void HistoryWidget::initUi()
{
    setBackground();
    searchInput->setMinimumHeight(28);
    layout->addWidget(searchInput);

    layout->addSpacing(10);
    QHBoxLayout *middleBtnLayout = new QHBoxLayout;
    middleBtnLayout->addWidget(deselectButton);
    middleBtnLayout->addWidget(removeButton);
    middleBtnLayout->addWidget(removeAllButton);
    middleBtnLayout->setContentsMargins(5, 0, 5, 0);
    layout->addLayout(middleBtnLayout);


    layout->addStretch(1);
    layout->addSpacing(3);
    layout->addWidget(saveButton);
    layout->addSpacing(3);

    layout->setContentsMargins(0, 0, 0, 0);
}

void HistoryWidget::setBackground(const QColor c)
{
    QPalette p;
    p.setColor(QPalette::Window, c);
    setAutoFillBackground(true);
    setPalette(p);
}


CollectionWidget::CollectionWidget(QWidget* parent)
    : QWidget(parent)
    , layout (new QVBoxLayout(this))
    , searchInput(new FilterInput(this))
    , newButton(new TextButton(tr("New"), this))
    , removeAllButton(new TextButton(tr("Remove all"), this))
{
    initUi();
}

void CollectionWidget::initUi()
{
    setBackground();
    searchInput->setMinimumHeight(28);
    layout->addWidget(searchInput);

    layout->addSpacing(10);
    QHBoxLayout *middleBtnLayout = new QHBoxLayout;
    middleBtnLayout->addWidget(newButton);
    middleBtnLayout->addWidget(removeAllButton);
    middleBtnLayout->setContentsMargins(5, 0, 5, 0);
    layout->addLayout(middleBtnLayout);

    layout->addStretch(1);

    layout->setContentsMargins(0, 0, 0, 0);
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
    , centralWidget(new RealLeftSideBar(this))
    , centralWidgetLayout(new QVBoxLayout(centralWidget))
    , historyBtn(new LeftBarTabButton(centralWidget))
    , collectionBtn(new LeftBarTabButton(centralWidget))
    , buttonWidth(45)
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
    centralWidget->setLinex(buttonWidth);
    layout->addWidget(centralWidget);
    layout->setContentsMargins(15, 30, 0, 30);

    // history button
    historyBtn->setText(tr("HISTORY"));
    historyBtn->setFixedHeight(buttonWidth);
    historyBtn->setButtonType(LeftBarTabButton::History);
    historyBtn->setChecked(true);

    // collection button
    collectionBtn->setText(tr("COLLECTION"));
    collectionBtn->setButtonType(LeftBarTabButton::Collection);
    collectionBtn->setFixedHeight(buttonWidth);

    // add buttons to button group
    btnGroup->addButton(historyBtn);
    btnGroup->addButton(collectionBtn);
    btnGroup->setExclusive(true);

    // add buttons to layout
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addSpacing(8);
    topLayout->addWidget(historyBtn);
    topLayout->addWidget(collectionBtn);
    topLayout->addSpacing(8);

    topLayout->setSpacing(0);
    topLayout->setContentsMargins(0, 0, 0, 0);
    centralWidgetLayout->addLayout(topLayout);
    centralWidgetLayout->addSpacing(8);

    tabWidget->insertWidget(0, historyWidget);
    tabWidget->insertWidget(1, collectionWidget);
    tabWidget->setCurrentIndex(0);
    centralWidgetLayout->addWidget(tabWidget);
    centralWidgetLayout->setSpacing(0);
    centralWidgetLayout->setContentsMargins(0, 0, 0, 8);
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

RealLeftSideBar::RealLeftSideBar(QWidget* parent)
    : BorderRadiusWidget(parent)
    , color(QColor(145, 145, 145))
{}

void RealLeftSideBar::setLinex(int x)
{
    this->x = x;
    repaint();
}

void RealLeftSideBar::setColor(QColor color)
{
    this->color = color;
    repaint();
}

void RealLeftSideBar::paintEvent(QPaintEvent* event)
{
    BorderRadiusWidget::paintEvent(event);
    QPen pen;
    pen.setColor(color);
    QPainter painter(this);
    painter.setPen(pen);
//    painter.drawLine(0, x, width(), x);
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
