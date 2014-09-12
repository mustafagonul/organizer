#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <QSqlQuery>

inline int generateId(const QString &table, const QString &attribute)
{
    QSqlQuery query;
    QString qstr;

    qstr += "SELECT MAX(";
    qstr += attribute;
    qstr += ") FROM ";
    qstr += table;

    query.exec(qstr);
    int id = 0;
    if (query.next())
        id = query.value(0).toInt() + 1;

    return id;
}

#define BEGIN_CASE(x)            switch(x) {
#define ON_CASE(x, func)         case x: func(); break;
#define ON_DEFAULT_CASE(func)    default: func(); break;
#define END_CASE()               }

#define INVALID -1

#endif
