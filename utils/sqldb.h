#ifndef SQLDB_H
#define SQLDB_H

#include <QSqlDatabase>
#include <QSqlDriver>

//#define SQLITE_FILE "./picassa.db"
#define SQLITE_FILE "C:/Users/afrendy/Documents/koding/exe/picassa.db"

class SqlDb
{
public:
    SqlDb();
    ~SqlDb();

    void openConnDB();
    void closeConnDB();
    void simpanLog(QString isi);

private:
    QSqlDatabase sqlite;
    QSqlDatabase mssql;

    bool openConnectionSqlite(const QString& path);
    void closeConnectionSqlite();

    void openConnectionMsSql();

};

#endif // SQLDB_H
