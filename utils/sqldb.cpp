#include "sqldb.h"
#include <QDebug>
#include <QSqlQuery>
#include <QDateTime>
#include <QStandardPaths>

SqlDb::SqlDb()  {
    SQLITE_FILE = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/picassa.db";
    qDebug() << "lokasi sql:"<< SQLITE_FILE;
}

void SqlDb::openConnDB(QString koneksi)  {
    openConnectionSqlite(SQLITE_FILE, koneksi);
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

bool SqlDb::openConnectionSqlite(const QString& path, QString koneksi) {
//    sqlite = QSqlDatabase::addDatabase("QSQLITE","qt_sql_default_connection"); // nama koneksi default
    sqlite = QSqlDatabase::addDatabase("QSQLITE", koneksi);  //
//    sqlite = QSqlDatabase::addDatabase("QSQLITE");  //
    sqlite.setDatabaseName(path);
    bool st = false;

//    if (sqlite.open()) {
//        qDebug() << "SqlDb open koneksi sqlite";
//    }

//    sqlite = QSqlDatabase::database("koneksiSqlite");
    if (!sqlite.open()) {
        qDebug() << "KOneksi SQLite gagal !!";
    }
    else {
        qDebug() << "Koneksi SQLite berhasil";
//        logMessage( "koneksi berhasil", 1 );    // QtServiceBase::Error
        st = true;
    }

//    qDebug() << "open ?: " << sqlite.open();
    return st;
}

bool SqlDb::openConnectionSqlite(const QString& path) {
//    sqlite = QSqlDatabase::addDatabase("QSQLITE","qt_sql_default_connection"); // nama koneksi default
    sqlite = QSqlDatabase::addDatabase("QSQLITE");  //
    sqlite.setDatabaseName(path);
    bool st = false;

//    if (sqlite.open()) {
//        qDebug() << "SqlDb open koneksi sqlite";
//    }

//    sqlite = QSqlDatabase::database("koneksiSqlite");
    if (!sqlite.open()) {
        qDebug() << "KOneksi SQLite gagal !!";
    }
    else {
        qDebug() << "Koneksi SQLite berhasil";
//        logMessage( "koneksi berhasil", 1 );    // QtServiceBase::Error
        st = true;
    }

//    qDebug() << "open ?: " << sqlite.open();
    return st;
}

void SqlDb::closeConnectionSqlite() {
//    qDebug() << "Siap tutup KOneksi SQLite";
//    if (sqlite.open()) {            // gagal tidak dikenali
//        qDebug() << "open";
//    }

//    qDebug() << "mau tutup open ?: " << sqlite.open();


    if (sqlite.open()) {
//        QString connection;
//        connection = sqlite.connectionName();
//        qDebug() << "koneksi db:" << connection;
//        QSqlDatabase::removeDatabase("QSQLITE");
        sqlite.close();
//        sqlite.QSqlDatabase();
//        sqlite.removeDatabase("qt_sql_default_connection");
//        sqlite.removeDatabase(connection);
//        QStringList list = QSqlDatabase::connectionNames();
//        for(int i = 0; i < list.count(); ++i) {
//            qDebug() << "koneksi: " << list[i];
//            QSqlDatabase::removeDatabase(list[i]);
//        }

//        qDebug() << "tutup KOneksi SQLite berhasil !!";
    }
}

void SqlDb::closeConnDB() {
    closeConnectionSqlite();
}

SqlDb::~SqlDb()  {
//    qDebug() << "ini fungsi destructive ~SqlDb";
//    QStringList list = QSqlDatabase::connectionNames();
//    for(int i = 0; i < list.count(); ++i) {
//        qDebug() << "koneksi: " << list[i];
//        QSqlDatabase::removeDatabase(list[i]);
//    }
}
