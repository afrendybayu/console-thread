#include "serverconfigmodel.h"

#include <QDebug>

//#include <QDialog>
//#include <QtWidgets>
#include <QtSql>

//extern ServerConfigModel modelServerConfig;

ServerConfigModel::ServerConfigModel()  {
    qDebug("masuk constructor ServerConfigModel");

}

/*
void ServerConfigModel::init()  {
    qDebug("masuk init ServerConfigModel");
    //initData();
}
//*/

int ServerConfigModel::initData(QSqlRelationalTableModel* model)  {
    qDebug("masuk initData pointer ServerConfigModel QSqlRelationalTableModel");
    //model = new QSqlRelationalTableModel();

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("option");

    if (!model->select()) {
        //showError(modelTmmsTag->lastError());
        qDebug() << "error " << model->lastError();
        return -1;
    }

    //int n = model->rowCount();
    //qDebug("Jml row: %d", n);
    return model->rowCount();
}

/*
void ServerConfigModel::initData(int a)  {
    qDebug("masuk initData ServerConfigModel %d", a);

}
//*/


/*
void ServerConfigModel::showError(const QSqlError &err)    {
    QMessageBox::critical(this, "Unable to initialize Database",
                "Error initializing database: " + err.text());
}
//*/

/*
int ServerConfigModel::rowCount(const QModelIndex &parent) const    {
    Q_UNUSED(parent);
    return serverCfg.size();
}

int ServerConfigModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 2;
}

QVariant ServerConfigModel::data(const QModelIndex &index, int role) const  {
    if (!index.isValid())
        return QVariant();

    if (index.row() >= serverCfg.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &cfg = serverCfg.at(index.row());

        if (index.column() == 0)
            return cfg.name;
        else if (index.column() == 1)
            return cfg.value;
    }
    return QVariant();
}

QVariant ServerConfigModel::headerData(int section, Qt::Orientation orientation, int role) const    {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Name");

            case 1:
                return tr("Value");

            default:
                return QVariant();
        }
    }
    return QVariant();
}

bool ServerConfigModel::insertRows(int position, int rows, const QModelIndex &index)   {
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        serverCfg.insert(position, { QString(), QString() });

    endInsertRows();
    return true;
}

bool ServerConfigModel::removeRows(int position, int rows, const QModelIndex &index)   {
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        serverCfg.removeAt(position);

    endRemoveRows();
    return true;
}

bool ServerConfigModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        auto contact = serverCfg.value(row);

        if (index.column() == 0)
            serverCfg.name = value.toString();
        else if (index.column() == 1)
            serverCfg.value = value.toString();
        else
            return false;

        serverCfg.replace(row, contact);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}

Qt::ItemFlags ServerConfigModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QList<stServerConfig> ServerConfigModel::getServerConfigs() const
{
    return serverCfg;
}
//*/


void ServerConfigModel::setupHeader(void)    {
    //modelServerConfig.setEditStrategy(QSqlTableModel::OnManualSubmit);
    //modelServerConfig.setTable("option");

//    modelServerConfig.setHeaderData(modelServerConfig.fieldIndex("name"))
}
