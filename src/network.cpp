#include "network.h"

BaseHttpResponse::BaseHttpResponse()
{}

QString BaseHttpResponse::getHeaderString()
{
    QString headers;
    foreach(QString s, this->headers.uniqueKeys())
    {
        foreach(QString v, this->headers.values(s))
            headers += s + ": " + v + "\n";
    }
    return headers;
}

BaseHttpRequest::BaseHttpRequest()
{}


QtHttpResponse::QtHttpResponse(QNetworkReply* reply)
    : BaseHttpResponse()
{
    _content_consumed = false;
    setReply(reply);
}

QtHttpResponse::~QtHttpResponse()
{
    delete reply;
}

std::ostream& operator << (std::ostream& os, const QtHttpResponse& p)
{
    os << QString("<Qt Network Response [%1]>").arg(p.status_code).toStdString();
    return os;
}

void QtHttpResponse::setReply(QNetworkReply *reply)
{
    this->reply = reply;
    if (this->reply)
    {
        this->status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
        this->reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
        this->url = reply->url().toString();
        QList<QByteArray> headerList = reply->rawHeaderList();
        foreach(QByteArray head, headerList) {
            headers.insert(QString::fromLocal8Bit(head), QString::fromLocal8Bit(reply->rawHeader(head)));
        }
    }
}


bool QtHttpResponse::ok()
{
    if (status_errors().isEmpty())
        return true;
    return false;
}

QString QtHttpResponse::status_errors()
{
    QString http_error_msg = "";
    if (400 <= status_code.toInt() && status_code.toInt() < 500)
        http_error_msg = QString("%1 Client Error: %2 for url: %3").arg(status_code, reason, url);
    else if (500 <= status_code.toInt() && status_code.toInt() < 600)
        http_error_msg = QString("%1 Server Error: %s for url: %s").arg(status_code, reason, url);
    return http_error_msg;
}

bool QtHttpResponse::is_redirect()
{

    return headers.uniqueKeys().contains("location") && QList<QString>{"301", "302", "303", "307", "308"}.contains(status_code);
}

bool QtHttpResponse::is_permanent_redirect()
{
    return headers.uniqueKeys().contains("location") && QList<QString>{"301", "308"}.contains(status_code);
}

QByteArray QtHttpResponse::content()
{
    if (_content.isEmpty())
    {
        if (_content_consumed)
            return _content;
        if (status_code.isEmpty())
            _content = "";
        else
            _content = reply->readAll();
    }
    _content_consumed = true;
    return _content;
}

QString QtHttpResponse::text()
{
    QString content = "";
    try {
        content = QString::fromLocal8Bit(this->content());
    }  catch (...) {}
    return content;
}

QJsonObject QtHttpResponse::json()
{
    QJsonDocument doc = QJsonDocument::fromJson(this->content());
    return doc.object();
}

QMultiMap<QString, QString> QtHttpResponse::links()
{
    return {};
}



QtHttpRequest::QtHttpRequest()
    : manager(new QNetworkAccessManager)
    , _request(new QNetworkRequest)
{}

QtHttpRequest::~QtHttpRequest()
{
    delete _request;
    delete manager;
}

std::ostream& operator<< (std::ostream& os, const QtHttpRequest& p)
{
    os << QString("<Qt Network Request: [%1]>").arg(p.method).toStdString();
    return os;
}

BaseHttpResponse* QtHttpRequest::get(
        QString url, QMap<QString, QString> params, QMultiMap<QString, QString> headers,
        QByteArray files, QByteArray data, QString auth,
        QMultiMap<QString, QString> cookies, QString json)
{
    QtHttpResponse *response = new QtHttpResponse();
    prepare(GET, url, headers, files, data, params, auth, cookies, json);
    QNetworkReply* reply = manager->get(*_request);
    QEventLoop eventloop;
    connect(reply, &QNetworkReply::finished, this, [&response, &eventloop, reply, this] {
        response->setReply(reply);
        eventloop.quit();
    });
    eventloop.exec(QEventLoop::DialogExec);
    return response;
}

void QtHttpRequest::post(QString url, QByteArray data, QString json, QByteArray files, QString auth, QMap<QString, QString> params, QMultiMap<QString, QString> cookies, QMultiMap<QString, QString> headers)
{}

void QtHttpRequest::patch(QString url, QByteArray data, QString json, QByteArray files, QString auth, QMap<QString, QString> params, QMultiMap<QString, QString> cookies, QMultiMap<QString, QString> headers)
{}

void QtHttpRequest::put(QString url, QByteArray data, QString json, QByteArray files, QString auth, QMap<QString, QString> params, QMultiMap<QString, QString> cookies, QMultiMap<QString, QString> headers)
{}

void QtHttpRequest::deleteResource(QString url, QByteArray data, QString json, QByteArray files, QString auth, QMap<QString, QString> params, QMultiMap<QString, QString> cookies, QMultiMap<QString, QString> headers)
{}

void QtHttpRequest::head(QString url, QMap<QString, QString> params, QMultiMap<QString, QString> headers, QByteArray files, QByteArray data, QString auth, QMultiMap<QString, QString> cookies, QString json)
{}

void QtHttpRequest::options(QString url, QMap<QString, QString> params, QMultiMap<QString, QString> headers, QByteArray files, QByteArray data, QString auth, QMultiMap<QString, QString> cookies, QString json)
{}

void QtHttpRequest::prepare(Method method, QString url, QMultiMap<QString, QString> headers, QByteArray files, QByteArray data, QMap<QString, QString> params, QString auth, QMultiMap<QString, QString> cookies, QString json)
{
    prepareMethod(method);
    prepareURL(url, params);
    prepareHeaders(headers);
    prepareCookies(cookies);
    prepareBody(data, files, json);
    prepareAuth(auth, url);
}

void QtHttpRequest::prepareMethod(Method method)
{
    this->method = method;
}


void QtHttpRequest::prepareURL(const QString _url, const QMap<QString, QString>& params)
{
    QUrl url(_url);
    QUrlQuery query;
    for (auto iter = params.cbegin(); iter != params.cend(); iter++)
        query.addQueryItem(iter.key(), QUrl::toPercentEncoding(iter.value()));
    url.scheme();
    url.setQuery(query);
    _request->setUrl(url);
    this->url = url;
}


void QtHttpRequest::prepareHeaders(const QMultiMap<QString, QString>& headers)
{
    for (auto iter = headers.cbegin(); iter != headers.cend(); iter++)
        _request->setRawHeader(iter.key().toUtf8(), iter.value().toUtf8());
    this->headers = headers;
}

void QtHttpRequest::prepareCookies(const QMultiMap<QString, QString>& cookies)
{
    QNetworkCookieJar *cookieJar = new QNetworkCookieJar;
    QList<QNetworkCookie> cookieList;
    for (auto iter = cookies.cbegin(); iter != cookies.cend(); iter++)
    {
        QNetworkCookie cookie(iter.key().toUtf8(), iter.value().toUtf8());
        cookieList.append(cookie);
    }
    cookieJar->setCookiesFromUrl(cookieList, url);
    manager->setCookieJar(cookieJar);
    this->cookieList = cookieList;
}

void QtHttpRequest::prepareBody(const QByteArray& data, const QByteArray& files, const QString& json)
{

}

void QtHttpRequest::prepareAuth(QString auth, QString url)
{

}


BaseHttpRequest* request_producer(BaseHttpRequest::Engine engine)
{
    if (engine == BaseHttpRequest::QNetWork)
        return new QtHttpRequest();
    else
        return new QtHttpRequest();
}


PreparedRequest::PreparedRequest()
{}

void PreparedRequest::prepare(
        QString method, QString url, QMap<QString, QString> headers, QByteArray files, QByteArray data,
        QMap<QString, QString> params, QString auth, QMap<QString, QString> cookies, QString json)
{
//    prepareMethod(method);
//    prepareURL(url, params);
//    prepareHeaders(headers);
//    prepareCookies(cookies);
//    prepareBody(data, files, json);
//    prepareAuth(auth, url);
}

PreparedRequest* PreparedRequest::copy()
{
    PreparedRequest* p = new PreparedRequest();
    p->method = method;
    p->url = url;
//    p->headers = self.headers.copy() if self.headers is not None else None
//    p->_cookies = _copy_cookie_jar(_cookies);
    p->body = body;
    p->_body_position = _body_position;
    return p;
}

void PreparedRequest::prepareMethod(QString method)
{}


Request::Request(QString method, QString url, QMap<QString, QString> headers,
                 QByteArray files, QByteArray data, QMap<QString, QString> params,
                 QString auth, QMap<QString, QString> cookies, QString json)
    : method(method)
    , url(url)
    , headers(headers)
    , files(files)
    , data(data)
    , json(json)
    , params(params)
    , auth(auth)
    , cookies(cookies)
{}

PreparedRequest* Request::prepare()
{
    PreparedRequest* p = new PreparedRequest();
    p->prepare(method, url, headers, files, data, params, auth, cookies, json);
    return p;
}
