#include "piwebapicrawler.h"
#include <QDebug>

//#include <QtNetwork>
#include <QtNetwork>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

PiWebApiCrawler::PiWebApiCrawler()  {
    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedRecorded(QNetworkReply *)));
}

void PiWebApiCrawler::requestWebApi(QString urls)    {
    QNetworkRequest request;
    qDebug() << "url = " << urls;
    QUrl url =  QUrl::fromEncoded(urls.toLocal8Bit().data());

    request.setUrl(url);
    manager.get(request);

    qDebug() << "masuk PiWebApiCrawler request: " << urls;
}


void PiWebApiCrawler::replyFinishedRecorded(QNetworkReply *reply)    {
    qDebug() << "<<<<<< PiWebApiCrawler replyFinished: " ;

}
