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

#include <QApplication>
#include <QMessageBox>
#include <QLibraryInfo>
#include <QDir>
#include <QFile>
#include <QTextCodec>
#include <QTranslator>
#include <QSqlDatabase>
#include <QSqlError>
#include "mainwindow.h"


static bool createConnection(const char *dbFile, const char *dbDriver)
{

  QSqlDatabase db = QSqlDatabase::addDatabase(dbDriver);
  db.setDatabaseName(dbFile);

  if (db.open() == false) {
    QMessageBox::critical(0, QObject::tr("Cannot open database"),
                             QObject::tr("Unable to establish a database connection.\n"
                                         "Click Cancel to exit."),
                          QMessageBox::Cancel);

    return false;
  }

  return true;
}


int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QString appDirPath = app.applicationDirPath();
  
  // Adding paths for win32
#ifdef WIN32
  QString pluginDirPath = appDirPath  + "/plugins";
  app.removeLibraryPath(QLibraryInfo::location(QLibraryInfo::PluginsPath));
  app.addLibraryPath(pluginDirPath);
#endif

  // Loading translations
  QTranslator translator;
  QString transFilePath = appDirPath + "/translations";
  QString transFile("organizer_tr");
  translator.load(transFile, transFilePath);
  app.installTranslator(&translator);
  
  // Connecting database
  QString dataFilePath = appDirPath + "/data/data.db";
  if (!createConnection(dataFilePath.toLocal8Bit(), "QSQLITE"))
    return 1;
  //else
  //  QMessageBox::information(0, qApp->tr("Baglandi"), qApp->tr("Connected"), QMessageBox::Ok);
  
  // Main window
  MainWindow mainWindow;
  mainWindow.show();

  return app.exec();
}
