

#ifndef ACTIVEFORMULAMODEL_H
#define ACTIVEFORMULAMODEL_H

#include <QSqlQueryModel>

#include <utils/struct.h>

class ActiveFormulaModel : public QSqlQueryModel
{
public:
    ActiveFormulaModel();
    int getActiveFormula(QSqlQueryModel *model);
    int getCurrentFormula(stJobQueue job, QStringList args);
    int prosesFormulaScript(QString kode, QStringList args);
//    int parsingParamFormula(QJsonObject o, QStringList args);
    int parsingParamFormula(QJsonObject o, QString &type, QString &value);
    QString validateFormulaScript(QString kode);
    int exeFormulaScript(stJobQueue job);
    int getValueParamFormula(QJsonValue jv, QStringList &hasil);
//  QStringList args,  , QStringList index
};

#endif // ACTIVEFORMULAMODEL_H

