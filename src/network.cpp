#include "network.h"

BaseHttpRequest::BaseHttpRequest()
{}

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

void QtHttpRequest::get(QString url, QMap<QString, QString> params, QMap<QString, QString> headers, QByteArray files, QByteArray data, QString auth, QMap<QString, QString> cookies, QString json)
{
    prepare(GET, url, headers, files, data, params, auth, cookies, json);
}

void QtHttpRequest::post(QString url, QByteArray data, QString json, QByteArray files, QString auth, QMap<QString, QString> params, QMap<QString, QString> cookies, QMap<QString, QString> headers)
{}

void QtHttpRequest::patch(QString url, QByteArray data, QString json, QByteArray files, QString auth, QMap<QString, QString> params, QMap<QString, QString> cookies, QMap<QString, QString> headers)
{}

void QtHttpRequest::put(QString url, QByteArray data, QString json, QByteArray files, QString auth, QMap<QString, QString> params, QMap<QString, QString> cookies, QMap<QString, QString> headers)
{}

void QtHttpRequest::deleteResource(QString url, QByteArray data, QString json, QByteArray files, QString auth, QMap<QString, QString> params, QMap<QString, QString> cookies, QMap<QString, QString> headers)
{}

void QtHttpRequest::head(QString url, QMap<QString, QString> params, QMap<QString, QString> headers, QByteArray files, QByteArray data, QString auth, QMap<QString, QString> cookies, QString json)
{}

void QtHttpRequest::options(QString url, QMap<QString, QString> params, QMap<QString, QString> headers, QByteArray files, QByteArray data, QString auth, QMap<QString, QString> cookies, QString json)
{}

void QtHttpRequest::prepare(Method method, QString url, QMap<QString, QString> headers, QByteArray files, QByteArray data, QMap<QString, QString> params, QString auth, QMap<QString, QString> cookies, QString json)
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
    this->url = url;
}


void QtHttpRequest::prepareHeaders(const QMap<QString, QString>& headers)
{
    for (auto iter = headers.cbegin(); iter != headers.cend(); iter++)
        _request->setRawHeader(iter.key().toUtf8(), iter.value().toUtf8());
    this->headers = headers;
}

void QtHttpRequest::prepareCookies(const QMap<QString, QString>& cookies)
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
