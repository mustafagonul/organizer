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
