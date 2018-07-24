#ifndef SQLDB_H
#define SQLDB_H

#include <QSqlDatabase>
#include <QSqlDriver>

#ifdef   Q_OS_UNIX
#define SQLITE_FILE "picassa.db"
#else   // Q_OS_WINDOWS
//#define SQLITE_FILE "C:/Users/afrendy/Documents/koding/exe/picassa.db"
#define SQLITE_FILE "C:/Program Files (x86)/dbe/exe/picassa.db"
#endif

//#define SQLITE_FILE "./picassa.db"

class SqlDb
{
public:
    SqlDb();
    ~SqlDb();

    void openConnDB();
    void openConnDB(QString koneksi);
    void closeConnDB();
    void simpanLog(QString isi);

private:
    QSqlDatabase sqlite;
    QSqlDatabase mssql;

    bool openConnectionSqlite(const QString& path);
    bool openConnectionSqlite(const QString& path, QString koneksi);
    void closeConnectionSqlite();

    void openConnectionMsSql();

};

#endif // SQLDB_H
