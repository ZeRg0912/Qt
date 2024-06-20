#include "dialog.h"
#include "./ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pb_Connect_clicked()
{
    InfoWIndow->close();

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

    InfoWIndow->show();
    InfoWIndow->setData(connectionInfo);
}

