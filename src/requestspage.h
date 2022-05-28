#ifndef REQUESTSPAGE_H
#define REQUESTSPAGE_H

#include <QSplitter>
#include <QVBoxLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QStackedWidget>
#include <QButtonGroup>
#include <QSysInfo>
#include <QList>
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>

#include "buttons.h"
#include "widgets.h"
#include "input.h"
#include "labels.h"
#include "network.h"
#include <QDebug>

class HistoryWidget: public QWidget
{
    Q_OBJECT
public:
    HistoryWidget(QWidget* parent);
    void initUi();
    void setBackground(const QColor c = QColor(255, 255, 255));
private:
    QVBoxLayout *layout;
    FilterInput *searchInput;
    TextButton *deselectButton;
    TextButton *removeButton;
    TextButton *removeAllButton;
    UnFilledPrimaryButton *saveButton;
};

class CollectionWidget: public QWidget
{
    Q_OBJECT
public:
    CollectionWidget(QWidget* parent);
    void initUi();
    void setBackground(const QColor c = QColor(255, 255, 255));
private:
    QVBoxLayout *layout;
    FilterInput *searchInput;
    TextButton *newButton;
    TextButton *removeAllButton;
};


// 侧边栏
class LeftSideBar: public QWidget
{
    Q_OBJECT
signals:
    void afterHide();
public:
    LeftSideBar(QWidget* parent=nullptr);
    void initUi();
    void initSignals();
    void resizeEvent(QResizeEvent*);
    void setBackground(QColor c = QColor(255, 255, 255));
private:
    BorderRadiusWidget* centralWidget;
    QVBoxLayout* centralWidgetLayout;

    QVBoxLayout* layout;
    LeftBarTabButton* historyBtn;
    LeftBarTabButton* collectionBtn;
    int buttonWidth;
    QButtonGroup* btnGroup;
    QStackedWidget* tabWidget;
    HistoryWidget* historyWidget;
    CollectionWidget* collectionWidget;
};

class RequestHeader: public QWidget
{
    Q_OBJECT
public:
    RequestHeader(QWidget* parent);
private:
    QVBoxLayout* layout;
    int headerTabHeight;
    QComboBox* comboBox;
    QStackedWidget* bottomContent;
    QTextEdit* editor;
private:
    QMultiMap<QString, QString> headers;
};

class RequestBody: public QWidget
{
    Q_OBJECT
public:
    RequestBody(QWidget* parent);
private:
    QVBoxLayout* layout;
    int headerTabHeight;
    QComboBox* comboBox;
    QStackedWidget* bottomContent;
    // 输入框
    QTextEdit* editor;
private:
    QByteArray body;
};

// 请求部分，包括header、body等
class RequestPart: public BorderRadiusWidget
{
    Q_OBJECT
signals:
    void receivedResponse(BaseHttpResponse*);
public:
    RequestPart(QWidget* parent=nullptr);
    void initUi();
    void initSignals();
    void send();
private:
    QVBoxLayout* layout;
    // http method selector
    QComboBox* methodSelector;
    // url input
    URLInput* urlInput;
    // A label to show url length
    QLabel* lengthLable;
    // send button
    SendButton* sendButton;
    // header
    RequestHeader* requestHeader;
    // body
    RequestBody* requestBody;
};


class ResponseHeader: public QWidget
{
    Q_OBJECT
public:
    ResponseHeader(QWidget* parent);
    void setContent(const QString&);
private:
    QVBoxLayout* layout;
    int headerTabHeight;
    QComboBox* comboBox;
    QStackedWidget* bottomContent;
    QTextEdit* editor;
};

class ResponseBody: public QWidget
{
    Q_OBJECT
public:
    ResponseBody(QWidget* parent);
    void setContent(const QString&);
private:
    QVBoxLayout* layout;
    int headerTabHeight;
    QComboBox* comboBox;
    QStackedWidget* bottomContent;
    // 输入框
    QTextEdit* editor;
};

// 返回部分，包括返回结果、状态码、耗时等
class ResponsePart: public BorderRadiusWidget
{
    Q_OBJECT
public:
    ResponsePart(QWidget* parent=nullptr);
    void initUi();
    void handleResponse(BaseHttpResponse*);
private:
    QLabel* titleLabel;
    QLabel* elapsedLabel;
    QLabel* infoLabel;
    QLabel* statusLabel;
    QSplitter* splitter;
    ResponseHeader* responseHeader;
    ResponseBody* responseBody;
};


class RequestsContentPage: public QWidget
{
    Q_OBJECT
signals:
    void rotated(QBoxLayout::Direction);
public:
    RequestsContentPage(QWidget* parent=nullptr);
    void initUi();
    void rotate();
    void initSignals();
private:
    QVBoxLayout* layout;
    RequestPart* requestPart;
    ResponsePart* responsePart;
};

// requests部分的基础部件
class RequestsPage: public QWidget
{
    Q_OBJECT
public:
    RequestsPage(QWidget* parent=nullptr);
    void initUi();
    void initSignals();
    void resizeEvent(QResizeEvent*);
private:
    QSplitter* _requestsPage;
    QHBoxLayout* layout;
    LeftSideBar* leftSideBar;
    PopUpButton* leftSideBtn;
    RequestsContentPage* requestContentPage;
};
#endif // REQUESTSPAGE_H
