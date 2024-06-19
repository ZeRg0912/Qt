#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "graphic.h"

#define NUM_GRAPH 2

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
    void on_pb_clear_clicked();
    void on_pb_updGraph_clicked();

private:
    Ui::MainWindow *ui;
    QCPGraph* graphic;
    Graphic* graphClass;

    QVector<double> ConstructMouse(int numForm, QVector<double> x);

};
#endif // MAINWINDOW_H
