#include "goodsdialog.h"

GoodsDialog::GoodsDialog(QWidget *parent)
  : QDialog(parent)
{
  setupUi(this);
  connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
}
