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
    , centralWidget(new BorderRadiusWidget(this))
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


RequestHeader::RequestHeader(QWidget* parent)
    : QWidget(parent)
    , layout(new QVBoxLayout(this))
    , headerTabHeight(10)
    , comboBox(new QComboBox(this))
    , bottomContent(new QStackedWidget(this))
    , editor(new QTextEdit(this))
{
    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->addWidget(new QLabel("HEADERS"), Qt::AlignLeft);
    topLayout->addStretch(1);
    comboBox->addItems({"Form", "Raw"});
    topLayout->addWidget(comboBox, Qt::AlignRight);

    layout->addLayout(topLayout);
    SplitLine *splitline = new SplitLine(1, width());
    splitline->setOrientation(Qt::Horizontal);
    layout->addWidget(splitline);

    layout->addSpacing(10);

    bottomContent->addWidget(editor);
    layout->addWidget(bottomContent);

    layout->setContentsMargins(0, 0, 30, 15);
    layout->setSpacing(0);
}


RequestBody::RequestBody(QWidget* parent)
    : QWidget(parent)
    , layout(new QVBoxLayout(this))
    , headerTabHeight(10)
    , comboBox(new QComboBox(this))
    , bottomContent(new QStackedWidget(this))
    , editor(new QTextEdit(this))
{
    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->addWidget(new QLabel("BODY"), Qt::AlignLeft);
    topLayout->addStretch(1);
    comboBox->addItems({"Text", "Form", "File"});
    topLayout->addWidget(comboBox, Qt::AlignRight);

    layout->addLayout(topLayout);
    SplitLine *splitline = new SplitLine(1, width());
    splitline->setOrientation(Qt::Horizontal);
    layout->addWidget(splitline);

    layout->addSpacing(10);

    bottomContent->addWidget(editor);
    layout->addWidget(bottomContent);

    layout->setContentsMargins(30, 0, 0, 15);
    layout->setSpacing(0);
}


RequestPart::RequestPart(QWidget* parent)
    : BorderRadiusWidget(parent)
    , layout(new QVBoxLayout(this))
    , methodSelector(new BasicComboBox(this))
    , urlInput(new URLInput("https://", this))
    , lengthLable(new QLabel(QString("length: %1 byte(s)").arg(urlInput->text().toLocal8Bit().length())))
    , sendButton(new SendButton(this))
    , requestHeader(new RequestHeader(this))
    , requestBody(new RequestBody(this))
{
    initUi();
    initSignals();
}

void RequestPart::initUi()
{
    QGridLayout *topLayout = new QGridLayout;

    QLabel *label1 = new QLabel("METHOD");
    QFont font = label1->font();
    font.setPointSize(11);
    label1->setFont(font);
    QPalette p = label1->palette();
    p.setColor(QPalette::WindowText, ColorStyle::currentTooltipColor);
    label1->setPalette(p);
    topLayout->addWidget(label1, 0, 0);

    QLabel *label2 = new QLabel("SCHEME :// HOST [ \":\" PORT ] [ PATH [ \"?\" QUERY ]]");
    label2->setFont(font);
    label2->setPalette(p);
    topLayout->addWidget(label2, 0, 1);

    methodSelector->addItems({"GET", "POST", "PATCH", "PUT", "DELETE", "HEAD", "OPTIONS"});
    methodSelector->setFixedHeight(28);
    topLayout->addWidget(methodSelector, 1, 0);

    urlInput->setFixedHeight(28);
    topLayout->addWidget(urlInput, 1, 1);

    sendButton->setFixedHeight(28);
    topLayout->addWidget(sendButton, 1, 2);

    lengthLable->setFont(font);
    lengthLable->setPalette(p);
    topLayout->addWidget(lengthLable, 2, 1, Qt::AlignRight);


    topLayout->setSpacing(0);
    layout->addLayout(topLayout);

    QSplitter* splitter = new QSplitter(this);
    splitter->setHandleWidth(1);
    splitter->addWidget(requestHeader);
    splitter->addWidget(requestBody);

    layout->addWidget(splitter);
    layout->setContentsMargins(20, 35, 20, 20);
}


void RequestPart::initSignals()
{
    connect(sendButton, &SendButton::sendBtnClicked, this, &RequestPart::send);
    connect(urlInput, &QLineEdit::textChanged, this, [&]{
        lengthLable->setText(QString("length: %1 byte(s)").arg(urlInput->text().toLocal8Bit().length()));
    });
}

void RequestPart::send()
{
    BaseHttpRequest* request = request_producer(BaseHttpRequest::QNetWork);
    BaseHttpResponse* response = request->get(urlInput->text());
    emit receivedResponse(response);
}

ResponseHeader::ResponseHeader(QWidget* parent)
    :QWidget(parent)
    , layout(new QVBoxLayout(this))
    , headerTabHeight(10)
    , comboBox(new QComboBox(this))
    , bottomContent(new QStackedWidget(this))
    , editor(new QTextEdit(this))
{
    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->addWidget(new QLabel("HEADERS"), Qt::AlignLeft);
    topLayout->addStretch(1);
    comboBox->addItems({"pretty", "raw"});
    topLayout->addWidget(comboBox, Qt::AlignRight);

    layout->addLayout(topLayout);
    SplitLine *splitline = new SplitLine(1, width());
    splitline->setOrientation(Qt::Horizontal);
    layout->addWidget(splitline);

    layout->addSpacing(10);

    bottomContent->addWidget(editor);
    layout->addWidget(bottomContent);

    layout->setContentsMargins(0, 0, 30, 15);
    layout->setSpacing(0);
}

void ResponseHeader::setContent(const QString &content)
{
    editor->setPlainText(content);
}


ResponseBody::ResponseBody(QWidget* parent)
    :QWidget(parent)
    , layout(new QVBoxLayout(this))
    , headerTabHeight(10)
    , comboBox(new QComboBox(this))
    , bottomContent(new QStackedWidget(this))
    , editor(new QTextEdit(this))
{
    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->addWidget(new QLabel("BODY"), Qt::AlignLeft);
    topLayout->addStretch(1);
    comboBox->addItems({"pretty", "raw", "preview"});
    topLayout->addWidget(comboBox, Qt::AlignRight);

    layout->addLayout(topLayout);
    SplitLine *splitline = new SplitLine(1, width());
    splitline->setOrientation(Qt::Horizontal);
    layout->addWidget(splitline);

    layout->addSpacing(10);

    bottomContent->addWidget(editor);
    layout->addWidget(bottomContent);

    layout->setContentsMargins(30, 0, 0, 15);
    layout->setSpacing(0);
}

void ResponseBody::setContent(const QString &content)
{
    editor->setPlainText(content);
}


ResponsePart::ResponsePart(QWidget* parent)
    : BorderRadiusWidget(parent)
    , titleLabel(new QLabel(tr("Response")))
    , elapsedLabel(new QLabel(tr("Elapsed Time: 0ms")))
    , statusLabel(new QLabel(""))
    , infoLabel(new QLabel(tr("Not available, a request has not been sent yet.")))
    , splitter(new QSplitter(this))
    , responseHeader(new ResponseHeader(this))
    , responseBody(new ResponseBody(this))
{
    initUi();
}

void ResponsePart::initUi()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QHBoxLayout *topLayout = new QHBoxLayout();
    QFont font = titleLabel->font();
    font.setWeight(QFont::DemiBold);
    font.setPointSize(18);
    titleLabel->setFont(font);

    QPalette palette = titleLabel->palette();
    palette.setColor(QPalette::WindowText, ColorStyle::currentFontColor);
    titleLabel->setPalette(palette);
    topLayout->addWidget(titleLabel);
    topLayout->addStretch(1);

    statusLabel->hide();
    QFont statusLabelFont = statusLabel->font();
    statusLabelFont.setPointSize(11);
    statusLabel->setFont(statusLabelFont);
    topLayout->addWidget(statusLabel);


    elapsedLabel->hide();
    QFont elapsedLabelFont = elapsedLabel->font();
    elapsedLabelFont.setPointSize(11);
    elapsedLabel->setFont(elapsedLabelFont);
    QPalette palette2 = elapsedLabel->palette();
    palette2.setColor(QPalette::WindowText, ColorStyle::currentLineColor);
    elapsedLabel->setPalette(palette2);

    topLayout->addWidget(elapsedLabel);
    topLayout->setContentsMargins(0, 0, 10, 0);

    layout->addLayout(topLayout);

    infoLabel->setPalette(palette);
    layout->addWidget(infoLabel);
    layout->addStretch(1);

    splitter->setHandleWidth(1);
    splitter->addWidget(responseHeader);
    splitter->addWidget(responseBody);
    layout->addWidget(splitter);
    splitter->hide();
    layout->setContentsMargins(20, 20, 20, 20);
}

void ResponsePart::handleResponse(BaseHttpResponse *response)
{
    infoLabel->hide();

    statusLabel->show();
    int statusCode = response->statusCode();
    statusLabel->setText(QString(tr("Status Code")) + QString(": %1").arg(statusCode) + QString(" %2").arg(response->reason()));
    QPalette palette = statusLabel->palette();
    if (statusCode>=200 && statusCode < 300)
        palette.setColor(QPalette::WindowText, ColorStyle::currentSuccessColor);
    else if (statusCode>=400)
        palette.setColor(QPalette::WindowText, ColorStyle::currentFailedColor);
    else
        palette.setColor(QPalette::WindowText, ColorStyle::currentWarningColor);
    statusLabel->setPalette(palette);

    elapsedLabel->show();
    elapsedLabel->setText(QString(tr("Elapsed Time")) + QString(": %1ms").arg(response->elapsed));

    responseBody->setContent(response->text());
    responseHeader->setContent(response->getHeaderString());
    splitter->show();
}


RequestsContentPage::RequestsContentPage(QWidget* parent)
    : QWidget(parent)
    , layout(new QVBoxLayout(this))
    , requestPart(new RequestPart(this))
    , responsePart(new ResponsePart(this))
{
    initUi();
    initSignals();
}

void RequestsContentPage::initUi()
{
    layout->addWidget(requestPart);
    layout->addSpacing(10);
    layout->addWidget(responsePart);
    layout->setContentsMargins(15, 30, 15, 30);
}

void RequestsContentPage::initSignals()
{
    connect(requestPart, &RequestPart::receivedResponse, this, [&](BaseHttpResponse* response){responsePart->handleResponse(response);});
}

void RequestsContentPage::rotate()
{
    QList<QBoxLayout::Direction> directList{
        QBoxLayout::Direction::TopToBottom,
        QBoxLayout::Direction::LeftToRight,
        QBoxLayout::Direction::BottomToTop,
        QBoxLayout::Direction::RightToLeft,
        QBoxLayout::Direction::TopToBottom,
    };
    try {
        for (int index = 0; index < directList.count(); index++)
        {
            if (layout->direction() == directList[index])
            {
                layout->setDirection(directList[index + 1]);
                emit rotated(directList[index + 1]);
                break;
            }

        }
    }  catch (...) {
        layout->setDirection(QBoxLayout::Direction::TopToBottom);
        emit rotated(QBoxLayout::Direction::TopToBottom);
    }
}

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

    _requestsPage->setHandleWidth(0);
    _requestsPage->setObjectName("_requestsPage");
    _requestsPage->setStyleSheet("QSplitter#_requestsPage::handle { background-color: #ececec; }");
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
