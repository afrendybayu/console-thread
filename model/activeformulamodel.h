

#ifndef ACTIVEFORMULAMODEL_H
#define ACTIVEFORMULAMODEL_H

#include <QSqlQueryModel>

class ActiveFormulaModel : public QSqlQueryModel
{
public:
    ActiveFormulaModel();
    int getActiveFormula(QSqlQueryModel *model);
    int getCurrentFormula(QString tag, QString kode, QStringList args);
    int prosesFormulaScript(QString kode, QStringList args);
    int parsingParamFormula(QJsonObject o, QStringList args);
    QString validateFormulaScript(QString kode);
};

#endif // ACTIVEFORMULAMODEL_H

