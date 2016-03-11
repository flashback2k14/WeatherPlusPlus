#ifndef APICALL_H
#define APICALL_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDebug>
#include <QUrl>
#include <QUrlQuery>
#include <QByteArray>


class ApiCall : public QObject {

Q_OBJECT

private:
    QString mUri;

public:
    /**
     * Constructor / Destructor
     */
    ApiCall(QString uri) : mUri(uri) {}
    ~ApiCall(){}

    /**
     * Send Request
     */
    QByteArray sendRequest() {
        // create custom temporary event loop on stack
        QEventLoop eventLoop;
        // create network access manager
        QNetworkAccessManager *mAccessManager = new QNetworkAccessManager(this);
        // "quit()" the event-loop, when the network request "finished()"
        connect(mAccessManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
        // send HTTP Request and catch Response
        QNetworkReply *reply =  mAccessManager->get(QNetworkRequest(QUrl(mUri)));
        // blocks stack until "finished()" has been called
        eventLoop.exec();
        // check Response
        if (reply->error() == QNetworkReply::NoError) {
            // success
            return reply->readAll();
        } else {
            // error
            return reply->errorString().toUtf8();
        }
    }

};

#endif
