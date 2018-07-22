#ifndef MAINCONTROLLERO_H
#define MAINCONTROLLERO_H

#include <QTimer>
#include <QThread>
#include <QSqlQueryModel>
#include <QMutex>

#include <utils/sqldb.h>
#include <utils/struct.h>
#include <utils/utilsutils.h>

#include <model/serverconfigmodel.h>
#include <model/activetagmodel.h>
#include <model/activeformulamodel.h>
#include <model/piwebapicrawler.h>

#include <model/piwebapimodel.h>


class MainControllerO : public QObject
{
    Q_OBJECT
public:
    explicit MainControllerO(QObject *parent = nullptr);
    ~MainControllerO();
    void pause();
    void resume();



signals:

public slots:

private slots:
    void updateQueue();
    void exeQueue();
    void slotThFinish();
    void slotGetResultPiCrawler(QByteArray resp);
    void slotGetResultPiCrawlerTh(int thId, int urut, int th, int pi, QByteArray resp);
    void slotThreadFinished();
    void slotMasukPi(int th, int pi);

private:
    void init();
    void initData();
    void simpanFile(QString isi);
    void firstQueueDAQ();
    void firstQueueFormula();
    int  doCrawling(int id, stJobQueue job);
    int  doCalculating(int id, stJobQueue job);

    int  doCrawling(stJobQueue job, int urut);

    void sedot(stJobQueue job);

    QThread* th;
    PiWebApiCrawler* pi;

    QThread* pth;
    PiWebApiModel* ppi;
    bool disabled;
    int threadCount;
    bool ajaxDone;
//    PiWebApiCrawler pis;

    QNetworkAccessManager* pmanager;

    QTimer *mTimerQueue;
    QTimer *mTimerExe;

//    SqlDb sqlite;
    UtilsUtils utils;
    QList<stJobQueue> jobQueue;

    ServerConfigModel modelServerConfig;
    ActiveTagModel modelActiveTag;
    ActiveFormulaModel modelActiveFormula;

    QSqlQueryModel *mServerConfig;
    QSqlQueryModel *mActiveTag;
    QSqlQueryModel *mActiveFormula;

    int jmlThread;
    QList<int> iTh;
    QList<int> pidTh;
    QMutex mutex;
};

#endif // MAINCONTROLLERO_H
