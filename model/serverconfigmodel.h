#ifndef SERVERCONFIGMODEL_H
#define SERVERCONFIGMODEL_H

#include <QSqlRelationalTableModel>
//#include <QMessageBox>

class ServerConfigModel : public QSqlRelationalTableModel   {
//    Q_OBJECT
public:
    ServerConfigModel();
    int initData(QSqlRelationalTableModel* model);
//    void initData(int a);
//    void init();

/*
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    QList<stServerConfig> getServerConfigs() const;
//*/

private:
//    QList<stServerConfig> serverCfg;
//    void setupHeader();
    void setupHeader();
    void showError(const QSqlError &err);

};

#endif // SERVERCONFIGMODEL_H
