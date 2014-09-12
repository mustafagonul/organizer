#include <mainwindow.h>
#include <goodsdialog.h>
#include <purchaserdialog.h>
#include <utility.h>

#include <QApplication>
#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlRelationalDelegate>
#include <QListView>
#include <QMessageBox>


#define PURCHASERS 0
#define GOODS      1
#define ORDERS     2

#define PREPARE_OPERATION(widget, button, operation)    { \
               widget->setWindowTitle(tr(#operation));    \
               widget->button->setText(tr(#operation)); }

#define PREPARE_SHOW(widget, button) widget->setWindowTitle(QApplication::tr("Show")); \
               widget->button->setText(QApplication::tr("Goods"));
#define PREPARE_ADD(widget, button) PREPARE_OPERATION(widget, button, Add)
#define PREPARE_FIND(widget, button) PREPARE_OPERATION(widget, button, Find)
#define PREPARE_EDIT(widget, button) PREPARE_OPERATION(widget, button, Edit)

#define CREATE_WIDGET(ptrName, classType, parent) classType *ptrName = new classType(parent);
#define CREATE_PURCHASER(ptrName, parent) CREATE_WIDGET(ptrName, PurchaserDialog, parent)
#define CREATE_GOODS(ptrName, parent) CREATE_WIDGET(ptrName, GoodsDialog, parent)

/*
void PrepareComboBox(QComboBox *comboBox, QSqlTableModel *model, int row, int disCol)
{
  comboBox->setModel(model);
  comboBox->setModelColumn(disCol);
  comboBox->setCurrentIndex(row);
}
*/

// Bu islev key yerine record alacak ve secilebilir olup olmayacagini alacak
// Bu islevin benzerlerini text alanlari icinde yap
void PrepareComboBox(QComboBox *comboBox, QSqlTableModel *model, int keyCol, int disCol, int key)
{
  /*PrepareComboBox(comboBox, model, 0, disCol);
  
  for (int i = 0; i < model->rowCount(); ++i)
    if (model->record(i).field(keyCol).value().toInt() == key) {
      comboBox->setCurrentIndex(i);
      return;
    }*/
  for (int i = 0; i < model->rowCount(); ++i) {
    QSqlRecord record = model->record(i);
    QString string = record.field(disCol).value().toString();
    int k = record.field(keyCol).value().toInt();
    comboBox->addItem(string, k);
    if (k == key)
      comboBox->setCurrentIndex(i);
  }

}

void PrepareComboBox(QComboBox *comboBox, QSqlTableModel *model, int keyCol, int disCol, bool withAll = false)
{
  for (int i = 0; i < model->rowCount(); ++i) {
    QSqlRecord record = model->record(i);
    QString string = record.field(disCol).value().toString();
    int k = record.field(keyCol).value().toInt();
    comboBox->addItem(string, k);
  }
  if (withAll) {
    comboBox->addItem(QApplication::tr("All"), INT_MAX);
    comboBox->setCurrentIndex(comboBox->count() - 1);
  }
  else
    comboBox->setCurrentIndex(0);
}

int ComboBoxKeyValue(QComboBox *comboBox)
{
  /*QSqlTableModel *model = (QSqlTableModel *)comboBox->model();
  int row = comboBox->currentIndex();

  return  model->record(row).field(keyCol).value().toInt();*/

  return comboBox->itemData(comboBox->currentIndex()).toInt();
}

MainWindow::MainWindow(QWidget *parent)
  :QMainWindow(parent)
{
  setupUi(this);
  createConnections();
  createTables();
  hideAttributes();
  
  //eksiklerin kapanmasi
  //findButton->setEnabled(false);
}

void MainWindow::createConnections()
{
  connect(showButton, SIGNAL(clicked()), this, SLOT(onShow()));
  connect(showAllButton, SIGNAL(clicked()), this, SLOT(onShowAll()));
  connect(addButton, SIGNAL(clicked()), this, SLOT(onAdd()));
  connect(deleteButton, SIGNAL(clicked()), this, SLOT(onDelete()));
  connect(findButton, SIGNAL(clicked()), this, SLOT(onFind()));
  connect(editButton, SIGNAL(clicked()), this, SLOT(onEdit()));
  connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
  connect(goodsButton, SIGNAL(clicked()), this, SLOT(onGoods()));
}

void MainWindow::createTables()
{
  purchaserModel = new QSqlRelationalTableModel(this);
  goodsModel = new QSqlRelationalTableModel(this);
  
  goodsModel->setTable("GOODS");
  purchaserModel->setTable("PURCHASER");
    
  /*
  purchaserModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
  goodsModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
  citiesModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
  */

  /*QSqlRecord record = citiesModel->record();
  purchaserModel->setRelation(2, QSqlRelation(citiesModel->tableName(), record.fieldName(0), record.fieldName(1)));
  record = ordersModel->record();
  ordersModel->setRelation(1, QSqlRelation(purchaserModel->tableName(), record.fieldName(0), record.fieldName(1)));
  ordersModel->setRelation(2, QSqlRelation(citiesModel->tableName(), record.fieldName(0), record.fieldName(1)));*/
    

  tableView->setModel(purchaserModel);
  tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
  purchaserModel->setHeaderData(1, Qt::Horizontal, tr("Company Name"));
  purchaserModel->setHeaderData(2, Qt::Horizontal, tr("City"));
  purchaserModel->setHeaderData(3, Qt::Horizontal, tr("Name"));
  purchaserModel->setHeaderData(4, Qt::Horizontal, tr("Tel"));
  purchaserModel->setHeaderData(5, Qt::Horizontal, tr("Mobil"));
  purchaserModel->setHeaderData(6, Qt::Horizontal, tr("Address"));
  purchaserModel->setHeaderData(7, Qt::Horizontal, tr("E-Mail"));
  purchaserModel->setHeaderData(8, Qt::Horizontal, tr("Taxation No"));
  
  onShowAll();
}

void MainWindow::hideAttributes()
{
	tableView->setColumnHidden(0, true);
//	tableView->setColumnHidden(2, true);
//	tableView->setColumnHidden(4, true);
//	tableView->setColumnHidden(5, true);
//	tableView->setColumnHidden(6, true);
//	tableView->setColumnHidden(7, true);
//	tableView->setColumnHidden(8, true);
//	tableView->setColumnHidden(9, true);
	tableView->resizeColumnsToContents();
	tableView->resizeRowsToContents();  
}


void MainWindow::setAttributes()
{
	
}

int MainWindow::getTableRow()const
{
  if (tableView->currentIndex().isValid())
	  return tableView->currentIndex().row();
  else
	  return INVALID;
}

void MainWindow::onShow()
{ 
	if (getTableRow() == INVALID)
	{
		QMessageBox::information(this, QApplication::tr("Show"), QApplication::tr("You must select a row"), QMessageBox::Ok);
		return;
	}

	CREATE_PURCHASER(w, this)
	PREPARE_SHOW(w, actionButton)
	connect(w->actionButton, SIGNAL(clicked()), this, SLOT(onGoods()));
	purchaserDialog = w;
	fillPurchaser();
	//purchaserDialog->cityComboBox->setEnabled(false);
	
	w->exec();
}

void MainWindow::onShowAll()
{/*
  while (ordersModel->canFetchMore())
    ordersModel->fetchMore();
  while (purchaserModel->canFetchMore())
    purchaserModel->fetchMore();
  while (goodsModel->canFetchMore())
    goodsModel->fetchMore();*/
  
  
  purchaserModel->setFilter("");  
  purchaserModel->select();
  goodsModel->setFilter("");  
  goodsModel->select();
    
  hideAttributes();
}

void MainWindow::onAdd()
{
	CREATE_PURCHASER(w, this)
	PREPARE_ADD(w, actionButton)
	purchaserDialog = w;
	connect(w->actionButton, SIGNAL(clicked()), this, SLOT(addPurchaser()));
	connect(w->actionButton, SIGNAL(clicked()), w, SLOT(close()));
	w->exec();
}

void MainWindow::onDelete()
{
	int row = getTableRow();
	
	if (row == INVALID)
	{
		QMessageBox::information(this, QApplication::tr("Delete"), QApplication::tr("You must select a row"), QMessageBox::Ok);
		return;
	}
	  
	
	if (QMessageBox::warning(this, QApplication::tr("Delete"), 
			QApplication::tr("Are you sure to\ndelete this record?"), 
			QMessageBox::Ok | QMessageBox::Cancel)
			== QMessageBox::Cancel)
		return;
	
  	QSqlRecord purchaserRecord = purchaserModel->record(row);
  	int id = purchaserRecord.field(0).value().toInt();
  	deleteGoods(id);
	
  	deletePurchaser(row);
	  
	hideAttributes(); 
}

void MainWindow::onFind()
{
	CREATE_PURCHASER(w, this)
	PREPARE_FIND(w, actionButton)
	purchaserDialog = w;
	connect(w->actionButton, SIGNAL(clicked()), this, SLOT(findPurchaser()));
	connect(w->actionButton, SIGNAL(clicked()), w, SLOT(close()));
	w->exec();
}

void MainWindow::onEdit()
{
	if (getTableRow() == INVALID)
	{
		QMessageBox::information(this, QApplication::tr("Edit"), QApplication::tr("You must select a row"), QMessageBox::Ok);
		return;
	}
	  
	CREATE_PURCHASER(w, this)
	PREPARE_EDIT(w, actionButton)
	purchaserDialog = w;
	connect(w->actionButton, SIGNAL(clicked()), this, SLOT(editPurchaser()));
	connect(w->actionButton, SIGNAL(clicked()), w, SLOT(close()));
	fillPurchaser();
	w->exec();
}

void MainWindow::onGoods()
{
	if (getTableRow() == INVALID)
	{
		QMessageBox::information(this, QApplication::tr("Edit"), QApplication::tr("You must select a row"), QMessageBox::Ok);
		return;
	}
	
	CREATE_GOODS(w, this)
	PREPARE_EDIT(w, actionButton)
	goodsDialog = w;
	connect(w->actionButton, SIGNAL(clicked()), this, SLOT(editGoods()));
	connect(w->actionButton, SIGNAL(clicked()), w, SLOT(close()));
	fillGoods();
	w->exec();
}

void MainWindow::addPurchaser(int id)
{
	int row = purchaserModel->rowCount();
	bool isNew = false;
	  
	QSqlRecord record = purchaserModel->record();
	if (id == INVALID)
	{
	  id = generateId(purchaserModel->tableName(), record.fieldName(0));
	  isNew = true;
	}
	
	record.setValue(0, id);
	  
	record.setValue(1, purchaserDialog->companyEdit->text());
	record.setValue(2, purchaserDialog->cityEdit->text());
	record.setValue(3, purchaserDialog->nameEdit->text());
	record.setValue(4, purchaserDialog->telEdit->text());
	record.setValue(5, purchaserDialog->mobilEdit->text());
	record.setValue(6, purchaserDialog->addressEdit->toPlainText());
	record.setValue(7, purchaserDialog->emailEdit->text());
	record.setValue(8, purchaserDialog->taxnoEdit->text());
	  
	purchaserModel->insertRecord(row, record);
	
	if (isNew)
		addGoods(id);
	  
	hideAttributes();
}

void MainWindow::deletePurchaser(int row)
{
	if (purchaserModel->rowCount() > 0) {
	  purchaserModel->removeRows(row, 1);
	  purchaserModel->submitAll();
	}	
}

void MainWindow::findPurchaser()
{
	QString attributeName;
	QString filterStr;
	QString str;
	bool isFirst = true;
	  
	attributeName = purchaserModel->record().field(1).name();
	str = purchaserDialog->companyEdit->text();
	if (!str.isEmpty()) {
	  filterStr += attributeName + " LIKE '%" + str + "%'";
	  isFirst = false;
	}
	  	
	attributeName = purchaserModel->record().field(2).name();
	str = purchaserDialog->cityEdit->text();
	if (!str.isEmpty()) {
	  if (!isFirst)
	    filterStr += " AND ";
	  filterStr += attributeName + " LIKE '%" + str + "%'";
	  isFirst = false;
	}
	  
	attributeName = purchaserModel->record().field(3).name();
	str = purchaserDialog->nameEdit->text();
	if (!str.isEmpty()) {
	  if (!isFirst)
	    filterStr += " AND ";
	  filterStr += attributeName + " LIKE '%" + str + "%'";
	  isFirst = false;
	}
	
	attributeName = purchaserModel->record().field(4).name();
	str = purchaserDialog->telEdit->text();
	if (!str.isEmpty()) {
		if (!isFirst)
			filterStr += " AND ";
		filterStr += attributeName + " LIKE '%" + str + "%'";
		isFirst = false;
	}
	    
	attributeName = purchaserModel->record().field(5).name();
	str = purchaserDialog->mobilEdit->text();
	if (!str.isEmpty()) {
	    if (!isFirst)
	    	filterStr += " AND ";
	    filterStr += attributeName + " LIKE '%" + str + "%'";
	    isFirst = false;
	}
	  
	attributeName = purchaserModel->record().field(6).name();
	str = purchaserDialog->addressEdit->toPlainText();
	if (!str.isEmpty()) {
	  if (!isFirst)
	    filterStr += " AND ";
	  filterStr += attributeName + " LIKE '%" + str + "%'";
	  isFirst = false;
	}
		  
	attributeName = purchaserModel->record().field(7).name();
	str = purchaserDialog->emailEdit->text();
	if (!str.isEmpty()) {
	  if (!isFirst)
	    filterStr += " AND ";
	  filterStr += attributeName + " LIKE '%" + str + "%'";
	  isFirst = false;
	}
	  
	attributeName = purchaserModel->record().field(8).name();
	str = purchaserDialog->taxnoEdit->text();
	if (!str.isEmpty()) {
	  if (!isFirst)
	    filterStr += " AND ";
	  filterStr += attributeName + " LIKE '%" + str + "%'";
	  isFirst = false;
	}
  
	  
	purchaserModel->setFilter(filterStr);
	purchaserModel->select();
	
	hideAttributes();  
}

void MainWindow::editPurchaser()
{
	int row = getTableRow();
	QSqlRecord record = purchaserModel->record(row);
	int id = record.field(0).value().toInt();
	deletePurchaser(row);
	addPurchaser(id);
		  
		  
	  /*
	  record.setValue(1, purchaserDialog->companyLineEdit->text());
	  record.setValue(2, ComboBoxKeyValue(purchaserDialog->cityComboBox));
	  record.setValue(3, purchaserDialog->nameLineEdit->text());
	  record.setValue(4, purchaserDialog->surnameLineEdit->text());
	  record.setValue(5, purchaserDialog->tel1LineEdit->text());
	  record.setValue(6, purchaserDialog->tel2LineEdit->text());
	  record.setValue(7, purchaserDialog->faxLineEdit->text());
	  record.setValue(8, purchaserDialog->mobilLineEdit->text());
	  record.setValue(9, purchaserDialog->adressEdit->toPlainText());
	  
	  
	  purchaserModel->setRecord(row, record);
	  */
	  
	hideAttributes(); 
}

void MainWindow::addGoods(int id, QString str)
{
	QSqlRecord record = goodsModel->record();
	
	record.setValue(0, id);
	record.setValue(1, str);
	
	goodsModel->insertRecord(goodsModel->rowCount(), record);
}

void MainWindow::deleteGoods(int id)
{
	QString str = goodsModel->record().field(0).name(); 
	str += QString(" = ");
	str += QString::number(id);
	
	goodsModel->setFilter(str);
	goodsModel->select();
	int rowCount = goodsModel->rowCount();
	goodsModel->removeRows(0, rowCount);
	goodsModel->submitAll();
	
	goodsModel->setFilter("");
	goodsModel->select();
}

void MainWindow::editGoods()
{
	int row = getTableRow();
	QSqlRecord record = purchaserModel->record(row);
	int id = record.field(0).value().toInt();
	
	deleteGoods(id);
	addGoods(id, goodsDialog->textEdit->toPlainText());
}

//void MainWindow::showGoods()
//{
//  if (getTableRow() == INVALID)
//    return;
//	  
//  CREATE_GOODS(w, this)
//  PREPARE_SHOW(w, actionButton)
//  goodsDialog = w;
//  fillGoods();
//  w->exec();
//}
//
//void MainWindow::addGoods()
//{
//  CREATE_GOODS(w, this)
//  PREPARE_ADD(w, actionButton)
//  goodsDialog = w;
//  connect(w->actionButton, SIGNAL(clicked()), this, SLOT(onAddSignal()));
//  connect(w->actionButton, SIGNAL(clicked()), w, SLOT(close()));
//  w->exec();
//}
//
//void MainWindow::delGoods()
//{
//  if (getTableRow() == INVALID)
//   return;
//  
//  if (goodsModel->rowCount() > 0) {
//    goodsModel->removeRows(getTableRow(), 1);
//    goodsModel->submitAll();
//  }
//  
//  hideAttributes();
//}
//
//void MainWindow::findGoods()
//{
//  CREATE_GOODS(w, this)
//  PREPARE_FIND(w, actionButton)
//  goodsDialog = w;
//  connect(w->actionButton, SIGNAL(clicked()), this, SLOT(onFindSignal()));
//  connect(w->actionButton, SIGNAL(clicked()), w, SLOT(close()));
//  w->exec();
//}
//
//void MainWindow::editGoods()
//{
//  if (getTableRow() == INVALID)
//    return;
//  
//  CREATE_GOODS(w, this)
//  PREPARE_EDIT(w, actionButton)
//  goodsDialog = w;
//  connect(w->actionButton, SIGNAL(clicked()), this, SLOT(onEditSignal()));
//  connect(w->actionButton, SIGNAL(clicked()), w, SLOT(close()));
//  fillGoods();
//  w->exec();
//}
//
//void MainWindow::addSignalGoods(int id)
//{
//  int row = goodsModel->rowCount();
//	  
//  QSqlRecord record = goodsModel->record();
//  if (id == INVALID)
//	  record.setValue(0, generateId(goodsModel->tableName(), record.fieldName(0)));
//  else
//	  record.setValue(0, id);
//  record.setValue(1, goodsDialog->textEdit->toPlainText());
//  
//  goodsModel->insertRecord(row, record);
//  
//  hideAttributes();
//}
//
//
//void MainWindow::findSignalGoods()
//{
//  const QString attributeName = goodsModel->record().field(1).name();
//
//  goodsModel->setFilter(attributeName + " LIKE '%" + goodsDialog->textEdit->toPlainText() + "%'");
//  goodsModel->select();
//  
//  hideAttributes();
//}
//
//
//void MainWindow::editSignalGoods()
//{
//  int row = getTableRow(); 
//  QSqlRecord record = goodsModel->record(row);
//  int id = record.field(0).value().toInt();
//  delGoods();
//  addSignalGoods(id);
//  
//  /*  
//  record.setValue(1, goodsDialog->textEdit->toPlainText());
//
//  goodsModel->setRecord(row, record);
//  */
//  
//  hideAttributes();
//}

void MainWindow::fillPurchaser()
{
  int row = getTableRow();
  QSqlRecord record = purchaserModel->record(row);
  
  purchaserDialog->companyEdit->setText(record.field(1).value().toString());
  purchaserDialog->cityEdit->setText(record.field(2).value().toString());
  purchaserDialog->nameEdit->setText(record.field(3).value().toString());
  purchaserDialog->telEdit->setText(record.field(4).value().toString());
  purchaserDialog->mobilEdit->setText(record.field(5).value().toString());
  purchaserDialog->addressEdit->setText(record.field(6).value().toString());
  purchaserDialog->emailEdit->setText(record.field(7).value().toString());
  purchaserDialog->taxnoEdit->setText(record.field(8).value().toString());
}

void MainWindow::fillGoods()
{
	int row = getTableRow();
  	QSqlRecord purchaserRecord = purchaserModel->record(row);
  	int id = purchaserRecord.field(0).value().toInt();
	QString str = goodsModel->record().field(0).name(); 
	str += QString(" = ");
	str += QString::number(id);
  	goodsModel->setFilter(str);
  	goodsModel->select();
	QSqlRecord goodsRecord = goodsModel->record(0);
	goodsDialog->textEdit->setText(goodsRecord.field(1).value().toString());
	
	goodsModel->setFilter("");
	goodsModel->select();
}
