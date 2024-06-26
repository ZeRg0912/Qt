#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    watch = new Stopwatch(this);
    ui->pb_StartStop->setStyleSheet("background-color: rgb(173, 0, 0);");
    ui->lb_Time->setText("Время, с");
    ui->le_Time->setText(QString("0.00"));
    ui->pb_Circle->setEnabled(false);

    connect(watch, &Stopwatch::sig_UpdateTime, this, &MainWindow::UpdateTime);
    connect(this, &MainWindow::sig_CircleTime, watch, &Stopwatch::ReceiveCircle);
    connect(this, &MainWindow::sig_ClearTime, watch, &Stopwatch::ReceiveClear);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::UpdateTime(QString text)
{
    ui->le_Time->setText(text);
}


void MainWindow::on_pb_StartStop_toggled(bool checked)
{
    if (checked) {
        ui->pb_StartStop->setText("СТОП");
        ui->pb_StartStop->setStyleSheet("background-color: rgb(173, 0, 0);");
        ui->pb_Circle->setEnabled(true);
        watch->StartTimer();
    }
    else {
        ui->pb_StartStop->setText("СТАРТ");
        ui->pb_StartStop->setStyleSheet("background-color:green;");
        ui->pb_Circle->setEnabled(false);
        watch->StopTimer();
    }
}


void MainWindow::on_pb_Clear_clicked()
{
    ui->tb_CircleTime->clear();
    ui->le_Time->setText("00:00.0");
    emit sig_ClearTime();
}


void MainWindow::on_pb_Circle_clicked()
{
    emit sig_CircleTime();
    QString text = watch->strCircleTime;
    ui->tb_CircleTime->append(text);
}
