#ifndef PIWEBAPIMODEL_H
#define PIWEBAPIMODEL_H

#include <QObject>
#include <utils/struct.h>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
class QSslError;
class QNetworkReply;
class QAuthenticator;
QT_END_NAMESPACE

class PiWebApiModel : public QObject
{
    Q_OBJECT
public:
    explicit PiWebApiModel(QObject *parent = nullptr);
    ~PiWebApiModel();
    void reqWebApiDataRecordedSingle(stJobQueue job);
    void passingParam(stJobQueue job, int urut);

signals:
    void resultReadyTh(int thId, int urut, QByteArray ba);
    void finished();

public slots:
    void slotTesting();
//    void reqWebApiDataRecorded();

private:
    stJobQueue mJob;
    QNetworkAccessManager manager;
    QNetworkAccessManager* pmanager;

    QNetworkRequest xrequest;
    QString mArg;
    int mUrut;

    QString getLastDataTime(QString tag);

private slots:
    void replyFinishedRecorded(QNetworkReply *reply);


};

#endif // PIWEBAPIMODEL_H
