#include "infowindow.h"
#include "ui_infowindow.h"

infoWindow::infoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::infoWindow)
{
    ui->setupUi(this);
}

infoWindow::~infoWindow()
{
    delete ui;
}

void infoWindow::on_pb_Close_clicked()
{
    close();
}

void infoWindow::setData(const QString &text) {
  ui->te_Info->setText(text);
}
