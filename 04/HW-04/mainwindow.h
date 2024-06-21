#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void InfoOut();

private slots:
    void on_pb_Start_toggled(bool checked);

    void on_cb_FrequencySelect_currentIndexChanged(int index);

    void on_pb_Next_clicked();

    void on_pb_Prev_clicked();

    void on_rb_Mode2_clicked();

    void on_rb_Mode1_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
