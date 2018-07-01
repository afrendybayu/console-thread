#include "maincontrollero.h"
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QObject>
#include <QtSql>

#include <QScriptEngine>


#ifdef   Q_OS_UNIX
#define LOG_FILE "log.txt"
#else   // Q_OS_WINDOWS
#define LOG_FILE "C:/Users/afrendy/Documents/koding/ext/log.txt"
#endif

void tesDataRecorded()  {
    qDebug() << "bisakah ??";


    QFile file("./airinlet.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString str;
    while (!in.atEnd()) {
        str += in.readLine();
    }
    qDebug() << str;
    QByteArray ba = str.toUtf8();

    PiWebApiCrawler p("");
    QList<stRecordedDataPiWebAPi> data;
    int last;
    int a = p.parsingRecordedDataPiWebApi(1000, ba, data, last);

    /*
    for (int i=0; i<a; i++) {
        qDebug() <<"id:"<< data[i].id <<", value:"<< data[i].value
                <<", waktu:"<< data[i].dt.toString("yyyy-MM-dd HH:mm:ss.zzz") << data[i].epoch;
    }
    //*/
    p.simpanRecordedDataWebApi(data);
}

void tesScriptEngine()  {
/*
    QFile file("./hitung.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString str = "";
    while (!in.atEnd()) {
        str += in.readLine();
    }
    qDebug() << str;
//*/




    ActiveFormulaModel f;
    QStringList args;

//    f.getCurrentFormula(tag, formula, args);
//    f.prosesFormulaScript(str, args);
}

MainControllerO::MainControllerO(QObject *parent) : QObject(parent)
{

//    tesDataRecorded();
//    return;

    qDebug() << "masuk thread MainControllerO : "<< QThread::currentThreadId();
    init();
//    tesScriptEngine();

//    connect(pi, &PiWebApiCrawler::finished, pi, &QObject::deleteLater, Qt::DirectConnection);
//    connect(th, &QThread::finished, pi, &QObject::deleteLater);
//    connect(th, SIGNAL(finished()), th, SLOT(deleteLater()));

/*
    connect(th, &QThread::started, pi, &PiWebApiCrawler::slotTesting);
    connect(pi, SIGNAL(resultReady(QString)), this, SLOT(slotFinish(QString)));
    connect(pi, SIGNAL(finished()), th, SLOT(quit()));          // mandatory
    connect(pi, SIGNAL(finished()), pi, SLOT(deleteLater()));   // require th::quit. Jika mandiri, optional(?)
//*/

//    pi.moveToThread(&th);
//    th.start();

//    pi->moveToThread(th);
//    th->start();



}

//void MainControllerO::slotGetResultPiCrawler(QString resp)  {
void MainControllerO::slotGetResultPiCrawler(QByteArray resp)  {

    qDebug() << "+++ masuk MainControllerO::slotGetResultPiCrawler, parsing Data" << resp;
    PiWebApiCrawler px("");
    int id, last;
    QList<stRecordedDataPiWebAPi> data;

    px.parsingRecordedDataPiWebApi(id, resp, data, last);
    //    while (!th->isFinished()) {
//        QThread::sleep(1);
//        qDebug() << "MASIH jalan";
//    }
//    while(th->isRunning());
//        qDebug() << "sudah mati";
//    else
//        qDebug() << "masih jalan";
//    delete th;
//    delete pi;
}

void MainControllerO::slotThFinish()    {

    qDebug() << "+++ masuk MainControllerO::slotThFinish" << th->currentThreadId() << th->isRunning()
             << "thread: " << threadCount;
    pi->slotDebug();
    th = NULL;
    pi = NULL;

    delete th;
    delete pi;
    threadCount = (threadCount<=0)?0:(threadCount-1);
    qDebug() << "sisa thread: " << threadCount;
}

MainControllerO::~MainControllerO()    {
    mTimerQueue = NULL;
    delete mTimerQueue;
    mTimerExe = NULL;
    delete mTimerExe;

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

void MainControllerO::init()    {

    threadCount = 0;
    mTimerQueue = new QTimer();
    mTimerExe = new QTimer();



    qDebug() << "masuk constructor MainController" << QThread::currentThreadId()
             << ", idealThreadCount: " << QThread::idealThreadCount();
    this->initData();

    qDebug("CtrlMainWindows isi mServerConfig: %d", mServerConfig->rowCount());
    qDebug("CtrlMainWindows isi mActiveTagDetail: %d", mActiveTag->rowCount());
    qDebug("CtrlMainWindows isi mActiveForDetail: %d", mActiveFormula->rowCount());

    this->connect(mTimerQueue, SIGNAL(timeout()), this, SLOT(updateQueue()));
    this->connect(mTimerExe, SIGNAL(timeout()), this, SLOT(exeQueue()));
    mTimerQueue->start(5000);
//    mTimerExe->start(1000);
    QString str = QString("\r\n\r\n-------------------------------\r\nmasuk constructor MainController");
//           .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    simpanFile(str);
//    firstQueueDAQ();
    firstQueueFormula();
}

void MainControllerO::updateQueue()   {
    if (disabled) return;


//    qDebug() << "masuk updateQueue" << QThread::currentThreadId();  //<<"/";// << th->isRunning();
    QString str = QString("masuk updateQueue %1 %2")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),
                 QString::number(QDateTime::currentMSecsSinceEpoch()));
    simpanFile(str);

    int epoch = (int) QDateTime::currentSecsSinceEpoch();
    qDebug() << "updateQueue" << "njobQueue: " << jobQueue.count() << ", Thread: " << threadCount;
//             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz") <<", now:"<< epoch <<  QThread::currentThreadId();
//           "mActiveTag->rowCount()" << mActiveTag->rowCount()

    int j=0;
    stJobQueue tmp;
    foreach (tmp, jobQueue) {
//        if (tmp.tag == rec.value("tag"))    {
        if (jobQueue[j].nextnextJob < QDateTime::currentSecsSinceEpoch()) {
            while (jobQueue[j].nextnextJob < QDateTime::currentSecsSinceEpoch())    {
                jobQueue[j].status = JOB_FREE;
//                qDebug() << "  GANTI JJJJADDDDUULLLLL: " << tmp.tag << (QDateTime::currentSecsSinceEpoch()-tmp.nextJob) << tmp.lastJob << tmp.nextJob << tmp.status;
                jobQueue[j].nextnextJob += jobQueue[j].periode;
//                    this->doCrawling(j, jobQueue[j]);

            }
          sedot(jobQueue[j]);
        }
        j++;
    }
/*
    for (int i=0; i<mActiveTag->rowCount(); i++) {
        QSqlRecord rec = mActiveTag->record(i);
        stJobQueue tmp;
        int j=0;
        foreach (tmp, jobQueue) {
            if (tmp.tag == rec.value("tag"))    {
                while (jobQueue[j].nextnextJob < QDateTime::currentSecsSinceEpoch())    {
                    jobQueue[j].status = JOB_FREE;
                    qDebug() << "  GANTI JJJJADDDDUULLLLL: " << tmp.tag << (QDateTime::currentSecsSinceEpoch()-tmp.nextJob) << tmp.lastJob << tmp.nextJob << tmp.status;
                    jobQueue[j].nextnextJob += jobQueue[j].periode;
//                    this->doCrawling(j, jobQueue[j]);
                    sedot();
                }
            }
            j++;
        }
    }
//*/
}

void MainControllerO::exeQueue()    {
    int epoch = (int) QDateTime::currentSecsSinceEpoch();
//    qDebug() << "exeQueue" << "jobQueue count: " << jobQueue.count()
//             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz") <<", now:"<< epoch <<  QThread::currentThreadId();

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

void MainControllerO::sedot(stJobQueue job) {
    th = new QThread;
    pi = new PiWebApiCrawler(job.tag);

    connect(th, &QThread::started, pi, &PiWebApiCrawler::reqWebApiDataRecorded);
//    connect(pi, SIGNAL(resultReady(QString)), this, SLOT(slotGetResultPiCrawler(QString)));
    connect(pi, SIGNAL(resultReady(QByteArray)), this, SLOT(slotGetResultPiCrawler(QByteArray)));
    connect(pi, SIGNAL(finished()), th, SLOT(quit()));          // mandatory
    connect(pi, SIGNAL(finished()), pi, SLOT(deleteLater()));   // require th::quit. Jika mandiri, optional(?)
    connect(th, SIGNAL(finished()), this, SLOT(slotThFinish()));
    connect(th, SIGNAL(finished()), th, SLOT(deleteLater()));

    pi->moveToThread(th);
    th->start();

    threadCount++;
//    QMetaObject::invokeMethod(pi,"startWorking");
}

void MainControllerO::firstQueueDAQ()   {
    int epoch = (int) QDateTime::currentSecsSinceEpoch();
    qDebug() << "firstQueue" << "mTmmsTagDetail->rowCount()" << jobQueue.count()
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz") <<", now:"<< epoch;

//    mMutex->lock();
//    for (int i=0; i<mTmmsTagDetail->rowCount(); i++)    {
//*
    for (int i=0; i<mActiveTag->rowCount(); i++) {
        QSqlRecord rec = mActiveTag->record(i);
//        QString per = rec.value("periode").toString();
//        if ((per=="00:00:00") || (per=="0") || (per==NULL))   continue;
//        int wkt = (int) (rec.value("periode").toTime().msecsSinceStartOfDay()/1000);
//        wkt = (wkt==0)?86400:wkt;

        stJobQueue tmp;
        bool flag = true;
        int j=0;
        foreach (tmp, jobQueue) {
//                qDebug() << "**** looping jobQueue:" << j << ":" << tmp.tag << tmp.id << rec.value("tag");
            if (tmp.tag == rec.value("tag"))    {
//                qDebug() << "konfig:" << rec.value("tag").toString() << ", periode:"<< wkt
//                         << QDateTime::currentSecsSinceEpoch() << tmp.lastJob << tmp.nextJob << tmp.jobType << tmp.source;

                while (jobQueue[j].nextnextJob < QDateTime::currentSecsSinceEpoch())    {
                    jobQueue[j].status = JOB_FREE;
                    qDebug() << "  GANTI JJJJADDDDUULLLLL: " << tmp.tag << (QDateTime::currentSecsSinceEpoch()-tmp.nextJob) << tmp.lastJob << tmp.nextJob << tmp.status;
//                    jobQueue[j].nextnextJob += wkt;
                    jobQueue[j].nextnextJob += jobQueue[j].periode;
                }
                flag = false;

            }
            j++;
        }

        if (flag)   {
            stJobQueue tmp;
            tmp.id  = rec.value("id").toInt();
            tmp.tag = rec.value("tag").toString();
//            QString start = rec.value("start").toString();
//            qDebug() <<tmp.tag<< ", wkt: "<<wkt << tmp.lastJob << tmp.nextJob;
//            tmp.nextJob = QDateTime::currentSecsSinceEpoch() + wkt;     // jika waktu mulai tidak stated
            tmp.nextJob = utils.awalTime(rec.value("start").toString(), rec.value("periode").toString());
            tmp.nextnextJob = tmp.nextJob;
//            tmp.lastJob = QDateTime::currentSecsSinceEpoch();
            tmp.lastJob = 0;
            tmp.jobType = JOB_DAQ;
            tmp.status  = JOB_WAITING;
            tmp.source  = rec.value("source").toInt();
//            tmp.periode = wkt;
            tmp.periode = utils.getPeriode(rec.value("periode").toString());
            tmp.selalu = true;
            jobQueue.append(tmp);
        }
    }
//*/
//    qDebug() << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl << endl;
//    mMutex->unlock();
}

void MainControllerO::firstQueueFormula()    {
    int epoch = (int) QDateTime::currentSecsSinceEpoch();
    qDebug() << "firstQueueFormula" << mActiveFormula->rowCount()
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz") <<", now:"<< epoch;

    for (int i=0; i<mActiveFormula->rowCount(); i++)    {
        QSqlRecord rec = mActiveFormula->record(i);
//        qDebug() << rec.value("content").toString();
        qDebug() << modelActiveFormula.validateFormulaScript(rec.value("content").toString());
    }

}

int  MainControllerO::doCrawling(int id, stJobQueue job)   {
    jobQueue[id].status = JOB_PENDING;
//            jobQueue[i].nextnextJob = jobQueue[i].lastJob+wkt;
    qDebug() << ">>>>>>>>>>>>>>> doCrawling execute tag:" << job.tag << QDateTime::currentSecsSinceEpoch() << job.nextJob << job.periode;
    jobQueue[id].status = JOB_EXECUTING;

    jobQueue[id].lastJob = jobQueue[id].nextJob;
    jobQueue[id].nextJob = jobQueue[id].lastJob + job.periode;

    jobQueue[id].status = JOB_DONE;
    return JOB_DONE;
}

int  MainControllerO::doCalculating(int id, stJobQueue job)   {
    jobQueue[id].status = JOB_PENDING;
//            jobQueue[i].nextnextJob = jobQueue[i].lastJob+wkt;
    qDebug() << ">>>>>>>>>>>>>>> doCalculating execute tag:" << job.tag << QDateTime::currentSecsSinceEpoch() << job.nextJob;
    jobQueue[id].status = JOB_EXECUTING;
    jobQueue[id].lastJob = jobQueue[id].nextJob;
    jobQueue[id].nextJob = jobQueue[id].lastJob + job.periode;

//    for (int j=0; j<MAX_CRAWLING_LOOP; j++)  {

//    }



    jobQueue[id].status = JOB_DONE;
    return JOB_DONE;
}
