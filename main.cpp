#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include "qtservice.h"
#include "controller/maincontrollero.h"

#define PAKAI_OBJEK
//#define PAKAI_THREAD_LANGSUNG
//#define PAKAI_SERVICE


class DaqService : public QtService<QCoreApplication>  {
public:
    DaqService(int argc, char **argv)
        : QtService<QCoreApplication>(argc, argv, "DaqMITS Daemon") {
        qDebug() << "konstruktor Service";
    }
    ~DaqService()   {
        daemon.quit();      //
        daemon.wait();
        qDebug("selesai perkara service daemon");
    }

protected:
    void start() {
        qDebug() << "start protected";
        QCoreApplication *app = application();

        main = new MainControllerO;
        main->moveToThread(&daemon);
        QObject::connect(&daemon, &QThread::finished, main, &QObject::deleteLater);

        daemon.start();


        if (daemon.isFinished())   {
            app->quit();
        }
    }

    void stop() {

        main = NULL;
        delete main;
         qDebug() << "stop daemon protected";
    }

    void pause()    {
        qDebug() << "pause protected";
        main->pause();
//        daemon->pause();
    }

    void resume()   {
        main->resume();
//        daemon->resume();
    }

private:
    QThread daemon;
    MainControllerO *main;
};

int main(int argc, char *argv[])    {
    QCoreApplication::setOrganizationName("DaunBiru");
    QCoreApplication::setOrganizationDomain("daunbiru.com");
    QCoreApplication::setApplicationName("daqscadamits");

    qDebug()<<"From main thread: "<<QThread::currentThreadId();

#ifdef PAKAI_OBJEK
    QCoreApplication a(argc, argv);
    qDebug()<<" --- PAKAI_THREAD_LANGSUNG --- ";

    MainControllerO main;
    return a.exec();
#endif

#ifdef PAKAI_THREAD_LANGSUNG        // sesat !!!
    QCoreApplication a(argc, argv);
    qDebug()<<" --- PAKAI_THREAD_LANGSUNG --- ";
    QThread t;
    MainControllerO *main = new MainControllerO;
    main->moveToThread(&t);

    QObject::connect(&t, SIGNAL(finished()), &a, SLOT(deleteLater()));
    t.start();

    return a.exec();
#endif

#ifdef PAKAI_SERVICE
    DaqService service(argc, argv);
    qDebug()<<" --- PAKAI_SERVICE --- ";

    return service.exec();
#endif

}
