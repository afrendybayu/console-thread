#include "activeformulamodel.h"

ActiveFormulaModel::ActiveFormulaModel()    {

}

int ActiveFormulaModel::getActiveFormula(QSqlQueryModel *model) {
    QString str = "SELECT * "
                  "FROM formula f "
                  "WHERE f.status = 1";

//    qDebug() << "query: " << str;
    model->setQuery(str);
    return model->rowCount();
}