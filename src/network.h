#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <iostream>



class BaseHttpRequest: public QObject
{
    Q_OBJECT
public:
    enum Engine {QNetWork};
    enum Method {GET, POST, PUT, PATCH, DELETE, HEAD, OPTIONS};
    enum Schema {HTTP, HTTPS};
    BaseHttpRequest();


    virtual void get(QString url=nullptr, QMap<QString, QString> params={}, QMap<QString, QString> headers={},
                     QByteArray files=nullptr, QByteArray data=nullptr, QString auth=nullptr,
                     QMap<QString, QString> cookies={}, QString json=nullptr) = 0;

    virtual void post(QString url=nullptr, QByteArray data=nullptr, QString json=nullptr,
                      QByteArray files=nullptr, QString auth=nullptr, QMap<QString, QString> params={},
                      QMap<QString, QString> cookies={},  QMap<QString, QString> headers={}) = 0;

    virtual void put(QString url=nullptr, QByteArray data=nullptr, QString json=nullptr,
                     QByteArray files=nullptr, QString auth=nullptr, QMap<QString, QString> params={},
                     QMap<QString, QString> cookies={},  QMap<QString, QString> headers={}) = 0;

    virtual void patch(QString url=nullptr, QByteArray data=nullptr, QString json=nullptr,
                       QByteArray files=nullptr, QString auth=nullptr, QMap<QString, QString> params={},
                       QMap<QString, QString> cookies={},  QMap<QString, QString> headers={}) = 0;

    virtual void deleteResource(QString url=nullptr, QByteArray data=nullptr, QString json=nullptr,
                                QByteArray files=nullptr, QString auth=nullptr, QMap<QString, QString> params={},
                                QMap<QString, QString> cookies={},  QMap<QString, QString> headers={}) = 0;

    virtual void head(QString url=nullptr, QMap<QString, QString> params={}, QMap<QString, QString> headers={},
                      QByteArray files=nullptr, QByteArray data=nullptr, QString auth=nullptr,
                      QMap<QString, QString> cookies={}, QString json=nullptr) = 0;

    virtual void options(QString url=nullptr, QMap<QString, QString> params={}, QMap<QString, QString> headers={},
                         QByteArray files=nullptr, QByteArray data=nullptr, QString auth=nullptr,
                         QMap<QString, QString> cookies={}, QString json=nullptr) = 0;
protected:
    // HTTP verb to send to the server.
    Method method;

    // HTTP URL to send the request to.
    QUrl url;

    // dictionary of HTTP headers.
    QMap<QString, QString> headers;

    // The `CookieList` used to create the Cookie header will be stored here
    // after prepare_cookies is called
    QList<QNetworkCookie> cookieList;

    //request body to send to the server.
    QByteArray body;
    QString json;
    QMap<QString, QString> params;
    QString auth;
};



class QtHttpRequest: public BaseHttpRequest
{
    Q_OBJECT
public:
    QtHttpRequest();
    ~QtHttpRequest();
    friend std::ostream& operator<< (std::ostream& os, const QtHttpRequest& p);


    void get(QString url=nullptr, QMap<QString, QString> params={}, QMap<QString, QString> headers={},
                     QByteArray files=nullptr, QByteArray data=nullptr, QString auth=nullptr,
                     QMap<QString, QString> cookies={}, QString json=nullptr);

    void post(QString url=nullptr, QByteArray data=nullptr, QString json=nullptr,
                      QByteArray files=nullptr, QString auth=nullptr, QMap<QString, QString> params={},
                      QMap<QString, QString> cookies={},  QMap<QString, QString> headers={});

    void put(QString url=nullptr, QByteArray data=nullptr, QString json=nullptr,
                     QByteArray files=nullptr, QString auth=nullptr, QMap<QString, QString> params={},
                     QMap<QString, QString> cookies={},  QMap<QString, QString> headers={});

    void patch(QString url=nullptr, QByteArray data=nullptr, QString json=nullptr,
                       QByteArray files=nullptr, QString auth=nullptr, QMap<QString, QString> params={},
                       QMap<QString, QString> cookies={},  QMap<QString, QString> headers={});

    void deleteResource(QString url=nullptr, QByteArray data=nullptr, QString json=nullptr,
                                QByteArray files=nullptr, QString auth=nullptr, QMap<QString, QString> params={},
                                QMap<QString, QString> cookies={},  QMap<QString, QString> headers={});

    void head(QString url=nullptr, QMap<QString, QString> params={}, QMap<QString, QString> headers={},
                      QByteArray files=nullptr, QByteArray data=nullptr, QString auth=nullptr,
                      QMap<QString, QString> cookies={}, QString json=nullptr);

    void options(QString url=nullptr, QMap<QString, QString> params={}, QMap<QString, QString> headers={},
                         QByteArray files=nullptr, QByteArray data=nullptr, QString auth=nullptr,
                         QMap<QString, QString> cookies={}, QString json=nullptr);
private:
    void prepare(Method method, QString url=nullptr, QMap<QString, QString> headers={},
                 QByteArray files=nullptr, QByteArray data=nullptr, QMap<QString, QString> params={},
                 QString auth=nullptr, QMap<QString, QString> cookies={}, QString json=nullptr);
    QtHttpRequest* copy();

    // Prepares the given HTTP method.
    void prepareMethod(Method);

    // Prepares the given HTTP URL.
    void prepareURL(const QString, const QMap<QString, QString>&);

    // Prepares the given HTTP headers.
    void prepareHeaders(const QMap<QString, QString>&);

    // Prepares the given HTTP body data.
    void prepareBody(const QByteArray&, const QByteArray&, const QString&);

    // Prepare Content-Length header based on request method and body
    void prepareContentLength(QByteArray);

    // Prepares the given HTTP auth data.
    void prepareAuth(QString, QString url="");

    // Prepares the given HTTP cookie data.
    void prepareCookies(const QMap<QString, QString>&);
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
