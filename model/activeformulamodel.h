

#ifndef ACTIVEFORMULAMODEL_H
#define ACTIVEFORMULAMODEL_H

#include <QSqlQueryModel>

class ActiveFormulaModel : public QSqlQueryModel
{
public:
    ActiveFormulaModel();
    int getActiveFormula(QSqlQueryModel *model);
};

#endif // ACTIVEFORMULAMODEL_H

