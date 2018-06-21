#include "maincontrollero.h"
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QObject>

MainControllerO::MainControllerO(QObject *parent) : QObject(parent)
{
    mTimerQueue = new QTimer();
    qDebug() << "masuk constructor MainController";
    this->initData();

    qDebug("CtrlMainWindows isi mServerConfig: %d", mServerConfig->rowCount());
    qDebug("CtrlMainWindows isi mActiveTagDetail: %d", mActiveTag->rowCount());
    qDebug("CtrlMainWindows isi mActiveForDetail: %d", mActiveFormula->rowCount());

    this->connect(mTimerQueue, SIGNAL(timeout()), this, SLOT(updateQueue()));
    mTimerQueue->start(2000);

}

MainControllerO::~MainControllerO()    {
    mTimerQueue = NULL;
    delete mTimerQueue;

    mServerConfig = NULL;
    mActiveTag = NULL;
    mActiveFormula = NULL;

    delete mServerConfig;
    delete mActiveTag;
    delete mActiveFormula;
}

void MainControllerO::pause()    {
    disabled = true;
}

void MainControllerO::resume()  {
    disabled = false;
}

void MainControllerO::updateQueue()   {
    qDebug() << "masuk updateQueue";
//    logMessage( "Masuk ke fungsi updateQueue", QtServiceBase::Success );
}


void MainControllerO::initData() {
    sqlite.openConnDB();

    mServerConfig = new QSqlRelationalTableModel();
    mActiveTag = new QSqlQueryModel();
    mActiveFormula = new QSqlQueryModel();

    modelServerConfig.initData(mServerConfig);
    modelActiveTag.getActiveTag(mActiveTag);
    modelActiveFormula.getActiveFormula(mActiveFormula);

    sqlite.closeConnDB();
}

void MainControllerO::simpanFile(QString isi)   {
    if (!isi.length())  return;
    QFile file(LOG_FILE);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Append))
        return;

    QTextStream out(&file);
    out << isi << "\r\n";
    file.close();
}
