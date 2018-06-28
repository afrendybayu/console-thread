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

#define URL_WEBAPI_DATA_RECORDED "https://jsonplaceholder.typicode.com/comments?postId=1"

class PiWebApiCrawler : public QObject
{
    Q_OBJECT
public:
//    explicit PiWebApiCrawler(QObject *parent = nullptr);
    explicit PiWebApiCrawler(QObject *parent = nullptr, QString arg = "test");
    PiWebApiCrawler(QString arg = "test");

    ~PiWebApiCrawler();
    void init(QString url);
    void slotDebug();
    int parsingRecordedDataPiWebApi(int id, QByteArray str, QList<stRecordedDataPiWebAPi> &data, int &lastdata);
    int simpanRecordedDataWebApi(QList<stRecordedDataPiWebAPi> data);


signals:
//    void resultReady(QString str);
    void resultReady(QByteArray ba);
    void finished();

public slots:
    void reqWebApiDataRecorded();
    void run(QString str);
    void slotTesting();


private:
    QNetworkAccessManager manager;
    QNetworkAccessManager* pmanager;

    QNetworkRequest xrequest;
    QString mArg;

private slots:
    void replyFinishedRecorded(QNetworkReply *reply);

};

#endif // PIWEBAPICRAWLER_H
