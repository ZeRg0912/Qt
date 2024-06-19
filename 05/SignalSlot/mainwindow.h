#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "signalcollect.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
    SignalCollect *sigColl;


public slots:

    void RcvSignal(QString str);
    void RcvSignal(int num);
    void SendSignals( void );


};


#endif // MAINWINDOW_H
