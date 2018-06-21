#ifndef UTILSUTILS_H
#define UTILSUTILS_H


#include <QDateTime>
#include <QTime>
#include <QDebug>

#if defined(Q_OS_WIN32)
#define LOG_FILE    "C:/Users/afrendy/Documents/koding/exe/log.txt"
#else
#define LOGFILE     "log.txt"
#endif

class UtilsUtils    {
public:
    UtilsUtils();
    int awalTime(QString start, QString periode);
    int getPeriode(QString time);
};

#endif // UTILSUTILS_H
