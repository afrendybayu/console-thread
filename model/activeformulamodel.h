

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
    int prosesFormulaScript(QString kode, int id);
//    int parsingParamFormula(QJsonObject o, QStringList args);
    int parsingParamFormula(QJsonObject o, QString &nama, QString &type, QString &value);
    QString validateFormulaScript(QString kode);

//  QStringList args,

private:
    int getValueParamFormula(int id, QJsonValue jv, int &waktu, QStringList &index, QStringList &hasil);
    int exeEngineScript(QStringList tag, QString kode);
//    int exeFormulaScript(stJobQueue job);
};

#endif // ACTIVEFORMULAMODEL_H

