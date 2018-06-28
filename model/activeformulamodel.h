

#ifndef ACTIVEFORMULAMODEL_H
#define ACTIVEFORMULAMODEL_H

#include <QSqlQueryModel>

class ActiveFormulaModel : public QSqlQueryModel
{
public:
    ActiveFormulaModel();
    int getActiveFormula(QSqlQueryModel *model);
    int prosesFormulaScript(QString kode, int epochAwal, int epochAkhir);
};

#endif // ACTIVEFORMULAMODEL_H

