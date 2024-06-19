#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_Connect_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(ui->le_HostName->text());
    db.setDatabaseName(ui->le_DBName->text());
    db.setUserName(ui->le_Login->text());
    db.setPassword(ui->le_Password->text());
    Dialog* dialog= new Dialog(this);
    dialog->show();
}

