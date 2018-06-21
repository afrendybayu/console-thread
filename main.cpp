#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include "qtservice.h"
#include "controller/maincontrollero.h"

class DaqService : public QtService<QCoreApplication>  {
public:
    DaqService(int argc, char **argv)
        : QtService<QCoreApplication>(argc, argv, "Qt HTTP Daemon") {
        qDebug() << "konstruktor HttpService";
    }
    ~DaqService()   {
        qDebug("selesai perkara service daemon");
    }

protected:
    void start() {
        qDebug() << "staart protected";
        QCoreApplication *app = application();

        if (daemon->isFinished())   {
            app->quit();
        }
    }

    void stop() {
         qDebug() << "stop daemon protected";
    }

    void pause()    {
        qDebug() << "pause protected";
//        daemon->pause();
    }

    void resume()   {
//        daemon->resume();
    }

private:
    QThread *daemon;
};

int main(int argc, char *argv[])    {
    QCoreApplication a(argc, argv);

    qDebug("masuk main");
    MainControllerO main;

    return a.exec();
}
