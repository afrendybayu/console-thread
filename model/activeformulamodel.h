

#ifndef ACTIVEFORMULAMODEL_H
#define ACTIVEFORMULAMODEL_H

#include <QSqlQueryModel>

#include <utils/struct.h>

class ActiveFormulaModel : public QSqlQueryModel
{
public:
    ActiveFormulaModel();
    int getActiveFormula(QSqlQueryModel *model);
    int getCurrentFormula(QString tag, QString kode, QStringList args);
    int prosesFormulaScript(QString kode, QStringList args);
    int parsingParamFormula(QJsonObject o, QStringList args);
    QString validateFormulaScript(QString kode);
    int exeFormulaScript(stJobQueue job);
};

#endif // ACTIVEFORMULAMODEL_H

