#include "sourcemodel.h"
#include <QDebug>
#include <QtSql>
#include <QSqlRelationalTableModel>

SourceModel::SourceModel()  {

}

int SourceModel::initData(QSqlRelationalTableModel* model)   {
    qDebug("masuk initData SourceModel QSqlRelationalTableModel");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("source");

    model->setHeaderData(model->fieldIndex("id"), Qt::Horizontal, tr("ID"));
    model->setHeaderData(model->fieldIndex("nama"), Qt::Horizontal, tr("Nama"));
    model->setHeaderData(model->fieldIndex("link"), Qt::Horizontal, tr("Link"));
    model->setHeaderData(model->fieldIndex("arg"), Qt::Horizontal, tr("Arg"));

    if (!model->select()) {
        qDebug() << "error " << model->lastError();
        return -1;
    }

    return model->rowCount();
}
