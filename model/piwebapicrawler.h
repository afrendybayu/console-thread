#ifndef PIWEBAPICRAWLER_H
#define PIWEBAPICRAWLER_H

#include <QObject>
#include <utils/struct.h>
//#include <QString>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
class QSslError;
class QNetworkReply;
class QAuthenticator;
QT_END_NAMESPACE

//#define URL_WEBAPI_DATA_RECORDED "https://jsonplaceholder.typicode.com/comments?postId=1"
#define URL_WEBAPI_DATA_RECORDED "http://localhost/piwebapi/"

class PiWebApiCrawler : public QObject
{
    Q_OBJECT
public:
//    explicit PiWebApiCrawler(QObject *parent = nullptr);
//    explicit PiWebApiCrawler(QObject *parent = nullptr, QString arg = "test");
    PiWebApiCrawler(QString arg = "test");

    ~PiWebApiCrawler();
    void init(QString url);
    void slotDebug();
    int parsingRecordedDataPiWebApi(int id, QByteArray str, QList<stRecordedDataPiWebAPi> &data);
    int simpanRecordedDataWebApi(QList<stRecordedDataPiWebAPi> data);
    void reqWebApiDataRecordedSingle(stJobQueue job);
    QString getLastDataTime(QString tag);

signals:
//    void resultReady(QString str);
    void resultReady(QByteArray ba);
    void resultReadyTh(int thId, QByteArray ba);
    void signalMasukPi(int th, int pi);
    void finished();

public slots:
    void reqWebApiDataRecorded();
    void run(QString str);
    void slotTesting();


private:
    stJobQueue mJob;
    QNetworkAccessManager manager;
    QNetworkAccessManager* pmanager;

    QNetworkRequest xrequest;
    QString mArg;


private slots:
    void replyFinishedRecorded(QNetworkReply *reply);
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
//    void PiWebApiCrawler::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);

#ifndef QT_NO_SSL
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
#endif

};

#endif // PIWEBAPICRAWLER_H
