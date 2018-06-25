#ifndef PIWEBAPICRAWLER_H
#define PIWEBAPICRAWLER_H

#include <QObject>
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
    explicit PiWebApiCrawler(QObject *parent = nullptr);
    ~PiWebApiCrawler();

signals:
    void resultReady(const QString &str);

public slots:
    void run(QString str);

private:
    QNetworkAccessManager manager;

private slots:
    void replyFinishedRecorded(QNetworkReply *reply);

};

#endif // PIWEBAPICRAWLER_H
