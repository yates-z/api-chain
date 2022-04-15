#include "mainwindow.h"

TopMenu::TopMenu(QWidget *parent)
    : layout(new QHBoxLayout(this))
    , logo(new QLabel(this))
    , title(new QLabel(this))
    , btnGroup(new QButtonGroup(this))
    , apiPageButton(new TopMenuTabButton(this))
    , apiChainButton(new TopMenuTabButton(this))
    , settingsButton(new QPushButton(this))
    , fixedHeight(48)
{
    initUi();
}

void TopMenu::initUi()
{
    QPalette p1;
    p1.setColor(QPalette::Window, QColor("#263762"));
    this->setAutoFillBackground(true);
    this->setPalette(p1);
    this->setFixedHeight(fixedHeight);

    // logo
    logo->setFixedSize(fixedHeight*0.6, fixedHeight*0.6);
    layout->addWidget(logo);

    // 标题
    title->setText(tr("API Chain"));
    QPalette p2;
    p2.setColor(QPalette::WindowText,Qt::white);
    title->setPalette(p2);
    title->setAlignment(Qt::AlignCenter);
    title->setFixedWidth(100);
    layout->addWidget(title);

    layout->addSpacing(15);

    // 分割线
    SplitLine* splitLine = new SplitLine(this);
    splitLine->setHeight(fixedHeight*0.3);
    layout->addWidget(splitLine);

    // tab
    apiPageButton->setText(tr("Requests"));
    apiPageButton->setFixedSize(160, fixedHeight);
    apiPageButton->setChecked(true);
    layout->addWidget(apiPageButton);

    apiChainButton->setEnabled(false); // 禁用
    apiChainButton->setText(tr("Chain"));
    apiChainButton->setFixedSize(160, fixedHeight);
    layout->addWidget(apiChainButton);

    // 分割线
    SplitLine* splitLine2 = new SplitLine(this);
    splitLine2->setHeight(fixedHeight*0.3);
    layout->addWidget(splitLine2);
    layout->addStretch(1);

    // 右侧设置按钮
    settingsButton->setText(tr("settings"));
    layout->addWidget(settingsButton);

    layout->setContentsMargins(10, 0, 10, 0);
    layout->setSpacing(1);

    btnGroup->addButton(apiPageButton);
    btnGroup->addButton(apiChainButton);
    btnGroup->setExclusive(true);
}


BaseContent::BaseContent(QWidget *parent)
    : requestsPage(new RequestsPage(this))
    , chainPage(new ChainPage(this))
{
    initUi();
}

void BaseContent::initUi()
{
    this->insertTab(0, requestsPage, "Requests");
    this->insertTab(1, chainPage, "Chain");
    setDocumentMode(true);
    setTabVisible(0, false);
    setTabVisible(1, false);
    setCurrentIndex(0);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mainWindow(new QWidget(this))
    , mainLayout(new QVBoxLayout(mainWindow))
    , topMenu(new TopMenu(mainWindow))
    , content(new BaseContent(mainWindow))
{
    setCentralWidget(mainWindow);
    initUi();
    initSignals();
}

void MainWindow::initUi()
{
    this->resize(1260, 720);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(topMenu);
    mainLayout->addWidget(content);
    mainLayout->setSpacing(0);
}


void MainWindow::initSignals()
{
    connect(topMenu->apiPageButton, &TopMenuTabButton::clicked, this, [&]{content->setCurrentIndex(0);});
    connect(topMenu->apiChainButton, &TopMenuTabButton::clicked, this, [&]{content->setCurrentIndex(1);});
}


MainWindow::~MainWindow()
{
}

