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
    pmanager = new QNetworkAccessManager;
//    prequest = new QNetworkRequest;

//    connect(pmanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedRecorded(QNetworkReply*)));
    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedRecorded(QNetworkReply *)));
    mArg = arg;

}

PiWebApiCrawler::~PiWebApiCrawler() {
    pmanager = NULL;
    delete pmanager;

//    prequest = NULL;
//    delete prequest;
}

void PiWebApiCrawler::run(QString urls) {
    qDebug() << "run Thread piweb craler " << QThread::currentThreadId() << ":" << mArg;
    qDebug() << "url = " << urls;
    QUrl url =  QUrl::fromEncoded(urls.toLocal8Bit().data());

//    QNetworkRequest request;
    xrequest.setUrl(url);
    manager.get(xrequest);

//    xrequest.setUrl(url);
//    pmanager->get(xrequest);
}

void PiWebApiCrawler::reqWebApiDataRecorded() {
    qDebug() << "run Thread piweb crawler " << QThread::currentThreadId() << ":" << mArg;

    QNetworkRequest request;
    QString urls = URL_WEBAPI_DATA_RECORDED;
//    qDebug() << "url = " << urls;
    QUrl url =  QUrl::fromEncoded(urls.toLocal8Bit().data());
//    qDebug() << " 9 -----------------------------";

    request.setUrl(url);
//*
//    qDebug() << "sampe sini";
//    qDebug() << " 8 -----------------------------";
    //QObject: Cannot create children for a parent that is in a different thread.
    //(Parent is QNetworkAccessManager(0x1eab6a0), parent's thread is QThread(0x1e78fe0), current thread is QThread(0x1e9c3d0)
//    manager.get(request);


    qDebug() << " 1 -----------------------------";
//*/
//*
    QThread::sleep(5);

    emit resultReady(mArg);
    emit finished();
//*/
}

void PiWebApiCrawler::replyFinishedRecorded(QNetworkReply *reply)    {
    qDebug() << " 2 -----------------------------";
    qDebug() << "<<<<<< PiWebApiCrawler replyFinished: " ;
//    QString hasil = "tes hasil";
    QByteArray ba = reply->readAll();
    reply->deleteLater();

    qDebug() << ba;
    QJsonObject json;
//    json.begin()
//    ba.toUpper()
//    emit resultReady(QString(reply->readAll()));
    emit resultReady(mArg);
    emit finished();
}

void PiWebApiCrawler::slotTesting() {
    qDebug() << ">>>>>> masuk piwebapicrawler : " << QThread::currentThreadId() << ", arg: " << mArg;
    QThread::sleep(5);
    qDebug() << "<<<<<< selesai piwebapicrawler : " << QThread::currentThreadId();
    emit resultReady(mArg);
    emit finished();
}

void PiWebApiCrawler::slotDebug() {
    qDebug() << ">>>>>> masuk slotDebug";
}

int PiWebApiCrawler::parsingRecordedDataPiWebApi(int id, QByteArray str, QList<stRecordedDataPiWebAPi> &data, int &lastdata)  {
    QJsonDocument JsonDoc = QJsonDocument::fromJson(str);
    QJsonObject o = JsonDoc.object();

    QJsonArray items;
    if (o.count()>0)
        items = o.value("Items").toArray();
    else {
        qDebug() << "ERROR parsing atau tidak ada data !!";
        return 0;
    }
    QString t;
//    QDateTime dt;

    stRecordedDataPiWebAPi tmp;
    for (int i=0; i<items.count(); i++) {
        tmp.id    = id;
        tmp.value = (float) items[i].toObject().value("Value").toDouble();
        t = items[i].toObject().value("Timestamp").toString().left(23);
        tmp.dt    = QDateTime::fromString(t,"yyyy-MM-ddTHH:mm:ss.zzz");
        tmp.epoch = (int) tmp.dt.toSecsSinceEpoch();
        //  "2018-05-04T06:07:46.6890106Z"
//        dt = QDateTime::fromString(t,"yyyy-MM-ddThh:mm:ss.zzz");
//        qDebug() << t << dt << dt.toString()  << dt.toString("yyyy-MM-dd");
        data.append(tmp);
    }

    qDebug() << "Finish:" << data.count();
    return items.count();
}






