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
    QStatusBar * StatusBar = statusBar();
    StatusBar->showMessage("Trying connection...", 1500);

    dialog->close();

    db.setHostName(ui->le_HostName->text());
    db.setDatabaseName(ui->le_DBName->text());
    db.setUserName(ui->le_Login->text());
    db.setPassword(ui->le_Password->text());
    db.setPort(ui->sb_Port->value());

    bool connected = db.open();

    QString connection;
    if (connected) connection = "Successful";
    else connection = "Failed";

    QString connectionInfo =      "Host name: " + ui->le_HostName->text() + "\n";
            connectionInfo.append("Data base: " + ui->le_DBName->text()   + "\n");
            connectionInfo.append("Login: "     + ui->le_Login->text()    + "\n");
            connectionInfo.append("Password: "  + ui->le_Password->text() + "\n");
            connectionInfo.append("Port: "      + ui->sb_Port->text()     + "\n");
            connectionInfo.append("Connection: "+ connection              + "\n");

    dialog->show();
    dialog->setData(connectionInfo);
}

