#include "dbdata.h"
#include "database.h"
#include "ui_dbdata.h"

DbData::DbData(QWidget *parent) : QDialog(parent)
    , ui(new Ui::DbData)
{
    ui->setupUi(this);
    data.resize(NUM_DATA_FOR_CONNECT_TO_DB);
}

DbData::~DbData()
{
    delete ui;
}

void DbData::on_pb_Connect_clicked()
{
    data[hostName] = ui->le_HostName->text();
    data[dbName] = ui->le_DBName->text();
    data[login] = ui->le_Login->text();
    data[pass] = ui->le_Password->text();
    data[port] = ui->sb_Port->text();

    emit sig_sendData(data);
    this->close();
}

