/*
 * Copyright (C) 2014 Mustafa Gönül
 *
 * Organizer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Organizer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
**/

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
