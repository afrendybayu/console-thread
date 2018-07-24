#include "maincontrollero.h"
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QObject>
#include <QtSql>
#include <QStandardPaths>
#include <QScriptEngine>


/*
#ifdef   Q_OS_UNIX
#define LOG_FILE "log.txt"
#else   // Q_OS_WINDOWS
#define LOG_FILE "C:/Users/afrendy/Documents/koding/ext/log.txt"
#endif
//*/

#ifdef  PAKAI_MULTI_THREAD
    #undef PAKAI_SINGLE_THREAD
#endif

/*
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
    int a = p.parsingRecordedDataPiWebApi(1000, ba, data);
    p.simpanRecordedDataWebApi(data);
}

void tesScriptEngine()  {

    QFile file("./hitung2.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString str = "";
    while (!in.atEnd()) {
        str += in.readLine();
    }
    qDebug() << str;

    ActiveFormulaModel f;
    QStringList args;
    int id = 1490;
    ActiveFormulaModel m;

//    f.getCurrentFormula(tag, formula, args);
    f.prosesFormulaScript(m.validateFormulaScript(str), id);
}

void tesExeScript() {
    QString kode;
    QStringList tags;
    tags.append("10880");
    tags.append("13983");
    tags.append("17086");

    kode = "(function() { var data1  = [{'avg':1321.3320338983049,'epochtime':1530601075,'id':1846,'max':1322.8,'min':1320.21},{'avg':1321.017833333333,'epochtime':1530601083,'id':1846,'max':1322.68,'min':1318.95},{'avg':1319.5338333333334,'epochtime':1530601199,'id':1846,'max':1320.88,'min':1318.07},{'avg':1321.7003333333334,'epochtime':1530601227,'id':1846,'max':1323.13,'min':1320.17},{'avg':1320.3296666666672,'epochtime':1530601310,'id':1846,'max':1321.32,'min':1319.18},{'avg':1321.0029999999997,'epochtime':1530601355,'id':1846,'max':1321.89,'min':1319.71},{'avg':1318.6761666666666,'epochtime':1530601380,'id':1846,'max':1321.24,'min':1317.58},{'avg':1320.4157894736845,'epochtime':1530601470,'id':1846,'max':1321.83,'min':1318.53},{'avg':1320.7650847457628,'epochtime':1530601558,'id':1846,'max':1323.22,'min':1319.19},{'avg':1321.9645000000005,'epochtime':1530601570,'id':1846,'max':1324.45,'min':1319.41},{'avg':1320.8638333333336,'epochtime':1530601651,'id':1846,'max':1322.45,'min':1319.43},{'avg':1320.4583333333333,'epochtime':1530601738,'id':1846,'max':1321.25,'min':1319.41},{'avg':1320.5690000000002,'epochtime':1530601780,'id':1846,'max':1321.36,'min':1319.39},{'avg':1320.9735593220341,'epochtime':1530601829,'id':1846,'max':1321.9,'min':1320.22},{'avg':1320.4898333333333,'epochtime':1530601881,'id':1846,'max':1321.84,'min':1318.97},{'avg':1318.924166666667,'epochtime':1530601974,'id':1846,'max':1320.52,'min':1317.1},{'avg':1321.7395348837208,'epochtime':1530602012,'id':1846,'max':1322.3,'min':1320.75}];var data2  = [{'avg':99.33765,'epochtime':1530600253,'id':2170,'max':99.3432,'min':99.3321},{'avg':98.60294999999999,'epochtime':1530600865,'id':2170,'max':98.6085,'min':98.5974},{'avg':98.5918,'epochtime':1530601465,'id':2170,'max':98.5974,'min':98.5862},{'avg':98.56954999999999,'epochtime':1530602062,'id':2170,'max':98.5751,'min':98.564},{'avg':98.61405,'epochtime':1530602668,'id':2170,'max':98.6196,'min':98.6085},{'avg':98.60294999999999,'epochtime':1530603280,'id':2170,'max':98.6085,'min':98.5974},{'avg':98.5584,'epochtime':1530603874,'id':2170,'max':98.564,'min':98.5528},{'avg':98.50275,'epochtime':1530604488,'id':2170,'max':98.5083,'min':98.4972},{'avg':98.58625,'epochtime':1530605087,'id':2170,'max':98.5974,'min':98.5751},{'avg':98.56954999999999,'epochtime':1530605690,'id':2170,'max':98.5751,'min':98.564},{'avg':98.51385,'epochtime':1530606294,'id':2170,'max':98.5194,'min':98.5083},{'avg':98.51385,'epochtime':1530606899,'id':2170,'max':98.5194,'min':98.5083},{'avg':98.6085,'epochtime':1530607499,'id':2170,'max':98.6085,'min':98.6085},{'avg':98.6196,'epochtime':1530607503,'id':2170,'max':98.6196,'min':98.6196},{'avg':98.6307,'epochtime':1530608094,'id':2170,'max':98.6307,'min':98.6307},{'avg':98.6419,'epochtime':1530608103,'id':2170,'max':98.6419,'min':98.6419},{'avg':98.58065,'epochtime':1530608706,'id':2170,'max':98.5862,'min':98.5751},{'avg':98.58065,'epochtime':1530609304,'id':2170,'max':98.5862,'min':98.5751},{'avg':98.5584,'epochtime':1530609910,'id':2170,'max':98.564,'min':98.5528},{'avg':98.4916,'epochtime':1530610518,'id':2170,'max':98.4972,'min':98.486},{'avg':99.44895,'epochtime':1530611120,'id':2170,'max':99.4545,'min':99.4434},{'avg':99.705,'epochtime':1530611722,'id':2170,'max':99.7106,'min':99.6994},{'avg':99.72725,'epochtime':1530612324,'id':2170,'max':99.7328,'min':99.7217},{'avg':99.71615,'epochtime':1530612925,'id':2170,'max':99.7217,'min':99.7106},{'avg':99.68275,'epochtime':1530613529,'id':2170,'max':99.6883,'min':99.6772},{'avg':99.58255,'epochtime':1530614129,'id':2170,'max':99.5881,'min':99.577},{'avg':99.51575,'epochtime':1530614727,'id':2170,'max':99.5213,'min':99.5102},{'avg':99.538,'epochtime':1530615334,'id':2170,'max':99.5436,'min':99.5324},{'avg':99.705,'epochtime':1530615941,'id':2170,'max':99.7106,'min':99.6994},{'avg':99.71615,'epochtime':1530616544,'id':2170,'max':99.7217,'min':99.7106},{'avg':99.6382,'epochtime':1530617146,'id':2170,'max':99.6438,'min':99.6326},{'avg':99.71615,'epochtime':1530617748,'id':2170,'max':99.7217,'min':99.7106},{'avg':99.92765,'epochtime':1530618347,'id':2170,'max':99.9332,'min':99.9221},{'avg':99.74955,'epochtime':1530618946,'id':2170,'max':99.7551,'min':99.744},{'avg':98.56954999999999,'epochtime':1530619550,'id':2170,'max':98.5751,'min':98.564},{'avg':98.40255,'epochtime':1530620152,'id':2170,'max':98.4081,'min':98.397},{'avg':98.44705,'epochtime':1530620753,'id':2170,'max':98.4526,'min':98.4415},{'avg':98.43595,'epochtime':1530621353,'id':2170,'max':98.4415,'min':98.4304},{'avg':98.3914,'epochtime':1530621952,'id':2170,'max':98.397,'min':98.3858},{'avg':98.33575,'epochtime':1530622550,'id':2170,'max':98.3413,'min':98.3302},{'avg':98.3914,'epochtime':1530623155,'id':2170,'max':98.397,'min':98.3858},{'avg':98.3413,'epochtime':1530623754,'id':2170,'max':98.3413,'min':98.3413},{'avg':98.3524,'epochtime':1530623762,'id':2170,'max':98.3524,'min':98.3524},{'avg':98.3858,'epochtime':1530624358,'id':2170,'max':98.3858,'min':98.3858},{'avg':98.397,'epochtime':1530624363,'id':2170,'max':98.397,'min':98.397},{'avg':98.3246,'epochtime':1530624964,'id':2170,'max':98.3302,'min':98.319},{'avg':98.36915,'epochtime':1530625565,'id':2170,'max':98.3747,'min':98.3636},{'avg':98.3858,'epochtime':1530626159,'id':2170,'max':98.3858,'min':98.3858},{'avg':98.397,'epochtime':1530626167,'id':2170,'max':98.397,'min':98.397},{'avg':98.34685,'epochtime':1530626767,'id':2170,'max':98.3524,'min':98.3413},{'avg':98.33575,'epochtime':1530627367,'id':2170,'max':98.3413,'min':98.3302},{'avg':98.3914,'epochtime':1530627974,'id':2170,'max':98.397,'min':98.3858},{'avg':98.358,'epochtime':1530628573,'id':2170,'max':98.3636,'min':98.3524},{'avg':98.29125,'epochtime':1530629176,'id':2170,'max':98.2968,'min':98.2857},{'avg':98.3914,'epochtime':1530629779,'id':2170,'max':98.397,'min':98.3858},{'avg':98.3246,'epochtime':1530630379,'id':2170,'max':98.3302,'min':98.319},{'avg':98.50275,'epochtime':1530630983,'id':2170,'max':98.5083,'min':98.4972},{'avg':98.4248,'epochtime':1530631586,'id':2170,'max':98.4304,'min':98.4192},{'avg':98.43595,'epochtime':1530632183,'id':2170,'max':98.4415,'min':98.4304},{'avg':98.48045,'epochtime':1530632793,'id':2170,'max':98.486,'min':98.4749},{'avg':98.4582,'epochtime':1530633390,'id':2170,'max':98.4638,'min':98.4526},{'avg':98.51385,'epochtime':1530633994,'id':2170,'max':98.5194,'min':98.5083},{'avg':98.525,'epochtime':1530634601,'id':2170,'max':98.5306,'min':98.5194},{'avg':98.50275,'epochtime':1530635203,'id':2170,'max':98.5083,'min':98.4972},{'avg':98.43595,'epochtime':1530635803,'id':2170,'max':98.4415,'min':98.4304},{'avg':97.99065,'epochtime':1530636402,'id':2170,'max':97.9962,'min':97.9851},{'avg':98.525,'epochtime':1530636998,'id':2170,'max':98.5306,'min':98.5194}];var onload = 90;if (!data1) return;if (!data2) return;if (data1.length<=0)return;if (data2.length<=0)return;function mini(d1, d2) {return (d1.min>d2.min)?d2:d1;}function maxi(d1, d2) {return (d1.max>d2.max)?d1:d2;}var i=0, j=0, k=0, min, max, avg, tot=0, urut=0, x=0, y=0;var nD1 = data1.length;var nD2 = data2.length;for (i=0; i<nD1; i++){for (j=k; j<nD2;j++){if (data1[x].epoch==data2[y].epoch) {k = j+1;break;}}if (data2[y].avg<onload){x++; y++;continue;}if (urut==0){min = data1[x];max = data1[x];}else {min = mini(min, data1[x]);max = maxi(max, data1[x]);}urut++;if (data1[x].epoch==data2[y].epoch) {tot+=data1[x].avg;x++;y++;} else if (data1[x].epoch<data2[y].epoch){tot+=data1[x].avg;x++;}else if (data1[x].epoch>data2[y].epoch){tot+=data1[x-1].avg;y++;i--;}}var xmin = { id: min.id, value: min.min, epoch: min.epochtime };var xmax = { id: max.id, value: max.max, epoch: max.epochtime };var xavg = { id: data1[nD1-1].id, value: (tot/urut), epoch: data1[nD1-1].epochtime };var ret = new Array(xmin, xmax, xavg);return ret;})";

    ActiveFormulaModel f;
    f.exeEngineScript(tags, kode, 1846);
}
//*/

MainControllerO::MainControllerO(QObject *parent) : QObject(parent)
{
    QString m = "2018-07-04 00:00:00";
    QDateTime UTC(QDateTime::fromString(m,"yyyy-MM-dd HH:mm:ss"));
    UTC.setTimeSpec(Qt::UTC);
    qDebug() << m << UTC << QDateTime::fromString(m,"yyyy-MM-dd HH:mm:ss").toUTC();
//    tesDataRecorded();
//    tesScriptEngine();
//    tesExeScript();
//    return;


    disabled = false;

    qDebug() << "masuk thread MainControllerO : "<< QThread::currentThreadId();
    init();



#ifdef PAKAI_SINGLE_THREAD
    qDebug() << "Aplikasi pakai single Threads";
    connect(pi, &PiWebApiCrawler::finished, this, &MainControllerO::slotThFinish);
#endif

#ifdef PAKAI_MULTI_THREAD
    qDebug() << "Aplikasi pakai multi Threads";
#endif
}

void MainControllerO::slotGetResultPiCrawlerTh(int thId, int urut, int th, int piId, QByteArray resp)  {
#ifdef PAKAI_MULTI_THREAD
    mutex.lock();
    int x = -1;
    int j = iTh.count();
    qDebug() << "[---------------] MainControllerO::slotGetResultPiCrawler:"<< thId<<"/"<<iTh.count()
             << jobQueue[urut].tag << jobQueue[urut].id << urut << th << piId;  // << resp;
    QString isilist = "";
    QString pidlist = "";

    for (int i=0; i<j; i++) {
        isilist.append(" "); isilist.append(QString::number(iTh[i]));
        pidlist.append(" "); pidlist.append(QString::number(pidTh[i]));
    }
    qDebug() << isilist << "  :  " << pidlist;

    for (int i=0; i<j; i++) {
        if (iTh[i] == thId)   {
            x=i;
//            disconnect(&ppi[piId],0,0,0);
            disconnect(&ppi[thId-1],0,0,0);
            disconnect(&pth[thId-1],0,0,0);
            pth[thId-1].quit();
            pth[thId-1].wait();
            iTh.removeAt(x);
        }
        if (pidTh[i]==jobQueue[urut].id) {
            pidTh.removeAt(i);
        }
    }

    isilist = ""; pidlist = "";
    j = iTh.count();
    for (int i=0; i<j; i++) {
        isilist.append(" "); isilist.append(QString::number(iTh[i]));
        pidlist.append(" "); pidlist.append(QString::number(pidTh[i]));
    }

    qDebug() << "sisa:"<< iTh.count()<<", urut:"<< urut << isilist << pidlist;

    while (jobQueue[urut].nextnextJob < QDateTime::currentSecsSinceEpoch())    {
        jobQueue[urut].status = JOB_FREE;
        jobQueue[urut].nextnextJob += jobQueue[urut].periode;
    }

    mutex.unlock();

#endif

}

//void MainControllerO::slotGetResultPiCrawler(QString resp)  {
void MainControllerO::slotGetResultPiCrawler(QByteArray resp)  {

    qDebug() << "+++ masuk MainControllerO::slotGetResultPiCrawler, parsing Data";  // << resp;
//    PiWebApiCrawler px("");
//    int id, last;
//    QList<stRecordedDataPiWebAPi> data;

//    px.parsingRecordedDataPiWebApi(id, resp, data);
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

#ifdef MULTI_THREAD

#endif

}

void MainControllerO::slotThFinish()    {
    qDebug() << "+++ masuk MainControllerO::slotThFinish";
#ifdef PAKAI_MULTI_THREAD
    qDebug() << "+++ masuk MainControllerO::slotThFinish" << th->currentThreadId() << th->isRunning()
             << "thread: " << threadCount;
    pi->slotDebug();
    th = NULL;
    pi = NULL;

    delete th;
    delete pi;
    threadCount = (threadCount<=0)?0:(threadCount-1);
    qDebug() << "sisa thread: " << threadCount;
#endif

#ifdef PAKAI_SINGLE_THREAD
    ajaxDone = true;
    while (jobQueue[nCurrentJob].nextnextJob < QDateTime::currentSecsSinceEpoch())    {
        jobQueue[nCurrentJob].status = JOB_FREE;
        jobQueue[nCurrentJob].nextnextJob += jobQueue[nCurrentJob].periode;
    }
    qDebug() << "ajaxDone"<< ajaxDone;
#endif
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

    pi = NULL;
    delete pi;

#ifdef PAKAI_MULTI_THREAD
    pth = NULL;
    delete [] pth;
    ppi = NULL;
    delete [] ppi;
#endif
}

void MainControllerO::pause()    {
    disabled = true;
}

void MainControllerO::resume()  {
    disabled = false;
}

void MainControllerO::mappingAccountTmms(QSqlQueryModel* data)  {
    for (int i=0; i<data->rowCount(); i++)   {
        QSqlRecord rec = data->record(i);
        if (rec.value("nama").toString()=="tmms_hostname")   {
            this->tmms_ip = rec.value("desc").toString();
        }
        else if (rec.value("nama").toString()=="tmms_account") {
            this->tmms_account = rec.value("desc").toString();
        }
        else if (rec.value("nama").toString()=="tmms_url") {
            this->tmms_url = rec.value("desc").toString();
        }
        else if (rec.value("nama").toString()=="tmms_password") {
            this->tmms_password = rec.value("desc").toString();
        }
        else if (rec.value("nama").toString()=="tmms_port") {
            this->tmms_port = rec.value("desc").toString();
        }
        else if (rec.value("nama").toString()=="max_daq_request") {
            this->tmms_max_daq_request = rec.value("desc").toString();
        }
    }
}

void MainControllerO::init()    {
    threadCount = 0;
    mTimerQueue = new QTimer();
    mTimerExe = new QTimer();
    ajaxDone = true;
    pi = new PiWebApiCrawler("");

#ifdef PAKAI_MULTI_THREAD
    jmlThread = 3;
    pth = new QThread[jmlThread];
    ppi = new PiWebApiModel[jmlThread];
#endif


    qDebug() << "masuk constructor MainController" << QThread::currentThreadId()
             << ", idealThreadCount: " << QThread::idealThreadCount();

    initData();

    qDebug() << "-----------------" << QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

//    return;

    qDebug("CtrlMainWindows isi mServerConfig: %d", mServerConfig->rowCount());
    qDebug("CtrlMainWindows isi mActiveTagDetail: %d", mActiveTag->rowCount());
    qDebug("CtrlMainWindows isi mActiveForDetail: %d", mActiveFormula->rowCount());

    mappingAccountTmms(mServerConfig);

    this->connect(mTimerQueue, SIGNAL(timeout()), this, SLOT(updateQueue()));
    this->connect(mTimerExe, SIGNAL(timeout()), this, SLOT(exeQueue()));
/*
    for (int i=0; i< mServerConfig->rowCount(); i++)    {
        QSqlRecord rec = mServerConfig->record(i);
        qDebug() << rec.value("nama").toString() << rec.value("desc").toString();
    }

    return;
//*/
/*
//    qDebug() << mActiveFormula->record(0);
    QJsonObject recordObject;
    recordObject.insert(
        mActiveFormula->record(0).fieldName(0),
        QJsonValue::fromVariant(mActiveFormula->record(0).value(0).toString()));
    recordObject.insert(
        mActiveFormula->record(0).fieldName(1),
        QJsonValue::fromVariant(mActiveFormula->record(0).value(1).toString()));
    qDebug() << recordObject;
    return;
//*/

    firstQueueDAQ();
    firstQueueFormula();

    mTimerQueue->start(2000);
}

void MainControllerO::updateQueue()   {
    if (disabled) return;

//    qDebug() << "masuk updateQueue" << QThread::currentThreadId();  //<<"/";// << th->isRunning();
    QString str = QString("masuk updateQueue %1 %2")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),
                 QString::number(QDateTime::currentMSecsSinceEpoch()));
    simpanFile(str);

    int epoch = (int) QDateTime::currentSecsSinceEpoch();

#ifdef PAKAI_SINGLE_THREAD
    qDebug() << "update njob:"<< jobQueue.count()<< QDateTime::currentDateTime().toString("HH:mm:ss.zzz")<<", now:"<< epoch << QThread::currentThreadId()
             << "##############";
#endif

#ifdef PAKAI_MULTI_THREAD
    qDebug() << "update njob:"<< jobQueue.count()<< ", Thread:"<< iTh.count()
             << QDateTime::currentDateTime().toString("HH:mm:ss.zzz")<<", now:"<< epoch << QThread::currentThreadId()
             << "##############" << iTh.count();
#endif


    int j=0;
    stJobQueue tmp;
    foreach (tmp, jobQueue) {
//        if (tmp.tag == rec.value("tag"))    {
//        qDebug() << "j: "<<j<<", updateQueue nextnextJob:"<< jobQueue[j].nextnextJob<<", now:"<< QString::number(QDateTime::currentMSecsSinceEpoch())<<", periode:"<< jobQueue[j].periode;
        if (jobQueue[j].nextnextJob < QDateTime::currentSecsSinceEpoch()) {
//            qDebug() << "next: "<<jobQueue[j].nextnextJob<<", current:"<< QDateTime::currentSecsSinceEpoch();

#ifdef PAKAI_MULTI_THREAD
            if (jobQueue[j].jobType == JOB_DAQ) {
                if (jobQueue[j].status == JOB_FREE) {
                    doCrawling(jobQueue[j], j);
                }
            }
#endif
#ifdef PAKAI_SINGLE_THREAD
            if (jobQueue[j].jobType == JOB_DAQ && ajaxDone) {
//            if (jobQueue[j].jobType == JOB_DAQ) {
                qDebug() << jobQueue[j].tag << ajaxDone;

//                while(!ajaxDone)
//                    QThread::usleep(1000);
                if (ajaxDone)   {
                    sedot(jobQueue[j]);
                    nCurrentJob = j;

                }
                else {
                    qDebug() << "tidak sedot"<< jobQueue[j].id << jobQueue[j].tag;
                }
            }
#endif
            if (jobQueue[j].jobType == JOB_FORMULA) {
                doCalculating(j, jobQueue[j]);
                while (jobQueue[j].nextnextJob < QDateTime::currentSecsSinceEpoch())    {
                    jobQueue[j].status = JOB_FREE;
                    jobQueue[j].nextnextJob += jobQueue[j].periode;
                }
            }
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
//    int epoch = (int) QDateTime::currentSecsSinceEpoch();
//    qDebug() << "exeQueue" << "jobQueue count: " << jobQueue.count()
//             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz") <<", now:"<< epoch <<  QThread::currentThreadId();

}

void MainControllerO::initData() {
    // biar tidak ada warning masalah duplicate connection name
    // QSqlDatabasePrivate::addDatabase: duplicate connection name 'qt_sql_default_connection', old connection removed
    // ------- mulai
    {
        QString liteKoneksi = "koneksiSqlite";
        SqlDb sqlite;
        sqlite.openConnDB();

        mServerConfig = new QSqlQueryModel();
        mActiveTag = new QSqlQueryModel();
        mActiveFormula = new QSqlQueryModel();

        modelServerConfig.initData(mServerConfig, liteKoneksi);
        modelActiveTag.getActiveTag(mActiveTag);
        modelActiveFormula.getActiveFormula(mActiveFormula);

        sqlite.closeConnDB();
    }
    QStringList list = QSqlDatabase::connectionNames();
    for(int i = 0; i < list.count(); ++i) {
        QSqlDatabase::removeDatabase(list[i]);
    }

//    qDebug() << "sebelum cek koneksi ada di initData";

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
#ifdef PAKAI_MULTI_THREAD
    th = new QThread;
    pi = new PiWebApiCrawler(job.tag);

    connect(th, &QThread::started, pi, &PiWebApiCrawler::reqWebApiDataRecorded);
//    connect(pi, SIGNAL(resultReady(QByteArray)), this, SLOT(slotGetResultPiCrawler(QByteArray)));
//    connect(pi, SIGNAL(resultReady(QString)), this, SLOT(slotGetResultPiCrawler(QString)));
    connect(pi, SIGNAL(finished()), th, SLOT(quit()));          // mandatory
    connect(pi, SIGNAL(finished()), pi, SLOT(deleteLater()));   // require th::quit. Jika mandiri, optional(?)
    connect(th, SIGNAL(finished()), this, SLOT(slotThFinish()));
    connect(th, SIGNAL(finished()), th, SLOT(deleteLater()));

    pi->moveToThread(th);
    th->start();

    threadCount++;
//    QMetaObject::invokeMethod(pi,"startWorking");
#endif

#ifdef PAKAI_SINGLE_THREAD
    ajaxDone = false;
    qDebug() << "------- Pakai SINGLE THREAD -------";
    pi->reqWebApiDataRecordedSingle(job);
#endif
}

void MainControllerO::firstQueueDAQ()   {
    int epoch = (int) QDateTime::currentSecsSinceEpoch();
    qDebug() << "firstQueue" << "mTmmsTagDetail->rowCount()" << jobQueue.count()
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz") <<", now:"<< epoch;

//    mMutex->lock();
//    for (int i=0; i<mTmmsTagDetail->rowCount(); i++)    {
//*
    qDebug() << "firstQueue" << mActiveTag->rowCount();
    for (int i=0; i<mActiveTag->rowCount(); i++) {
        QSqlRecord rec = mActiveTag->record(i);
//        QString per = rec.value("periode").toString();
//        if ((per=="00:00:00") || (per=="0") || (per==NULL))   continue;
//        int wkt = (int) (rec.value("periode").toTime().msecsSinceStartOfDay()/1000);
//        wkt = (wkt==0)?86400:wkt;

//        stJobQueue tmp;
//        bool flag = true;
//        int j=0;
        /*
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
        //*/

//        if (flag)   {
//        qDebug() << rec;
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
        tmp.status  = JOB_FREE;
        tmp.source  = rec.value("source").toInt();
        tmp.webId   = rec.value("webid").toString();
//            tmp.periode = wkt;
        tmp.periode = utils.getPeriode(rec.value("periode").toString());
        tmp.selalu = true;

        tmp.account = this->tmms_account;
        tmp.password = this->tmms_password;
        tmp.host = this->tmms_ip;
        tmp.port = this->tmms_port;
        tmp.url  = this->tmms_url;
        tmp.max_daq_request = this->tmms_max_daq_request;
        jobQueue.append(tmp);
//        }
    }
//*/
//    qDebug() << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl << endl;
//    mMutex->unlock();
}

void MainControllerO::firstQueueFormula()    {
    int epoch = (int) QDateTime::currentSecsSinceEpoch();
    qDebug() << "firstQueueFormula" << mActiveFormula->rowCount()
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz") <<", now:"<< epoch;

    stJobQueue tmp;
    QString formula;
    for (int i=0; i<mActiveFormula->rowCount(); i++)    {
        QSqlRecord rec = mActiveFormula->record(i);
//        qDebug() << rec;
//        qDebug() << rec.value("content").toString();
        formula = modelActiveFormula.validateFormulaScript(rec.value("content").toString());
//        qDebug() << formula;
//        qDebug() << "---------------------------------";
        tmp.id = rec.value("id").toInt();
        tmp.tag = rec.value("tag").toString();
        tmp.jobType = JOB_FORMULA;
        tmp.status = JOB_WAITING;
        tmp.selalu = true;
        tmp.kode = formula;
        tmp.nextJob = utils.awalTime(rec.value("start_daq").toString(), rec.value("periode").toString());
        tmp.nextnextJob = tmp.nextJob;
        tmp.periode = utils.getPeriode(rec.value("periode").toString());
        qDebug() << ">>>>>> nextJob firstQUeueForm: " << tmp.nextnextJob;
        jobQueue.append(tmp);
    }
}

void MainControllerO::slotThreadFinished() {
    qDebug() << "****** masuk thFinish";
}

void MainControllerO::slotMasukPi(int th, int pi) {
    qDebug() << "slotMasukPiThread" << th << pi;
//    iTh.append(th);  // masuk methodnya telat !!
//    pidTh.append(job.id);
}

int  MainControllerO::doCrawling(stJobQueue job, int urut)   {
#ifdef PAKAI_MULTI_THREAD
    int i = iTh.count();
    if (i>=(jmlThread))   {
        return -1;
    }

    mutex.lock();
    int k=1;

    if (i==0)    {
        k = 1;
    }
    else {
        bool ke;
        for (int j=1; j<=jmlThread; j++) {
            ke = false;
            for (int l=0; l<i; l++) {   // thread ke-
//                qDebug() << "---- masuk j:"<< j<<", k:"<< k;
                if (iTh[l]==j)  {
                    ke = true;
//                    qDebug() << "j sama:"<< j<<", k:"<< k;
                }
                if (!ke)    k=j;
            }

            if (!ke)    {
                break;
            }
        }
    }

//    k=2;
//    i=1;

    qDebug() <<"th k:"<<k<<", pi:"<< i<<","<< job.tag << iTh.count();
//    connect(&pth[k-1], &QThread::started, &ppi[i], &PiWebApiModel::slotTesting);
//    connect(&ppi[i], &PiWebApiModel::resultReadyTh, this, &MainControllerO::slotGetResultPiCrawlerTh);

    connect(&pth[k-1], &QThread::started, &ppi[k-1], &PiWebApiModel::slotTesting);
    connect(&ppi[k-1], &PiWebApiModel::resultReadyTh, this, &MainControllerO::slotGetResultPiCrawlerTh);


    jobQueue[urut].status = JOB_WAITING;
    job.thId = k;
    ppi[k-1].passingParam(job, urut, k, i); // k,i
    ppi[k-1].moveToThread(&pth[k-1]);

    // https://stackoverflow.com/questions/26692649/how-to-detect-qobjectmovetothread-failure-in-qt5
    if(ppi[k-1].thread() != &pth[k-1])  {
        qDebug() << "======================= @@@@@@@@@ moveToThread failed.";
        jobQueue[urut].status = JOB_FREE;
        disconnect(&ppi[k-1],0,0,0);
        disconnect(&pth[k-1],0,0,0);
        QThread::msleep(2000);
        mutex.unlock();
        return -1;
    }

    pth[k-1].start();
    iTh.append(k);  // yg bikin sesat !!
    iPi.append(i);
    pidTh.append(job.id);
    mutex.unlock();

    QString pidlist;
    for (int i=0; i<pidTh.count(); i++) {
        pidlist.append(" "); pidlist.append(QString::number(pidTh[i]));
    }
    qDebug() << pidlist;

    return 0;
#endif
}

int  MainControllerO::doCrawling(int id, stJobQueue job)   {
    jobQueue[id].status = JOB_PENDING;
//            jobQueue[i].nextnextJob = jobQueue[i].lastJob+wkt;
    qDebug() << "[++++++++++++++] doCrawling execute tag:" << job.tag << QDateTime::currentSecsSinceEpoch() << job.nextJob << job.periode;
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
//    jobQueue[id].nextnextJob =

//    qDebug() << "formula: " << job.kode;

//    for (int j=0; j<MAX_CRAWLING_LOOP; j++)  {
//
//    }

    ActiveFormulaModel f;
    QStringList args;

//    f.getCurrentFormula(tag, formula, args);
    qDebug() << "id:"<< job.id;
    f.prosesFormulaScript(job.kode, job.id);


    jobQueue[id].status = JOB_DONE;
    return JOB_DONE;
}

