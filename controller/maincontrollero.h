#ifndef MAINCONTROLLERO_H
#define MAINCONTROLLERO_H

#include <QTimer>
#include <QThread>
#include <QSqlQueryModel>

#include <utils/sqldb.h>
#include <utils/struct.h>
#include <utils/utilsutils.h>

#include <model/serverconfigmodel.h>
#include <model/activetagmodel.h>
#include <model/activeformulamodel.h>
#include <model/piwebapicrawler.h>


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

private:
    void init();
    void initData();
    void simpanFile(QString isi);
    void firstQueueDAQ();
    void firstQueueFormula();
    int  doCrawling(int id, stJobQueue job);
    int  doCalculating(int id, stJobQueue job);

    void sedot(stJobQueue job);

    QThread* th;
    PiWebApiCrawler* pi;
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

};

#endif // MAINCONTROLLERO_H
