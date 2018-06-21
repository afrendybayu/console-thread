#ifndef PIWEBAPICRAWLER_H
#define PIWEBAPICRAWLER_H

//#include <QObject>
//#include <QtNetwork>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
class QSslError;
class QNetworkReply;
class QAuthenticator;
QT_END_NAMESPACE

#define tagList         "piwebapi/dataservers/s0kxaEHmyBS0qpEYOdDUHV2AVE1TUFJFTUlFUg/points?maxCount=5000"
#define recorded        "piwebapi/streams/{a}/recorded?startTime={b}&endTime={c}&selectedFields=Items.Timestamp;Items.Value"

class PiWebApiCrawler : public QObject  {
    Q_OBJECT
public:
    PiWebApiCrawler();
    void requestWebApi(QString link);

public slots:
    void replyFinishedRecorded(QNetworkReply *reply);
//    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

private:
    QNetworkAccessManager manager;


};

#endif // PIWEBAPICRAWLER_H
