#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //По умолчанию
    ui->rb_simpleSig->setChecked(true);
    ui->le_str->setEnabled(false);
    ui->spB_num->setEnabled(false);

    connect(ui->rb_simpleSig, &QRadioButton::clicked, this, [&]{
        ui->le_str->setEnabled(false);
        ui->spB_num->setEnabled(false);
    });
    connect(ui->rb_sendStr, &QRadioButton::clicked, this, [&]{
        ui->le_str->setEnabled(true);
        ui->spB_num->setEnabled(false);
    });
    connect(ui->rb_sendNum, &QRadioButton::clicked, this, [&]{
        ui->le_str->setEnabled(false);
        ui->spB_num->setEnabled(true);
    });

    sigColl = new SignalCollect(this);
    sigColl->setObjectName("sigColl");

    QObject::connect(sigColl, &SignalCollect::sig_SendSimpleSignal, this, [&]{
        ui->tb_result->append("Принят простой сигнал от " + QObject::sender()->objectName());
    });

    connect(sigColl, qOverload<QString>(&SignalCollect::sig_SendSignal), this, qOverload<QString>(&MainWindow::RcvSignal));
    connect(sigColl, qOverload<int>(&SignalCollect::sig_SendSignal), this, qOverload<int>(&MainWindow::RcvSignal));

    /*
    enum ConnectionType {
        AutoConnection,   //Если в одном потоке сиг/слот то Direct если в разных то QueuedConnection
        DirectConnection, //Слот вызывается сразу
        QueuedConnection, //Сигнал ставится в цикл обработки событий
        BlockingQueuedConnection, //Блокирует поток
        UniqueConnection =  0x80,
        SingleShotConnection = 0x100,
    };
    */

    connect(ui->pb_sendSignal, &QPushButton::clicked, this, &MainWindow::SendSignals);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RcvSignal(QString str)
{
    ui->tb_result->append("Принята строка " + str);
}
void MainWindow::RcvSignal(int num)
{
    ui->tb_result->append("Принята число " + QString::number(num));
}


void MainWindow::SendSignals()
{
    if(ui->rb_simpleSig->isChecked()){
        sigColl->SendSimpleSignal( );
    }
    else if(ui->rb_sendStr->isChecked()){
        emit sigColl->sig_SendSignal(ui->le_str->text());
    }
    else if(ui->rb_sendNum->isChecked()){
        emit sigColl->sig_SendSignal(ui->spB_num->value());
    }

}




