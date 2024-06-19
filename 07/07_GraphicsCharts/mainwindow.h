#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphicchart.h"
#include <QLineSeries>
#include <QChart>
#include <QChartView>

#define NUM_GRAPHS 2

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

    void ViewGraph(void);

    QVector<double> ConstructMouse(int numForm, QVector<double> x);

    GraphicChart* graphClass;
    QChart* chart;
    QChartView* chartView;
    QGridLayout *layout;
};
#endif // MAINWINDOW_H
