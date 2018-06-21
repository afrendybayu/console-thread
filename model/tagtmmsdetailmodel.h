#ifndef TAGTMMSDETAILMODEL_H
#define TAGTMMSDETAILMODEL_H

#include <QSqlRelationalTableModel>
//#include <QMessageBox>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QAuthenticator>

class TagTmmsDetailModel  : public QSqlRelationalTableModel   {
     Q_OBJECT               // signal slot tidak jalan klo tidak pake Q_OBJECT, bug qt.
public:
    TagTmmsDetailModel();
    virtual ~TagTmmsDetailModel();

    struct stWebIdPi    {
        int id;
        QString name;
        QString path;
        QString unit;
        QString type;
        QString webId;
    };

    int initData(QSqlRelationalTableModel* model);
    int initDataWebIdRefTmms(QSqlRelationalTableModel* model);
    void doReloadTmmsTag();
    int syncTmmsTagData(QSqlRelationalTableModel* model, QList<stWebIdPi> webId);


public slots:
    void replyFinished(QNetworkReply *reply);
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

signals:
//    void sigSyncTmmsData(QList<stWebIdPi> &webId);
    void sendSyncTmmsDataSignal(QList<stWebIdPi> &webId);


private:
    int methodIdx;
    int statusIdx;


    void request(QString urls);
    int parsing(QByteArray data, QList<stWebIdPi> &webId);

//    QNetworkAccessManager *manager;
    QNetworkAccessManager manager;

};

#endif // TAGTMMSDETAILMODEL_H
