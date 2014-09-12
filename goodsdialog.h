#ifndef GOODSDIALOG_H_
#define GOODSDIALOG_H_

#include <QDialog>
#include <ui_goods.h>

class GoodsDialog : public QDialog, public Ui::Goods
{
public:
  GoodsDialog(QWidget *parent = 0);
};

#endif /*GOODSDIALOG_H_*/
