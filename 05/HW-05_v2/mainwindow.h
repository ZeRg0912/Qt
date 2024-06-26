#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stopwatch.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_StartStop_toggled(bool checked);

    void on_pb_NewCircle_clicked();

    void on_pb_Clear_clicked();

    void ReceiveTime(QString& text);

signals:
    void sig_Circle();
    void sig_Clear();
    void sig_Start();
    void sig_Stop();

private:
    Ui::MainWindow *ui;
    Stopwatch *watch;
};
#endif // MAINWINDOW_H
