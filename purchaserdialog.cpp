#include "purchaserdialog.h"

PurchaserDialog::PurchaserDialog(QWidget *parent)
  : QDialog(parent)
{
  setupUi(this);
  connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
}
