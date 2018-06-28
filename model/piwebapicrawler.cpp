#include "piwebapicrawler.h"
#include <QDebug>
#include <QDateTime>
#include <QThread>
#include <QtSql>
#include <QSqlQuery>
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

    emit resultReady(mArg.toUtf8());
    emit finished();
//*/
}

void PiWebApiCrawler::replyFinishedRecorded(QNetworkReply *reply)    {
    qDebug() << " 2 -----------------------------";
    qDebug() << "<<<<<< PiWebApiCrawler replyFinished: " ;
//    QString hasil = "tes hasil";
    QByteArray ba = reply->readAll();
    reply->deleteLater();

/*
    // kalau penyimpanan langsung dari model. *Tapi belum dapat id titik ukur
    int id, last;
    QList<stRecordedDataPiWebAPi> data;
    parsingRecordedDataPiWebApi(id, ba, data, last);
    simpanRecordedDataWebApi(data);
//*/

    emit resultReady(ba);
//    emit resultReady(mArg);
    emit finished();
}

void PiWebApiCrawler::slotTesting() {
    qDebug() << ">>>>>> masuk piwebapicrawler : " << QThread::currentThreadId() << ", arg: " << mArg;
    QThread::sleep(5);
    qDebug() << "<<<<<< selesai piwebapicrawler : " << QThread::currentThreadId();
//    emit resultReady(mArg);
    emit resultReady(QString("tesSlot").toUtf8());
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
    stRecordedDataPiWebAPi tmp;
    for (int i=0; i<items.count(); i++) {
        tmp.id    = id;
        tmp.value = (float) items[i].toObject().value("Value").toDouble();
        t = items[i].toObject().value("Timestamp").toString().left(23); // jumlah character harus SAMA persis
        tmp.dt    = QDateTime::fromString(t,"yyyy-MM-ddTHH:mm:ss.zzz");
        tmp.epoch = (int) tmp.dt.toSecsSinceEpoch();
        data.append(tmp);
    }

//    qDebug() << "Finish:" << data.count();
    return items.count();
}

int PiWebApiCrawler::simpanRecordedDataWebApi(QList<stRecordedDataPiWebAPi> data) {

    // bagi query menjadi tiap kelipatan 20 insert data.
    int nInsert = 20;
    if (data.count()<=0)    return -1;
    QString s = "";
    QStringList lquery;

    int jml = (int) ((data.count()%nInsert)?((data.count()/nInsert)+1):(data.count()/nInsert));
    int urut = 0, list = 0;

    for (int i=0; i<data.count(); i++)   {
        qDebug() << "id:"<< data[i].id<<", value: "<<data[i].value;
        if (urut==0)    {
            if (list)   {
                lquery.append(s);
            }
            s = QString("INSERT INTO data (id, value, epoch) VALUES ");
            s.append(QString("('%1','%2','%3')")
                     .arg(QString::number(data[i].id),QString::number(data[i].value),QString::number(data[i].epoch)));
            list++;
        }
        else {
            s.append(QString(",('%1','%2','%3')")
                    .arg(QString::number(data[i].id),QString::number(data[i].value),QString::number(data[i].epoch)));
        }
        urut = (urut+1)%nInsert;
    }
    lquery.append(s);

    QSqlQuery query;
    int loop = 0, tersimpan = 0;

//*  dimatikan dulu. Nunggu model.
//    if (model->database().transaction())    {
        for (int i=0; i<list; i++)  {
            qDebug() << (i+1) << ":"<< lquery[i];
//            if (!query.exec(lquery[i])) qDebug() << query.lastError();
//            else tersimpan++;
        }

/*
        if (!model->database().commit()) {
            qDebug() << "gagal transaksi & commit !! Lanjutkan proses berikutnya : " << query.lastError();
            if (model->database().rollback())   {
                qDebug() << "database rollback";
            }
            if (loop>5) {       // gagal transaksi berturut-turut
                return -1;
            }
        }
    }
//*/
    return tersimpan;
}





