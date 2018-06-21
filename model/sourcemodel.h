#ifndef SOURCEMODEL_H
#define SOURCEMODEL_H

#include <QSqlRelationalTableModel>

class SourceModel : public QSqlRelationalTableModel {
public:
    SourceModel();
    int initData(QSqlRelationalTableModel* model);
};

#endif // SOURCEMODEL_H
