#ifndef MAINCONTROLLERO_H
#define MAINCONTROLLERO_H

#include <QTimer>
#include <QSqlRelationalTableModel>

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

private:
    void initData();
    void simpanFile(QString isi);

    bool disabled;

    QTimer *mTimerQueue;
    QTimer *mTimerExe;

    SqlDb sqlite;
    UtilsUtils utils;
    QList<stJobQueue> jobQueue;

    ServerConfigModel modelServerConfig;
    ActiveTagModel modelActiveTag;
    ActiveFormulaModel modelActiveFormula;

    QSqlRelationalTableModel *mServerConfig;
    QSqlQueryModel *mActiveTag;
    QSqlQueryModel *mActiveFormula;

};

#endif // MAINCONTROLLERO_H
