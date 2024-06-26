#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    watch = new Stopwatch(this);

    ui->lb_Time->setText("Время, с");
    ui->le_Time->setText("0:00.0");
    ui->pb_Clear->setText("Сбросить");
    ui->pb_NewCircle->setText("Круг");
    ui->pb_StartStop->setText("Старт");
    ui->pb_StartStop->setStyleSheet("background-color:green;");
    ui->pb_NewCircle->setEnabled(false);

    connect(watch, &Stopwatch::sig_UpdateTime, this, &MainWindow::ReceiveTime);
    connect(this, &MainWindow::sig_Circle, watch, &Stopwatch::ReceiveCircle);
    connect(this, &MainWindow::sig_Clear, watch, &Stopwatch::ReceiveClear);
    connect(this, &MainWindow::sig_Start, watch, &Stopwatch::StartTimer);
    connect(this, &MainWindow::sig_Stop, watch, &Stopwatch::StopTimer);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ReceiveTime(QString &text)
{
    ui->le_Time->setText(text);
}


void MainWindow::on_pb_StartStop_toggled(bool checked) {
    if (checked) {
        ui->pb_StartStop->setText("Пауза");
        ui->pb_StartStop->setStyleSheet("background-color: rgb(173, 0, 0);");
        ui->pb_NewCircle->setEnabled(true);
        emit sig_Start();

    } else {
        ui->pb_StartStop->setText("Старт");
        ui->pb_StartStop->setStyleSheet("background-color:green;");
        ui->pb_NewCircle->setEnabled(false);
        watch->StopTimer();
        emit sig_Stop();
    }
}


void MainWindow::on_pb_NewCircle_clicked() {
    emit sig_Circle();
    QString text = watch->circle_time;
    ui->tb_Circles->append(text);
}


void MainWindow::on_pb_Clear_clicked() {
    ui->tb_Circles->clear();
    ui->le_Time->setText("00:00.0");
    emit sig_Clear();
}

