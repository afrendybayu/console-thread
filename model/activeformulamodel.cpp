#include "activeformulamodel.h"
#include <QScriptEngine>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QtSql>
#include <QThread>
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
int ActiveFormulaModel::parsingParamFormula(QJsonObject o, QString &nama, QString &type, QString &value)   {
    QString xtype = o.value("type").toString();
//    QString xnama = o.value("name").toString();
    nama = o.value("name").toString();

//    QString strQ;
    if (xtype == "query")    {
        type  = xtype;
        value = o.value("value").toString();
    }
//    qDebug() << nama << type << strQ;
    return 1;
}
//*/

// , QStringList &hasil
int ActiveFormulaModel::getValueParamFormula(int id, QJsonValue jv, int &waktu, QStringList &index, QStringList &params)  {
    QSqlQueryModel paramModel;
    QString nama, type, value;
    QJsonArray apr;     //, aps;
    QJsonObject opr;    //, ops;
    int ipr=0, ipar=0;  //ips=0,
//    int n=0, m=0;
    int epoch;
    QJsonDocument  json;
    QStringList param;

    QString qry;
    {
        SqlDb sql;
        sql.openConnDB();

        if (waktu == 0)    {
//            epoch = 1530550813;
            paramModel.clear();
            // SELECT '1490' as id, ,
            qry = QString("SELECT '%1' as id, IFNULL((SELECT STRFTIME('%s',DATE(max(f.last_update),'unixepoch'),'utc') FROM formula f WHERE ID=%1)+86400,0) as epoch "
                          "UNION ALL "
                          "SELECT '%1',(STRFTIME('%s',date('now'),'utc')-(SELECT (o.desc*86400) FROM option o WHERE nama like '%formula_day_ago%')) as epoch ").arg(id);

//                          ",DATETIME(IFNULL((SELECT f.last_update FROM formula f WHERE ID=1490),0),'unixepoch') as waktu "
//                          ",DATETIME((STRFTIME('%s',date('now'),'utc')-(SELECT (o.desc*86400) FROM option o WHERE nama like '%formula_day_ago%')),'unixepoch') as waktu "
//                          ",DATETIME(d.epochtime,'unixepoch') as waktu "
//            "UNION ALL "
//            "SELECT id, max(d.epochtime) as epoch FROM data d where ID = '%1'"



            qDebug() <<"query:"<< qry;
            paramModel.setQuery(qry);

            if (!paramModel.rowCount()) return -1;
//            for (int i=0; i<paramModel.rowCount(); i++) {
//                QSqlRecord rec = paramModel.record(i);
//                qDebug() << "Rec:"<< rec.value("epoch").toInt();
//            }
            int formula = paramModel.record(0).value("epoch").toInt();
            int sapuber = paramModel.record(1).value("epoch").toInt();

            if (!formula)   epoch = sapuber;
            else epoch = formula;
            waktu = epoch;
            qDebug() << "#########################";
        }
        else {
            epoch = waktu;
        }

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

            for(int i=0; i<ipr; i++)    {
                if (parsingParamFormula(apr[i].toObject(), nama, type, value))    {
                    if (type=="query")  {
//                        qDebug() << "nama:"<< nama;
                        index.append(QString(":%1").arg(nama));

                        QJsonArray     arr;
                        arr.empty();
                        qry = QString(value).arg(QString::number(epoch), QString::number(epoch+86400-1)); // 1530550813. 1530558855
//                        qry = QString(value).arg("1530550813", "1530558855"); //
                        qDebug() << "qry["<<i<<"]:" << qry;
                        paramModel.clear();
                        paramModel.setQuery(qry);
//                        qDebug() << "jml rec:"<< paramModel.rowCount();
                        for (int j=0; j<paramModel.rowCount(); j++) {
                            QSqlRecord rec = paramModel.record(j);
//                            qDebug() << rec.value("id").toString() << rec.value("min").toFloat() << rec.value("avg").toFloat() << rec.value("max").toFloat();
//                            qDebug() << paramModel.record(j);
                            QJsonObject obj;
//                            qDebug() << rec;
                            for (int k=0; k<5; k++)     {
                                obj.insert(rec.fieldName(k), QJsonValue::fromVariant(rec.value(k)));
                            }
                            arr.insert(j, obj);
//                            qDebug() << obj;
                        }
//                        qDebug()<<"Arr:"<< QString(arr);

                        json.setArray(arr);
//                        qDebug()<<"JSON: "<< QString(json;
                        QString str(json.toJson(QJsonDocument::Compact));

                        str.replace("\"","\'");
//                        qDebug() << "Str:"<< str;
                        param.append(str);
//                        qDebug() << "======================================";
                    }
//*/
                }
            }
//            qDebug() <<"Param:"<< param;
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

    params = param;
    return ipar;
}

int ActiveFormulaModel::exeEngineScript(QStringList tag, QString kode)   {
    qDebug() << "tag:"<< tag;

    QScriptEngine eng;
    QScriptValueList arg;
    QScriptValue val = eng.evaluate(kode);
    QScriptValue res = val.call(QScriptValue(), arg);

    qDebug() << "sampesini 1" << val.isValid() << res.isValid();

    if (eng.hasUncaughtException()) {
        int line = eng.uncaughtExceptionLineNumber();
        qDebug() << "uncaught exception at line" << line;// << ":" << threeAgain.toString();
        return -1;
    }

    int nArray = res.property("length").toInteger();
    qDebug() << "sampesini 2" << nArray << QThread::currentThreadId();
    if (nArray<=0)   {
        return -1;
    }

    qDebug() << "sampesini 3";
    QString q = QString("INSERT INTO data (id, value, epochtime) VALUES ");
    for (int i=0; i<nArray; i++)    {
        if (i>0)   {
            q.append(",");
        }
        double val = res.property(i).property("value").toNumber();
        int epoch = res.property(i).property("epoch").toInteger();
//        qDebug() << val << epoch;
        q.append(QString("('%1'").arg(tag[i]));
        q.append(QString(",'%1'").arg(val));
        q.append(QString(",'%1')").arg(epoch));
    }
    qDebug() << "sampesini 4";
    qDebug() << "sql: " << q;

    {
        SqlDb sql;
        sql.openConnDB();
        QSqlQueryModel model;
        model.setQuery(q);
        sql.closeConnDB();
    }
    QStringList list = QSqlDatabase::connectionNames();
    for(int i = 0; i < list.count(); ++i) {
        QSqlDatabase::removeDatabase(list[i]);
    }


    return nArray;

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

int ActiveFormulaModel::prosesFormulaScript(QString kode, int id)  {
    QString str = QString("{");
    str.append(kode);
    str.append(" }");
    str.replace("\t","");

//    qDebug() << str;

    QJsonDocument JsonDoc = QJsonDocument::fromJson(str.toUtf8());
    QJsonObject o = JsonDoc.object();
    QJsonObject f = o.value("formula").toObject();

//    qDebug() << "---------f-------";
    if (f.isEmpty()) return -1;

    QJsonArray at;
//    QStringList param;
    QStringList index, pre, post, tag;

    if (f.value("tag").isArray())        at = f.value("tag").toArray();
    if (at.count()<=0)  return -1;

    for (int i=0; i<at.count(); i++)    {
//        qDebug() << "at:" << at[i].toInt();
        tag.append(QString::number(at[i].toInt()));
    }

    int waktu = 0;
    getValueParamFormula(id, f.value("pre"), waktu, index, pre);
//    qDebug() <<"Hasil pre:"<< pre;

    QString     c = "(function() { " + f.value("code").toString() + "})";
//    QString     c = f.value("code").toString();
    for (int i=0; i<index.count(); i++)   {
        c.replace(index[i], pre[i]);
    }
    qDebug() << "Hasil kode:"<< c;
    if (exeEngineScript(tag, c))
        getValueParamFormula(id, f.value("post"), waktu, index, post);


    return 1;
}

//int ActiveFormulaModel::exeFormulaScript(stJobQueue job)  {
//    return 0;
//}
