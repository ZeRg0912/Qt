#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "Stopwatch.h"

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

    void on_pb_Clear_clicked();

    void on_pb_Circle_clicked();

    void UpdateTime(QString text);

signals:
    void sig_CircleTime();
    void sig_ClearTime();

private:
    Ui::MainWindow *ui;
    Stopwatch *watch;
};
#endif // MAINWINDOW_H
