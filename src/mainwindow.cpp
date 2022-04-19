#include "mainwindow.h"

TitleBar::TitleBar(QWidget *parent)
    : layout(new QHBoxLayout(this))
    , logo(new QLabel(this))
    , title(new TitleLabel(this, tr("API Chain")))
    , btnGroup(new QButtonGroup(this))
    , apiPageButton(new TitleBarTabButton(this))
    , apiChainButton(new TitleBarTabButton(this))
    , settingsButton(new SvgButton(QSize(20, 20), ":/resource/svg/settings.svg", this))
    , fixedHeight(48)
{
    initUi();
}

void TitleBar::initUi()
{
    // 设置三个QHBoxLayout,让tab按钮居中
    QHBoxLayout *leftLayout = new QHBoxLayout;
    QHBoxLayout *middleLayout = new QHBoxLayout;
    QHBoxLayout * rightLayout = new QHBoxLayout;
    // 设置背景颜色
    QPalette p1;
    p1.setColor(QPalette::Window, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(p1);
    this->setFixedHeight(fixedHeight);

    #ifdef Q_OS_MAC
    // OSX留位置给系统按钮
    leftlayout->addSpacerItem(new QSpacerItem(60, 48));
    #endif
    // logo
    logo->setFixedSize(fixedHeight*0.6, fixedHeight*0.6);
    leftLayout->addWidget(logo);

    // 标题
    leftLayout->addWidget(title);
    leftLayout->addStretch(1);
    layout->addLayout(leftLayout, 1);

    // 分割线
    SplitLine* splitLine = new SplitLine(this, QColor(230, 230, 230));
    splitLine->setHeight(fixedHeight * 0.6);
    middleLayout->addWidget(splitLine);

    // tab
    apiPageButton->setText(tr("Requests"));
    apiPageButton->setFixedSize(160, fixedHeight);
    apiPageButton->setChecked(true);
    middleLayout->addWidget(apiPageButton);

    apiChainButton->setEnabled(false); // 禁用
    apiChainButton->setText(tr("Chain"));
    apiChainButton->setFixedSize(160, fixedHeight);
    middleLayout->addWidget(apiChainButton);

    // 分割线
    SplitLine* splitLine2 = new SplitLine(this, QColor(230, 230, 230));
    splitLine2->setHeight(fixedHeight * 0.6);
    middleLayout->addWidget(splitLine2);

    layout->addLayout(middleLayout, 1);

    // 右侧设置按钮
    rightLayout->addStretch(1);
    settingsButton->setFixedSize(36, 36);
    rightLayout->addWidget(settingsButton);
    layout->addLayout(rightLayout, 1);

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
    insertWidget(0, requestsPage);
    insertWidget(1, chainPage);
    setCurrentIndex(0);
}


#ifdef Q_OS_WIN
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mainWindow(new QWidget(this))
    , mainLayout(new QVBoxLayout(mainWindow))
    , titleBar(new TitleBar(mainWindow))
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
    mainLayout->addWidget(titleBar);
    mainLayout->addWidget(content);
    mainLayout->setSpacing(0);
}


void MainWindow::initSignals()
{
    connect(titleBar->apiPageButton, &TitleBarTabButton::clicked, this, [&]{content->setCurrentIndex(0);});
    connect(titleBar->apiChainButton, &TitleBarTabButton::clicked, this, [&]{content->setCurrentIndex(1);});
}


MainWindow::~MainWindow()
{
}

#endif
