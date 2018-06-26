#include "piwebapicrawler.h"
#include <QDebug>
#include <QDateTime>
#include <QThread>
#include <QtNetwork>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

//PiWebApiCrawler::PiWebApiCrawler(QObject *parent) : QObject(parent)
//{
////    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedRecorded(QNetworkReply *)));
//}

PiWebApiCrawler::PiWebApiCrawler(QObject *parent, QString arg) : QObject(parent)
{
//    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedRecorded(QNetworkReply *)));
    mArg = arg;
}

PiWebApiCrawler::PiWebApiCrawler(QString arg) : QObject()
{
//    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedRecorded(QNetworkReply *)));
    mArg = arg;
}

PiWebApiCrawler::~PiWebApiCrawler() {

}

void PiWebApiCrawler::run(QString urls) {
    qDebug() << "run Thread piweb craler " << QThread::currentThreadId() << ":" << mArg;
    QNetworkRequest request;
    qDebug() << "url = " << urls;
    QUrl url =  QUrl::fromEncoded(urls.toLocal8Bit().data());

    request.setUrl(url);
    manager.get(request);
}

void PiWebApiCrawler::replyFinishedRecorded(QNetworkReply *reply)    {
    qDebug() << "<<<<<< PiWebApiCrawler replyFinished: " ;
    QString hasil = "tes hasil";
    emit resultReady(hasil);
}

void PiWebApiCrawler::slotTesting() {
    qDebug() << ">>>>>> masuk piwebapicrawler : " << QThread::currentThreadId() << ", arg: " << mArg;
    QThread::sleep(5);
    qDebug() << "<<<<<< selesai piwebapicrawler : " << QThread::currentThreadId();
    emit resultReady("QString result");
    emit finished();
}








