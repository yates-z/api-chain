#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QMap>
#include <QMultiMap>
#include <QList>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QEventLoop>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <iostream>


class BaseHttpResponse: public QObject
{
    Q_OBJECT
public:
    BaseHttpResponse();

    // Returns true if :attr:`status_code` is less than 400, False if not.
    virtual bool ok() = 0;

    // Throw HTTPError if one occured
    virtual QString status_errors() = 0;

    // True if this Response is a well-formed HTTP redirect that could have
    // been processed automatically
    virtual bool is_redirect() = 0;

    // True if this Response one of the permanent versions of redirect.
    virtual bool is_permanent_redirect() = 0;

    // Content of the response, in bytes.
    virtual QByteArray content() = 0;

    // Content of response, in QString.
    virtual QString text() = 0;

    // Returns the json-encoded content of a response, if any.
    virtual QJsonObject json() = 0;

    // Returns the parsed header links of the response, if any.
    virtual QMultiMap<QString, QString> links() = 0;

    QString getHeaderString();

protected:
    QByteArray _content;
    QByteArray _next;

    bool _content_consumed;

    // Integer Code of responded HTTP Status, e.g. 404 or 200.
    QString status_code;

    // Case-insensitive Dictionary of Response Headers.
    // For example, ``headers['content-encoding']`` will return the
    // value of a ``'Content-Encoding'`` response header.
    QMultiMap<QString, QString> headers;

    // File-like object representation of response (for advanced usage).
    // Use of ``raw`` requires that ``stream=True`` be set on the request.
    // This requirement does not apply for use internally to Requests.
    QByteArray raw;

    // Final URL location of Response.
    QString url;

    // Encoding to decode with when accessing r.text.
    QString encoding;

    // A list of :class:`Response <Response>` objects from
    // the history of the Request. Any redirect responses will end
    // up here. The list is sorted from the oldest to the most recent request.
    QList<BaseHttpResponse*> history;

    // Textual reason of responded HTTP Status, e.g. "Not Found" or "OK".
    QString reason;

    // A CookieJar of Cookies the server sent back.
    QList<QNetworkCookie> cookieList;

    // The amount of time elapsed between sending the request
    // and the arrival of the response (as a timedelta).
    // This property specifically measures the time taken between sending
    // the first byte of the request and finishing parsing the headers. It
    // is therefore unaffected by consuming the response content or the
    // value of the ``stream`` keyword argument.
    long elapsed;

    // The :class:`PreparedRequest <PreparedRequest>` object to which this
    // is a response.
//    self.request = None

};


class BaseHttpRequest: public QObject
{
    Q_OBJECT
public:
    enum Engine {QNetWork};
    enum Method {GET, POST, PUT, PATCH, DELETE, HEAD, OPTIONS};
    enum Schema {HTTP, HTTPS};
    BaseHttpRequest();


    virtual BaseHttpResponse* get(QString url=nullptr, QMap<QString, QString> params={}, QMultiMap<QString, QString> headers={},
                     QByteArray files=nullptr, QByteArray data=nullptr, QString auth=nullptr,
                     QMultiMap<QString, QString> cookies={}, QString json=nullptr) = 0;

    virtual void post(QString url=nullptr, QByteArray data=nullptr, QString json=nullptr,
                      QByteArray files=nullptr, QString auth=nullptr, QMap<QString, QString> params={},
                      QMultiMap<QString, QString> cookies={},  QMultiMap<QString, QString> headers={}) = 0;

    virtual void put(QString url=nullptr, QByteArray data=nullptr, QString json=nullptr,
                     QByteArray files=nullptr, QString auth=nullptr, QMap<QString, QString> params={},
                     QMultiMap<QString, QString> cookies={},  QMultiMap<QString, QString> headers={}) = 0;

    virtual void patch(QString url=nullptr, QByteArray data=nullptr, QString json=nullptr,
                       QByteArray files=nullptr, QString auth=nullptr, QMap<QString, QString> params={},
                       QMultiMap<QString, QString> cookies={},  QMultiMap<QString, QString> headers={}) = 0;

    virtual void deleteResource(QString url=nullptr, QByteArray data=nullptr, QString json=nullptr,
                                QByteArray files=nullptr, QString auth=nullptr, QMap<QString, QString> params={},
                                QMultiMap<QString, QString> cookies={},  QMultiMap<QString, QString> headers={}) = 0;

    virtual void head(QString url=nullptr, QMap<QString, QString> params={}, QMultiMap<QString, QString> headers={},
                      QByteArray files=nullptr, QByteArray data=nullptr, QString auth=nullptr,
                      QMultiMap<QString, QString> cookies={}, QString json=nullptr) = 0;

    virtual void options(QString url=nullptr, QMap<QString, QString> params={}, QMultiMap<QString, QString> headers={},
                         QByteArray files=nullptr, QByteArray data=nullptr, QString auth=nullptr,
                         QMultiMap<QString, QString> cookies={}, QString json=nullptr) = 0;
protected:
    // HTTP verb to send to the server.
    Method method;

    // HTTP URL to send the request to.
    QUrl url;

    // dictionary of HTTP headers.
    QMultiMap<QString, QString> headers;

    // The `CookieList` used to create the Cookie header will be stored here
    // after prepare_cookies is called
    QList<QNetworkCookie> cookieList;

    //request body to send to the server.
    QByteArray body;
    QString json;
    QMap<QString, QString> params;
    QString auth;
};



class QtHttpResponse: public BaseHttpResponse
{
    Q_OBJECT
public:
    QtHttpResponse(QNetworkReply* reply=nullptr);
    ~QtHttpResponse();

    friend std::ostream& operator << (std::ostream& os, const QtHttpResponse& p);

    void setReply(QNetworkReply*);

    bool ok();

    QString status_errors();

    bool is_redirect();

    bool is_permanent_redirect();

    QByteArray content();

    QString text();

    QJsonObject json();

    QMultiMap<QString, QString> links();
private:
    QNetworkReply* reply;
};


class QtHttpRequest: public BaseHttpRequest
{
    Q_OBJECT
public:
    QtHttpRequest();
    ~QtHttpRequest();
    friend std::ostream& operator<< (std::ostream& os, const QtHttpRequest& p);


    BaseHttpResponse* get(QString url=nullptr, QMap<QString, QString> params={}, QMultiMap<QString, QString> headers={},
                     QByteArray files=nullptr, QByteArray data=nullptr, QString auth=nullptr,
                     QMultiMap<QString, QString> cookies={}, QString json=nullptr);

    void post(QString url=nullptr, QByteArray data=nullptr, QString json=nullptr,
                      QByteArray files=nullptr, QString auth=nullptr, QMap<QString, QString> params={},
                      QMultiMap<QString, QString> cookies={},  QMultiMap<QString, QString> headers={});

    void put(QString url=nullptr, QByteArray data=nullptr, QString json=nullptr,
                     QByteArray files=nullptr, QString auth=nullptr, QMap<QString, QString> params={},
                     QMultiMap<QString, QString> cookies={},  QMultiMap<QString, QString> headers={});

    void patch(QString url=nullptr, QByteArray data=nullptr, QString json=nullptr,
                       QByteArray files=nullptr, QString auth=nullptr, QMap<QString, QString> params={},
                       QMultiMap<QString, QString> cookies={},  QMultiMap<QString, QString> headers={});

    void deleteResource(QString url=nullptr, QByteArray data=nullptr, QString json=nullptr,
                                QByteArray files=nullptr, QString auth=nullptr, QMap<QString, QString> params={},
                                QMultiMap<QString, QString> cookies={},  QMultiMap<QString, QString> headers={});

    void head(QString url=nullptr, QMap<QString, QString> params={}, QMultiMap<QString, QString> headers={},
                      QByteArray files=nullptr, QByteArray data=nullptr, QString auth=nullptr,
                      QMultiMap<QString, QString> cookies={}, QString json=nullptr);

    void options(QString url=nullptr, QMap<QString, QString> params={}, QMultiMap<QString, QString> headers={},
                         QByteArray files=nullptr, QByteArray data=nullptr, QString auth=nullptr,
                         QMultiMap<QString, QString> cookies={}, QString json=nullptr);
private:
    void prepare(Method method, QString url=nullptr, QMultiMap<QString, QString> headers={},
                 QByteArray files=nullptr, QByteArray data=nullptr, QMap<QString, QString> params={},
                 QString auth=nullptr, QMultiMap<QString, QString> cookies={}, QString json=nullptr);
//    QtHttpRequest* copy();

    // Prepares the given HTTP method.
    void prepareMethod(Method);

    // Prepares the given HTTP URL.
    void prepareURL(const QString, const QMap<QString, QString>&);

    // Prepares the given HTTP headers.
    void prepareHeaders(const QMultiMap<QString, QString>&);

    // Prepares the given HTTP body data.
    void prepareBody(const QByteArray&, const QByteArray&, const QString&);

    // Prepare Content-Length header based on request method and body
    void prepareContentLength(QByteArray);

    // Prepares the given HTTP auth data.
    void prepareAuth(QString, QString url="");

    // Prepares the given HTTP cookie data.
    void prepareCookies(const QMultiMap<QString, QString>&);
private:
    QNetworkAccessManager* manager;
    QNetworkRequest* _request;
};


BaseHttpRequest* request_producer(BaseHttpRequest::Engine engine);


/*
 * The fully mutable :class:`PreparedRequest <PreparedRequest>` object,
 * containing the exact bytes that will be sent to the server.
 *
 *  Instances are generated from a :class:`Request <Request>` object, and
 *  should not be instantiated manually; doing so may produce undesirable
 *  effects.
 */
class PreparedRequest: public QObject
{
public:
    PreparedRequest();
    friend std::ostream& operator<< (std::ostream& os, const PreparedRequest& p)
    {
        os << QString("<PreparedRequest [%1]").arg(p.method).toStdString();
        return os;
    };
    void prepare(QString method=nullptr, QString url=nullptr, QMap<QString, QString> headers={},
                 QByteArray files=nullptr, QByteArray data=nullptr, QMap<QString, QString> params={},
                 QString auth=nullptr, QMap<QString, QString> cookies={}, QString json=nullptr);
    PreparedRequest* copy();
    void prepareMethod(QString);
    void prepareURL(QString, QMap<QString, QString>);
    void prepareHeaders(QMap<QString, QString>);
    void prepareBody(QByteArray, QByteArray, QString);
    void prepareContentLength(QByteArray);
    void prepareAuth(QString, QString url="");
    void prepareCookies(QMap<QString, QString>);
private:
    // HTTP verb to send to the server.
    QString method;
    // HTTP URL to send the request to.
    QString url;
    // dictionary of HTTP headers.
    QMap<QString, QString> headers;
    // request body to send to the server.
    QByteArray body;
    // The `CookieJar` used to create the Cookie header will be stored here
    // after prepare_cookies is called
    QMap<QString, QString> _cookies;
    // integer denoting starting position of a readable file-like body.
    QByteArray _body_position;
};


class Response: public QObject
{};


class Request: public QObject
{
public:
    enum Method {GET, POST, PUT, PATCH, DELETE, HEAD, OPTIONS};
    Request(QString method=nullptr, QString url=nullptr, QMap<QString, QString> headers={},
            QByteArray files=nullptr, QByteArray data=nullptr, QMap<QString, QString> params={},
            QString auth=nullptr, QMap<QString, QString> cookies={}, QString json=nullptr);

    friend std::ostream& operator<< (std::ostream& os, const Request& p)
    {
        os << QString("<Request [%1]").arg(p.method).toStdString();
        return os;
    };

    PreparedRequest* prepare();
private:
    QString method;
    QString url;
    QMap<QString, QString> headers;
    QByteArray files;
    QByteArray data;
    QString json;
    QMap<QString, QString> params;
    QString auth;
    QMap<QString, QString> cookies;
};
#endif // NETWORK_H
