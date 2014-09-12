#ifndef PURCHASERDIALOG_H_
#define PURCHASERDIALOG_H_

#include <QDialog>
#include <ui_purchaser.h>

class PurchaserDialog : public QDialog, public Ui::Purchaser
{
public:
  PurchaserDialog(QWidget *parent = 0);
};

#endif /*PURCHASERDIALOG_H_*/
