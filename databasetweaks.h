#ifndef DATABASETWEAKS_H
#define DATABASETWEAKS_H

#include <QSqlQuery>



class DatabaseTweaks
{
public:
    QVector<QSqlQuery> fetchAll(QSqlQuery *_query);
};

#endif // DATABASETWEAKS_H
