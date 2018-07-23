#include <QDebug>
#include <QDateTime>
#include <QThread>
#include <QtSql>
#include <QSqlQuery>
#include <QtNetwork>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include "piwebapimodel.h"
#include <utils/sqldb.h>

#define URL_WEBAPI_DATA_RECORDED "http://localhost/piwebapi/"

PiWebApiModel::PiWebApiModel(QObject *parent) : QObject(parent) {
    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedRecorded(QNetworkReply *)));
}

PiWebApiModel::~PiWebApiModel() {
    pmanager = NULL;
    delete pmanager;
}

void PiWebApiModel::slotTesting() {
    qDebug() << ">>>>>>>>>> masuk PiWebApiModel::slotTesting" << QThread::currentThreadId() << mJob.tag << "pi:"<< mPi;
//    emit signalMasukPi(this->mTh, this->mPi);
    qDebug() << mJob.tag << ":" << mJob.thId;
    QThread::sleep(4);

    QByteArray ba = QString("ini hasilnya").toUtf8();
    emit resultReadyTh(mJob.thId, mUrut, mTh, mPi, ba);
//    emit finished();
//    qDebug() << "emit finished"<< mTh << mPi;
}

void PiWebApiModel::passingParam(stJobQueue job, int urut, int th, int pi)  {
    this->mJob = job;
    this->mUrut = urut;
    this->mTh = th;
    this->mPi = pi;
    qDebug() << "[++++++++++++++++] PiWebApiModel::passingParam"<< job.tag << mTh <<", pi:"<< mPi;
}


void PiWebApiModel::reqWebApiDataRecordedSingle(stJobQueue job) {
    this->mJob = job;
    qDebug() << "run Thread piweb crawler " << QThread::currentThreadId() << ":" << job.tag;
    QString awal  = getLastDataTime(job.tag);


//    QString akhir = QDateTime::fromString(awal, "yyyy-MM-dd 00:00:00").addDays(1).addSecs(-1).toString("yyyy-MM-dd HH:mm:ss");
//    qDebug() << "last data: " << last;

    QNetworkRequest request;
//    qDebug() << " 9 -----------------------------";
    QString urls = URL_WEBAPI_DATA_RECORDED + job.webId
            + "/recorded.html?countMax=20000&startTime="+awal
            + "&selectedFields=Items.Timestamp;Items.Value";   //+"&endTime="+akhir;
//    qDebug() << "url = " << urls;
    QUrl url =  QUrl::fromEncoded(urls.toLocal8Bit().data());
//    qDebug() << " 9 -----------------------------";

    request.setUrl(url);
//*
    //QObject: Cannot create children for a parent that is in a different thread.
    //(Parent is QNetworkAccessManager(0x1eab6a0), parent's thread is QThread(0x1e78fe0), current thread is QThread(0x1e9c3d0)
    manager.get(request);


//    qDebug() << " 1 -----------------------------";
//*/
/*
    QThread::sleep(5);

    emit resultReady(mArg.toUtf8());
    emit finished();
//*/
}

void PiWebApiModel::replyFinishedRecorded(QNetworkReply *reply)    {
    qDebug() << " 2 -----------------------------";
    qDebug() << "<<<<<< PiWebApiCrawler replyFinished:"<< this->mJob.tag << this->mJob.id;
//    QString hasil = "tes hasil";
    QByteArray ba = reply->readAll();
    reply->deleteLater();

//    qDebug() << ba;

    // kalau penyimpanan langsung dari model. *Tapi belum dapat id titik ukur
//    int last;
    QList<stRecordedDataPiWebAPi> data;
//    parsingRecordedDataPiWebApi(this->mJob.id, ba, data);
//    simpanRecordedDataWebApi(data);

    emit resultReadyTh(mJob.thId, mUrut, mTh, mPi, ba);
//    emit resultReady(ba);

#ifdef MULTI_THREAD
    emit resultReadyTh(mJob.thId, ba);
#endif
//    emit resultReady(mArg);
    emit finished();
    qDebug()<< "<<<<<< finished Simpan Recorded Data PiWebApiCrawler";
}


QString PiWebApiModel::getLastDataTime(QString tag)  {
    QSqlQueryModel model;
    QString q = QString("select (select webid from staging_webapi where tag like '\%%1\%') as webid "
                ", ifnull((select last_update from tag_tmms_detail where tag like '\%1\%'),'0') as last_data "
                ", (select desc from option where nama like '%daq_day_ago%') as day_ago")
            .arg(tag);
//    qDebug() << "sql: "<< q;
    {
        SqlDb sql;
        sql.openConnDB();
        model.setQuery(q);
        sql.closeConnDB();
    }
    QStringList list = QSqlDatabase::connectionNames();
    for(int i = 0; i < list.count(); ++i) {
        QSqlDatabase::removeDatabase(list[i]);
    }

    QString webid;
    int epoch, days;
    qDebug() << "getLastDataTime: " << model.rowCount();
//    for (int i=0; i<model.rowCount(); i++)  {
        QSqlRecord rec = model.record(0);
//        qDebug() << rec;
        webid = rec.value("webid").toString();
        epoch = rec.value("last_data").toInt();
        days  = rec.value("day_ago").toInt();
//    }
    qDebug() << "rec: " << webid << epoch << days;
    if (!epoch) {
        return QDateTime::currentDateTime().addDays(-days).toString("yyyy-MM-dd 00:00:00");
    }
    else {
        return QDateTime::fromSecsSinceEpoch(epoch).toString("yyyy-MM-dd 00:00:00");
    }


    return "tgl";
}
