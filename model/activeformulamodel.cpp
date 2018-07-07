#include "activeformulamodel.h"
#include <QScriptEngine>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QtSql>
#include <utils/sqldb.h>

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

int getCurrentFormula(stJobQueue job, QStringList args)  {
    int id = job.id;
    QString x = args[0]+id;
    return -1;
}

//*
int ActiveFormulaModel::parsingParamFormula(QJsonObject o, QString &type, QString &value)   {
    QString xtype = o.value("type").toString();
    QString xnama = o.value("name").toString();

    QString strQ;
    if (xtype == "query")    {
        type  = xtype;
        value = o.value("value").toString();
    }
//    qDebug() << nama << type << strQ;
    return 1;
}
//*/

// , QStringList &hasil
int ActiveFormulaModel::getValueParamFormula(QJsonValue jv)  {
    QSqlQueryModel paramModel;
    QString type, value;
    QJsonArray apr, aps;
    QJsonObject opr, ops;
    int ipr=0, ips=0, ipar=0;
    int n=0, m=0;
    QString qry;
    {
        SqlDb sql;
        sql.openConnDB();

        if(jv.isArray()) {
            apr = jv.toArray();
            ipr = apr.count();
            /*
            ipar = okode.count(QLatin1String(":p"));
            qDebug() << ipar;

            if (ipar>0)   {
                for (int i=0; i<ipar; i++) {
                    n = str.indexOf(QRegExp(":p"), n);
                    m = str.indexOf(QRegExp("[;, +-*%/]"), n);
        //            qDebug() << "/ ada di" << n << ", \\n di "<< m;
                    QString sub = str.mid(n, (m-n));
                    qDebug()<<"Sub:"<< sub;
                    param.append(sub);
                    n++;
                }
            }
    //*/
//            qDebug() << "sampe sini" << ipr << apr[0].toObject();
//            pm = new QSqlQueryModel[ipr];
            for(int i=0; i<ipr; i++)    {
                if (parsingParamFormula(apr[i].toObject(), type, value))    {
                    if (type=="query")  {
                        qry = QString(value).arg("1530550813","1530558855");
        //*
                        paramModel.setQuery(qry);
                        qDebug() << "jml rec:"<< paramModel.rowCount();
    //*
                        for (int j=0; j<paramModel.rowCount(); j++) {
                            QSqlRecord rec = paramModel.record(j);
                            qDebug() << rec.value("id") << rec.value("min") << rec.value("avg") << rec.value("max");
//                            qDebug() << paramModel.record(j);
                        }
                    }
//*/
                }
            }
            qDebug() << "-----";
            for(int i=0; i<ipar; i++)   {

            }
        }
        else {
            opr = jv.toObject();
        }
        sql.closeConnDB();
    }
    QStringList list = QSqlDatabase::connectionNames();
    for(int i = 0; i < list.count(); ++i) {
        QSqlDatabase::removeDatabase(list[i]);
    }
//    delete[] pm;

    return ipar;
}


QString ActiveFormulaModel::validateFormulaScript(QString kode) {
    int n=0, m=0;
    QString resCode = kode;
    QStringList komentar;
//
    int jmlComment = resCode.count(QLatin1String("//"));
//    qDebug() << kode << endl << "jmlComment: " << jmlComment;
    if (jmlComment>0)   {
        for (int i=0; i<jmlComment; i++) {
            n = kode.indexOf(QRegExp("//"), n);
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

    qDebug() << "---------f-------";
    if (f.isEmpty()) return -1;
//    qDebug() << ;
//    QJsonArray at = {};
    QJsonArray at, apr, aps;
    QJsonObject opr, ops;
    QString okode = f.value("code").toString();
    int ipr=0, ips=0, ipar=0;
    int n=0, m=0;
    int index=0;
    QStringList param;
    QStringList pre, post;

    if (f.value("tag").isArray())        at = f.value("tag").toArray();

    getValueParamFormula(f.value("pre"));
//    getValueParamFormula(okode, f.value("post"), param, index, post);

    return 1;
    QSqlQueryModel *pm;

    {
        qDebug() << f.value("pre");
        if(f.value("pre").isArray()) {
            apr = f.value("pre").toArray();
            ipr = apr.count();
            ipar = okode.count(QLatin1String(":p"));
            qDebug() << ipar;

            if (ipar>0)   {
                for (int i=0; i<ipar; i++) {
                    n = str.indexOf(QRegExp(":p"), n);
                    m = str.indexOf(QRegExp("[;, +-/*%]"), n);
        //            qDebug() << "/ ada di" << n << ", \\n di "<< m;
                    QString sub = str.mid(n, (m-n));
                    qDebug()<<"Sub:"<< sub;
                    param.append(sub);
                    n++;
                }
            }

            pm = new QSqlQueryModel[ipr];
            for(int i=0; i<ipr; i++)    {
//                QSqlQuery q;
//                parsingParamFormula(apr[i].toObject(), args);

            }
            qDebug() << "-----";
            for(int i=0; i<ipar; i++)   {

            }
        }
        else
            opr = f.value("pre").toObject();
    }


    delete[] pm;


//    QJsonArray ps = (f.value("post").isArray())?f.value("post").toArray():f.value("post").toObject();

    qDebug() << "tag    " << at;
    qDebug() << "f.value(pre).isArray()" << f.value("pre").isArray();
    qDebug() << "f.value(post).isArray()" << f.value("post").isArray();
/*
    QJsonArray apr  = f.value("pre").isArray(); //?f.value("pre").toArray():NULL;
    QJsonObject opr = (!apr.count())?f.value("pre").toObject():NULL;
    QJsonArray aps  = f.value("post").isArray();//?f.value("post").toArray():NULL;
    QJsonObject ops = (!aps.count())?f.value("post").toObject():NULL;
//    qDebug() << f.value("post").isArray() << f.value("post").toObject() << ps;
    return;

//    QString     c = "var val = function() { " + f.value("code").toString() + "}";

//    qDebug() << f;
//    qDebug() << t;
//    qDebug() << pr;
//    qDebug() << ps;
    if (apr.count())    {
        for (int i=0; i<apr.count(); i++) {
    //        qDebug() << p[i].toObject().value("value").toString();
            parsingParamFormula(apr[i].toObject(), args);
        }
    }
    else {
        parsingParamFormula(opr, args);
    }

//    for (int i=0; i<ps.count(); i++) {
////        qDebug() << p[i].toObject().value("value").toString();
//        parsingParamFormula(ps[i].toObject(), args);
//    }

    QString     c = "(function() { " + f.value("code").toString() + "})";
//*/
/*
//    return -1;

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
        q.append(QString("('%1'").arg(at[i].toInt()));
        q.append(QString(",'%1'").arg(val));
        q.append(QString(",'%1')").arg(epoch));
    }
    qDebug() << "sql: " << q;
    return nArray;
//*/
    return 0;
}

int ActiveFormulaModel::exeFormulaScript(stJobQueue job)  {
    return 0;
}
