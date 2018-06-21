#include "utilsutils.h"

#define DIDEBUG false


UtilsUtils::UtilsUtils()    {

}

int UtilsUtils::awalTime(QString start, QString periode)    {
#if (DIDEBUG==true)
    qDebug() << "+++++ start: "<<start << "periode: "<<periode;
#endif
    QTime ct  = QTime::currentTime();
    QTime st  = QTime::fromString(start, "hh:mm:ss");
    QTime per = QTime::fromString(periode, "hh:mm:ss");

    if (start != "" && !st.isValid()) return -1;       //  && !per.isValid()
    int selang = getPeriode(periode);

    if (periode=="24:00:00") selang = 86400;
    else selang = per.msecsSinceStartOfDay()/1000;

    int epoch = QDateTime::currentSecsSinceEpoch();
    int jedaStart = ct.secsTo(st);

#if (DIDEBUG==true)
    qDebug() << "Jeda now-start:" <<jedaStart << st.isValid() << per.isValid() << selang;
#endif
    int next = 0;
    if (st.isValid())   {
        int jedaHari = QTime::currentTime().msecsSinceStartOfDay()/1000;
#if (DIDEBUG==true)
        qDebug() << "jedaStart: " << jedaStart << "JedaHari: " << QTime::currentTime().msecsSinceStartOfDay()/1000;
#endif
        if (jedaStart < 0)   {       // minus = besok
            int awal = st.secsTo(QTime::fromString("00:00:00"));        // minus
#if (DIDEBUG==true)
            qDebug() << "epoch: "<<epoch<< "jedaHari: "<<jedaHari << "awal: " << awal;
#endif
            next = epoch-jedaHari+86400-awal;
        }
        else {
//            qDebug() << "awal: " << st.msecsSinceStartOfDay()/1000;
            int awal = st.msecsSinceStartOfDay()/1000;
//            qDebug() << "epoch: "<<epoch<< "jedaHari: "<<jedaHari << "awal: " << awal;
            next = epoch-jedaHari+awal;
        }
    }
    else {
        next = (int) QDateTime::currentSecsSinceEpoch() + selang;
    }
#if (DIDEBUG==true)
    qDebug() << "epoch: "<<epoch << "periode: " << periode << "next: " << next;
#endif
    return next;
}


int UtilsUtils::getPeriode(QString time)   {
    int wkt = time.toInt();
    if (wkt>0)  return wkt;
    if (wkt<0)  return -1;
    if (time=="24:00:00")   return 86400;
    QTime periode = QTime::fromString(time, "hh:mm:ss");
    int p = periode.msecsSinceStartOfDay()/1000;

    return (p>0?p:-1);
}
