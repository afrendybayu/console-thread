#include "tagtmmsdetailmodel.h"

#include <QDebug>
#include <QtSql>
#include <QSqlRelationalTableModel>

extern QSqlRelationalTableModel *mPiTag;

TagTmmsDetailModel::TagTmmsDetailModel()    {
    qDebug("masuk constructor TagTmmsDetailModel");
    //manager = new QNetworkAccessManager(this);
    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply *)));
//    connect(&manager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), this, SLOT(authenticationRequired(QNetworkReply*,QAuthenticator*)));

#ifndef QT_NO_SSL
    connect(&manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
#endif

}

TagTmmsDetailModel::~TagTmmsDetailModel()    {
    qDebug("masuk destructor TagTmmsDetailModel");
//    manager = NULL;

//    delete manager;
}


int TagTmmsDetailModel::initData(QSqlRelationalTableModel* model)   {
    qDebug("masuk initData tag_tmms_detail TagTmmsDetailModel QSqlRelationalTableModel");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("tag_tmms_detail");

    methodIdx = model->fieldIndex("daq_method");
    statusIdx = model->fieldIndex("status");

    model->setHeaderData(model->fieldIndex("tag"), Qt::Horizontal, tr("Tag"));
    model->setHeaderData(model->fieldIndex("status"), Qt::Horizontal, tr("Status"));
    model->setHeaderData(model->fieldIndex("periode"), Qt::Horizontal, tr("Periode"));
    model->setHeaderData(model->fieldIndex("desc"), Qt::Horizontal, tr("Description"));
    model->setHeaderData(model->fieldIndex("start_dag"), Qt::Horizontal, tr("Start"));
    model->setHeaderData(model->fieldIndex("daq_method"), Qt::Horizontal, tr("Method"));

    if (!model->select()) {
        qDebug() << "error " << model->lastError();
        return -1;
    }

    return model->rowCount();
}

int TagTmmsDetailModel::initDataWebIdRefTmms(QSqlRelationalTableModel* model) {
    qDebug("masuk initData staging_webapi TagTmmsDetailModel QSqlRelationalTableModel");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("staging_webapi");

    model->setHeaderData(model->fieldIndex("tag"), Qt::Horizontal, tr("Tag"));
    model->setHeaderData(model->fieldIndex("id"), Qt::Horizontal, tr("ID"));
    model->setHeaderData(model->fieldIndex("webid"), Qt::Horizontal, tr("WebId"));

    if (!model->select()) {
        qDebug() << "error " << model->lastError();
        return -1;
    }
    /*
    for (int i=0; i<model->rowCount(); i++)   {
        //qDebug() << "data: " << model->record(i).value("Tag").toString();
        QSqlRecord r = model->record(i);
        qDebug() << r.value("tag") << r.value("Tag");
    }
    qDebug() << "+++++++ ada " << model->rowCount();
    //*/
    return model->rowCount();
}

void TagTmmsDetailModel::doReloadTmmsTag()  {
    QString url = "http://localhost/piwebapi2.html";
    this->request(url);
    qDebug() << "TagTmmsDetailModel::doReloadTmmsTag";
}

void TagTmmsDetailModel::request(QString urls)  {
    QNetworkRequest request;
    qDebug() << "url = " << urls;
    QUrl url =  QUrl::fromEncoded(urls.toLocal8Bit().data());

    request.setUrl(url);
//    manager->get(request);
    manager.get(request);
    qDebug() << "Request URL mulai";
}

void TagTmmsDetailModel::replyFinished(QNetworkReply *reply)   {
    qDebug() << "Get Reply";
    QByteArray data;
    data = reply->readAll();
//    qDebug() << data;

    QList<stWebIdPi> webId;
    int i = parsing(data, webId);
    qDebug() << "selesai Reply: "<< webId.count();
    if (i>0)    {
//        emit tesSignal();
        emit sendSyncTmmsDataSignal(webId);
//        emit sigSyncTmmsData(webId);  // Pakai ini jika signal slot jalan
//        syncTmmsTagData(mPiTag, webId);

        qDebug() << "trigger Emit LAGI sigSyncTmmsData";
    }
}

#ifndef QT_NO_SSL
void TagTmmsDetailModel::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qDebug() << "SSL Error: " << errors;
    reply->ignoreSslErrors();
}
#endif

//int TagTmmsDetailModel::parsing(QByteArray data)   {
int TagTmmsDetailModel::parsing(QByteArray data, QList<stWebIdPi> &webId)   {
//QList<TagTmmsDetailModel::stWebIdPi> TagTmmsDetailModel::parsing(QByteArray data)   {
    QJsonDocument JsonDoc = QJsonDocument::fromJson(data);
    QJsonObject o = JsonDoc.object();

    QJsonArray items;
    if (o.count()>0)
        items = o.value("Items").toArray();
    else {
        qDebug() << "ERROR parsing atau tidak ada data !!";
        return 0;
    }

    stWebIdPi tmp;
    for (int i=0; i<items.count(); i++) {
        tmp.id    = items[i].toObject().value("Id").toInt();
        tmp.name  = items[i].toObject().value("Name").toString();
        tmp.webId = items[i].toObject().value("WebId").toString();
        tmp.path  = items[i].toObject().value("Path").toString();
        tmp.type  = items[i].toObject().value("PointType").toString();
        tmp.unit  = items[i].toObject().value("EngineeringUnits").toString();

        //qDebug() <<(i+1)<<". "<<tmp.id<<","<<tmp.name<<","<<tmp.type;
        webId.append(tmp);
    }

    qDebug() << "Finish" << webId.count();
    return items.count();
}

//*
int TagTmmsDetailModel::syncTmmsTagData(QSqlRelationalTableModel* model, QList<stWebIdPi> webId)   {
    qDebug("masuk syncTmmsTagData: %d", webId.count());

//    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("staging_webapi");
/*
    model->setHeaderData(model->fieldIndex("tag"), Qt::Horizontal, tr("Tag"));
    model->setHeaderData(model->fieldIndex("id"), Qt::Horizontal, tr("ID"));
    model->setHeaderData(model->fieldIndex("webid"), Qt::Horizontal, tr("WebId"));
//*/
    if (!model->select()) {
        qDebug() << "error " << model->lastError();
        return -1;
    }

    int x = model->rowCount();
    qDebug() << "jml count: " << x << " : " << model->tableName();

//*

    //QSqlRecord rec = model->record();
    QSqlQuery query;
    int loop = 0;
    for (int i=0; i<webId.count(); i++)   {
        //  QDateTime::currentMSecsSinceEpoch()     QDateTime::currentSecsSinceEpoch()
        QString sql1;
        sql1 = QString("REPLACE INTO staging_webapi (id,tag,webid,created_date,modified_date) VALUES ('%1','%2','%3','%4','%5')").arg(
                        QString::number(webId[i].id), webId[i].name,webId[i].webId,
                        QString::number(QDateTime::currentSecsSinceEpoch()), QString::number(QDateTime::currentSecsSinceEpoch()));

//        qDebug() << "sql: " << sql1;

        QString sql2;
        sql2 = QString("REPLACE INTO tag_tmms_detail (id, tag) VALUES ('%1', '%2')").arg(
                        QString::number(webId[i].id), webId[i].name);

        if (model->database().transaction())    {
            if (!query.exec(sql1)) qDebug() << query.lastError();
            if (!query.exec(sql2)) qDebug() << query.lastError();

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
        loop++;




/*
        rec.setValue("id", QVariant(4444));
        rec.setGenerated("id", false);
        rec.setValue("tag", QVariant("dddd"));
        rec.setValue("webid", QVariant("dddd4444"));
        rec.setValue("created_date", QVariant("2018-06-02 04:25"));
        rec.setValue("modified_date", QVariant("2018-06-02 04:25"));
//*/
/*
//        qDebug() << rec.value("id").toString() << rec.value("webid").toString();
//        rec.setValue("id", webId[i].id);
//        rec.setValue("tag", (webId[i].name));   //
//        rec.setValue("webid", (webId[i].webId));
        qDebug() << rec;

        if (model->insertRecord(model->rowCount(),rec))   {

            model->submit();
            qDebug() << "jml count: " << model->rowCount();

            rec = model->record(0);
            qDebug() << "OK" << rec.value("id").toString() << rec.value("webid").toString();
            rec = model->record(model->rowCount());
            qDebug() << "OK" << rec.value("id").toString() << rec.value("webid").toString();
        }
//*/
    }

    if (!model->select()) {
        qDebug() << "error " << model->lastError();
        return -1;
    }
/*
    qDebug() << "jml Row: " << model->rowCount();

    for (int i=0; i<model->rowCount(); i++)   {
        qDebug() << "data: " << model->record(i).value("tag").toString();
    }
//*/
    qDebug() << "selesai proses DBSqlite -----";
    return model->rowCount();
}
//*/


