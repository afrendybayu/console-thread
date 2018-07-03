#include <QDebug>
#include <QDateTime>
#include <QThread>
#include <QtSql>
#include <QSqlQuery>
#include <QtNetwork>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include "piwebapicrawler.h"
#include <utils/sqldb.h>

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

//PiWebApiCrawler::PiWebApiCrawler(QString arg, QNetworkAccessManager manager) : QObject() {

//}

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

//void PiWebApiCrawler::reqWebApiDataRecordedSingle(QString tag) {
void PiWebApiCrawler::reqWebApiDataRecordedSingle(stJobQueue job) {
    this->mJob = job;
    qDebug() << "run Thread piweb crawler " << QThread::currentThreadId() << ":" << job.tag;
    QString awal  = getLastDataTime(job.tag);
//    QString akhir = QDateTime::fromString(awal, "yyyy-MM-dd 00:00:00").addDays(1).addSecs(-1).toString("yyyy-MM-dd HH:mm:ss");
//    qDebug() << "last data: " << last;

    QNetworkRequest request;
//    qDebug() << " 9 -----------------------------";
    QString urls = URL_WEBAPI_DATA_RECORDED + job.webId
            + "/recorded.html?countMax=100000&startTime="+awal
            + "&selectedFields=Timestamp;Value";   //+"&endTime="+akhir;
    qDebug() << "url = " << urls;
    QUrl url =  QUrl::fromEncoded(urls.toLocal8Bit().data());
//    qDebug() << " 9 -----------------------------";

    request.setUrl(url);
//*
//    qDebug() << "sampe sini";
//    qDebug() << " 8 -----------------------------";
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


void PiWebApiCrawler::reqWebApiDataRecorded() {
    qDebug() << "run Thread piweb crawler " << QThread::currentThreadId() << ":" << mArg;

    QNetworkRequest request;
    qDebug() << " 9 -----------------------------";
    QString urls = URL_WEBAPI_DATA_RECORDED;
//    qDebug() << "url = " << urls;
    QUrl url =  QUrl::fromEncoded(urls.toLocal8Bit().data());
    qDebug() << " 9 -----------------------------";

    request.setUrl(url);
//*
//    qDebug() << "sampe sini";
    qDebug() << " 8 -----------------------------";
    //QObject: Cannot create children for a parent that is in a different thread.
    //(Parent is QNetworkAccessManager(0x1eab6a0), parent's thread is QThread(0x1e78fe0), current thread is QThread(0x1e9c3d0)
    manager.get(request);


    qDebug() << " 1 -----------------------------";
//*/
/*
    QThread::sleep(5);

    emit resultReady(mArg.toUtf8());
    emit finished();
//*/
}

void PiWebApiCrawler::replyFinishedRecorded(QNetworkReply *reply)    {
    qDebug() << " 2 -----------------------------";
    qDebug() << "<<<<<< PiWebApiCrawler replyFinished:"<< this->mJob.tag << this->mJob.id;
//    QString hasil = "tes hasil";
    QByteArray ba = reply->readAll();
    reply->deleteLater();

    qDebug() << ba;
//*
    // kalau penyimpanan langsung dari model. *Tapi belum dapat id titik ukur
//    int last;
    QList<stRecordedDataPiWebAPi> data;
    parsingRecordedDataPiWebApi(this->mJob.id, ba, data);
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

QString PiWebApiCrawler::getLastDataTime(QString tag)  {
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

int PiWebApiCrawler::parsingRecordedDataPiWebApi(int id, QByteArray str, QList<stRecordedDataPiWebAPi> &data)  {
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
        t = items[i].toObject().value("Timestamp").toString().left(19); // jumlah character harus SAMA persis
        tmp.dt    = QDateTime::fromString(t,"yyyy-MM-ddTHH:mm:ss");
        tmp.epoch = (int) tmp.dt.toSecsSinceEpoch();
        qDebug() << t << tmp.dt  << tmp.dt.toString("yyyy-MM-dd HH:mm:ss") << tmp.epoch;
        data.append(tmp);
    }

//    qDebug() << "Finish:" << data.count();
    return items.count();
}

int PiWebApiCrawler::simpanRecordedDataWebApi(QList<stRecordedDataPiWebAPi> data) {
    if (data.count()<=0)    return -1;

    // bagi query menjadi tiap kelipatan 20 insert data.
    int nInsert = 50;
    QString s = "";
    QStringList lquery;

//    int jml = (int) ((data.count()%nInsert)?((data.count()/nInsert)+1):(data.count()/nInsert));
    int urut = 0, list = 0;

    for (int i=0; i<data.count(); i++)   {
        qDebug() << "id:"<< data[i].id<<", value: "<<data[i].value << ",waktu: " << data[i].epoch;
        if (urut==0)    {
            if (list)   {
                lquery.append(s);
            }
            s = QString("REPLACE INTO data (id, value, epochtime) VALUES ");
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

    int tersimpan = 0;
    {
        SqlDb sqlite;
        QSqlQueryModel model;       // cara sesat !!!

        sqlite.openConnDB();
        QString qs = "INSERT INTO data (id, epochtime, value) VALUES ('1234','1234567','123.456')";

//*
        for (int i=0; i<list; i++)  {
//            qDebug() << (i+1) << ":"<< lquery[i];
//            if (!query.exec(lquery[i]))
//                qDebug() << query.lastError();
            model.setQuery(lquery[i]);
            tersimpan++;
        }
//*/
         sqlite.closeConnDB();
    }
    QStringList conList = QSqlDatabase::connectionNames();
    for(int i = 0; i < conList.count(); ++i) {
        QSqlDatabase::removeDatabase(conList[i]);
    }

    return tersimpan;
}





