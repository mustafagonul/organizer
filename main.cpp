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
