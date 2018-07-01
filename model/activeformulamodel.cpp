#include "activeformulamodel.h"
#include <QScriptEngine>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

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

//ActiveFormulaModel::

int getCurrentFormula(QString tag, QString kode, QStringList args)  {

}


int ActiveFormulaModel::parsingParamFormula(QJsonObject o, QStringList args)   {
    QString type = o.value("type").toString();
    QString nama = o.value("name").toString();

    QString strQ;
    if (type == "query")    {
        strQ = o.value("value").toString();
    }
    qDebug() << nama << type << strQ;
}

QString ActiveFormulaModel::validateFormulaScript(QString kode) {
    int n=0, m=0;
    QString resCode = kode;
    QStringList komentar;
//

    int jmlComment = resCode.count(QLatin1String("\/\/"));
//    qDebug() << kode << endl << "jmlComment: " << jmlComment;
    if (jmlComment>0)   {
        for (int i=0; i<jmlComment; i++) {
            n = kode.indexOf(QRegExp("\/\/"), n);
            m = kode.indexOf(QRegExp("\n"), n);
//            qDebug() << "/ ada di" << n << ", \\n di "<< m;
            QString sub = kode.mid(n, (m-n+1));
//            qDebug() << sub;
            komentar.append(sub);
//            resCode.replace(sub,"");
//            qDebug() << resCode;
//            i = n+1;
            n++;
        }
    }
//*
    for (int i=0; i<jmlComment; i++)    {
//        qDebug() << komentar[i];
        resCode.replace(komentar[i],"");
    }

    resCode.replace("\t","");
    resCode.replace("\n","");
//*/
//    qDebug() << resCode;
    return resCode;
}

int ActiveFormulaModel::prosesFormulaScript(QString kode, QStringList args)  {
    QString str = QString("{");
    str.append(kode);
    str.append(" }");
    str.replace("\t","");

//    qDebug() << str;

    QJsonDocument JsonDoc = QJsonDocument::fromJson(str.toUtf8());
    QJsonObject o = JsonDoc.object();
    QJsonObject f = o.value("formula").toObject();
    QJsonArray  t = f.value("tag").toArray();
    QJsonArray  p = f.value("parameter").toArray();

//    QString     c = "var val = function() { " + f.value("code").toString() + "}";

    qDebug() << p;
    for (int i=0; i<p.count(); i++) {
//        qDebug() << p[i].toObject().value("value").toString();
        parsingParamFormula(p[i].toObject(), args);
    }

    QString     c = "(function() { " + f.value("code").toString() + "})";
//*
    QScriptEngine eng;
    QScriptValueList arg;
    QScriptValue val = eng.evaluate(c);
    QScriptValue res = val.call(QScriptValue(), arg);

    if (eng.hasUncaughtException()) {
        int line = eng.uncaughtExceptionLineNumber();
        qDebug() << "uncaught exception at line" << line;// << ":" << threeAgain.toString();
        return -1;
    }

    int nArray = res.property("length").toInteger();
    if (nArray<=0)   {
        return -1;
    }

    QString q = QString("INSERT INTO data (id, value, epoch) VALUES ");
    for (int i=0; i<nArray; i++)    {
        if (i>0)   {
            q.append(",");
        }
        double val = res.property(i).property("value").toNumber();
        int epoch = res.property(i).property("epoch").toInteger();
//        qDebug() << val << epoch;
        q.append(QString("('%1'").arg(t[i].toInt()));
        q.append(QString(",'%1'").arg(val));
        q.append(QString(",'%1')").arg(epoch));
    }
    qDebug() << "sql: " << q;
    return nArray;
//*/

}
