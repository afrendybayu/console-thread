#ifndef PIWEBAPICRAWLER_H
#define PIWEBAPICRAWLER_H

#include <QObject>
//#include <QString>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
class QSslError;
class QNetworkReply;
class QAuthenticator;
QT_END_NAMESPACE

class PiWebApiCrawler : public QObject
{
    Q_OBJECT
public:
//    explicit PiWebApiCrawler(QObject *parent = nullptr);
    explicit PiWebApiCrawler(QObject *parent = nullptr, QString arg = "test");
    PiWebApiCrawler(QString arg = "test");

    ~PiWebApiCrawler();
    void init(QString url);

signals:
    void resultReady(QString str);
    void finished();

public slots:
    void run(QString str);
    void slotTesting();

private:
    QNetworkAccessManager manager;
    QString mArg;

private slots:
    void replyFinishedRecorded(QNetworkReply *reply);

};

#endif // PIWEBAPICRAWLER_H
