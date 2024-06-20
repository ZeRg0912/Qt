#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pb_Close_clicked()
{
    close();
}

void Dialog::setData(const QString &text) {
  ui->te_Info->setText(text);
}
