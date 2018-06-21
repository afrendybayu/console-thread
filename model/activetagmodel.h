#ifndef ACTIVETAGMODEL_H
#define ACTIVETAGMODEL_H


#include <QSqlQueryModel>

class ActiveTagModel : public QSqlQueryModel   {
public:
    ActiveTagModel();

    int getActiveTag(QSqlQueryModel *model);
};

#endif // ACTIVETAGMODEL_H
