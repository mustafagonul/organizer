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

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>
#include <ui_mainwindow.h>
#include <utility.h>

class QSqlRelationalTableModel;
class GoodsDialog;
class PurchaserDialog;

class MainWindow : public QMainWindow, public Ui::MainWindow
{
  Q_OBJECT
  
public:
  MainWindow(QWidget *parent = 0);

private:
  int getTableRow()const;
  void createConnections();
  void createTables();
  void hideAttributes();
  void setAttributes();
  
private slots:
  void onShow();
  void onShowAll();
  void onAdd();
  void onDelete();
  void onFind();
  void onEdit();
  void onGoods();
  
  void addPurchaser(int id = INVALID);
  void deletePurchaser(int row);
  void findPurchaser();
  void editPurchaser();
  
  void editGoods();
  
private:
	void addGoods(int id, QString str = "");
	void deleteGoods(int id);
  
//  void addSignalPurchasers(int id = INVALID);
//  void addSignalGoods(int id = INVALID);
//
//  void findSignalPurchasers();
//  void findSignalGoods();
//  
//  void editSignalPurchasers();
//  void editSignalGoods();
//  
//  
  void fillPurchaser();
  void fillGoods();
  
  
//  void onIndexChanged();
  
private:
  QSqlRelationalTableModel *purchaserModel;
  QSqlRelationalTableModel *goodsModel;
  
  GoodsDialog *goodsDialog;
  PurchaserDialog *purchaserDialog;
  
//  int goodsIndex;
//  int purchaserIndex;
};

#endif /*MAINWINDOW_H_*/
