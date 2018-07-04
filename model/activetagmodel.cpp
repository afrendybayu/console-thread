#include "activetagmodel.h"
#include <QDebug>

ActiveTagModel::ActiveTagModel()  {

}

int ActiveTagModel::getActiveTag(QSqlQueryModel *model)    {

    QString str = "SELECT t.id, t.tag, t.periode, t.daq_method, t.start_daq as start, t.source, s.link, w.webid "
                  "FROM tag_tmms_detail t "
                  "LEFT JOIN source s ON t.source = s.id "
                  "LEFT JOIN staging_webapi w ON t.tag = w.tag "
                  "WHERE t.status = 1";
    qDebug() << str;

    model->setQuery(str);
    return model->rowCount();
}
