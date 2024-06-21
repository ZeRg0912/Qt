#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->rb_Mode1->setText("Frequency mode");
    ui->rb_Mode2->setText("Amplitude mode");

    for (int i = 0; i <= 10; i++) {
        ui->cb_FrequencySelect->addItem(QString("%1").arg(i));
    }

    ui->pb_Start->setText("Start / Stop");
    ui->pb_Start->setCheckable(true);

    ui->prb_Frequency->setMinimum(0);
    ui->prb_Frequency->setMaximum(10);
    ui->prb_Frequency->setValue(0);

    ui->rb_Mode1->setChecked(true);
    ui->te_OutputInfo->clear();

    ui->cb_FrequencySelect->setCurrentIndex(0);
    uint32_t val = ui->cb_FrequencySelect->currentText().toInt();
    ui->prb_Frequency->setValue(val);
    InfoOut();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::InfoOut() {
    QString info;
    uint32_t mode = 0;
    uint32_t val = ui->cb_FrequencySelect->currentText().toInt();
    if (ui->rb_Mode1->isChecked()) mode = 1;
    else mode = 2;
    info.append("Selected frequency: " + QString::number(val) + " GHz\n");
    info.append("Selected mode: " + QString::number(mode) + '\n');
    ui->te_OutputInfo->setText(info);
}


void MainWindow::on_pb_Start_toggled(bool checked)
{
    if (checked) {
        ui->pb_Start->setStyleSheet("background-color:green;");
        ui->prb_Frequency->setStyleSheet("background-color:green;");
        ui->rb_Mode1->setEnabled(false);
        ui->rb_Mode2->setEnabled(false);

    }
    else {
        ui->pb_Start->setStyleSheet("background-color: rgb(173, 0, 0);");
        ui->prb_Frequency->setStyleSheet("background-color: rgb(173, 0, 0);");
        ui->rb_Mode1->setEnabled(true);
        ui->rb_Mode2->setEnabled(true);
    }
}


void MainWindow::on_cb_FrequencySelect_currentIndexChanged(int index)
{
    ui->cb_FrequencySelect->currentIndex();
    ui->cb_FrequencySelect->currentData();
    uint32_t val = ui->cb_FrequencySelect->currentText().toInt();
    ui->prb_Frequency->setValue(val);
    InfoOut();

}


void MainWindow::on_pb_Next_clicked()
{
    uint32_t index = ui->cb_FrequencySelect->currentIndex() + 1;
    uint32_t max_index = ui->cb_FrequencySelect->maxCount() - 1;
    if (index == max_index + 1) index = 0;
    ui->cb_FrequencySelect->setCurrentIndex(index);
    uint32_t val = ui->cb_FrequencySelect->currentText().toInt();
    ui->prb_Frequency->setValue(val);
}


void MainWindow::on_pb_Prev_clicked()
{
    uint32_t index = ui->cb_FrequencySelect->currentIndex() - 1;
    uint32_t min_index = 0;
    if (index == (min_index - 1)) index = ui->cb_FrequencySelect->maxCount() - 1;
    ui->cb_FrequencySelect->setCurrentIndex(index);
    uint32_t val = ui->cb_FrequencySelect->currentText().toInt();
    ui->prb_Frequency->setValue(val);
}


void MainWindow::on_rb_Mode2_clicked()
{
    InfoOut();
}


void MainWindow::on_rb_Mode1_clicked()
{
    InfoOut();
}
