#include "databasetweaks.h"

#include <QSqlQuery>
#include <QSqlQuery>


static QVector<QSqlQuery> fetchAll(QSqlQuery *_query)
    {
        QVector<QSqlQuery> res;
        if(_query->exec())
        {
            while (_query->next())
            {
                res.push_back(*_query);
            }
        }
        return res;
    };
