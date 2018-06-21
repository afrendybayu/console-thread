#include "sqldb.h"
#include <QDebug>
#include <QSqlQuery>
#include <QDateTime>


SqlDb::SqlDb()  {

}

void SqlDb::openConnDB()  {
    openConnectionSqlite(SQLITE_FILE);
}

void SqlDb::openConnectionMsSql()   {

}

void SqlDb::simpanLog(QString isi)  {
    if (!isi.length())  return;

    openConnectionSqlite(SQLITE_FILE);
    QSqlQuery q;
    q.prepare("INSERT INTO log (desc,time) "
              "VALUES (:isi, :time)");
    q.bindValue(":isi", isi);
    q.bindValue(":time", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") );

    q.exec();
    closeConnectionSqlite();
}

bool SqlDb::openConnectionSqlite(const QString& path) {
    sqlite = QSqlDatabase::addDatabase("QSQLITE","qt_sql_default_connection"); // nama koneksi default
    sqlite.setDatabaseName(path);
    bool st = false;

    if (sqlite.open()) {
        qDebug() << "open";
    }

    if (!sqlite.open()) {
        qDebug() << "KOneksi SQLite gagal !!";
    }
    else {
        qDebug() << "Koneksi SQLite berhasil";
//        logMessage( "koneksi berhasil", 1 );    // QtServiceBase::Error
        st = true;
    }

    qDebug() << "open ?: " << sqlite.open();
    return st;
}

void SqlDb::closeConnectionSqlite() {
    qDebug() << "KOneksi SQLite";
//    if (sqlite.open()) {            // gagal tidak dikenali
//        qDebug() << "open";
//    }

    qDebug() << "mau tutup open ?: " << sqlite.open();


    if (sqlite.open()) {
        QSqlDatabase::removeDatabase("QSQLITE");
        sqlite.close();
        qDebug() << "tutup KOneksi SQLite berhasil !!";
    }
}

void SqlDb::closeConnDB() {
    closeConnectionSqlite();
}

SqlDb::~SqlDb()  {
    qDebug() << "ini fungsi destructive ~SqlDb";
}
