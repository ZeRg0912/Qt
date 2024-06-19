#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->rb_cos->setChecked(true);
    //Создаем объект нашего класса
    graphClass = new Graphic(ui->customPlot, NUM_GRAPH);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete graphClass;
}

/*!
    @brief Метод обрабатывает нажатие кнопки "Очистить"
*/
void MainWindow::on_pb_clear_clicked()
{
    graphClass->ClearGraph(ui->customPlot);
}

/*!
    @brief Метод обрабатывает нажатие кнопки "Построить"
*/
void MainWindow::on_pb_updGraph_clicked()
{

    //Перед новой отрисовкой очистим графики
    graphClass->ClearGraph(ui->customPlot);

    /*
        Создаем контейнеры для хранения данных
    */
    QVector<double> x;
    QVector<double> y;

    /*
        считываем шаг сетки и граничные значения
    */
    double step = ui->dsB_step->value();
    //Шаг не может быть равен нулю
    if(step <= 0){
        step = 0.1;
        ui->dsB_step->setValue(0.1);
    }

    double minVal = ui->dsB_minRange->value();
    double maxVal = ui->dsB_maxRange->value() + step; //Учитываем ноль

    /*
        Формируем сетку значений, ресайзим вектор и заполняем его
    */
    double steps = round(((maxVal-minVal)/step));
    x.resize(steps);
    x[0] = minVal; //Начинакем с минимального значения
    for(int i = 1; i<steps; i++){
        x[i] = x[i-1]+step;
    }

    /*
     * Заполняем массив значений в зависимости
     * от выбранного флажка
     */
    y.resize(steps);
    //Если выбран косинус
    if(ui->rb_cos->isChecked()){
        for(int i = 0; i<steps; i++){
            y[i] = cos(x[i]);
        }
        graphClass->AddDataToGrahp(x, y, FIRST_GRAPH);
    }
    else if(ui->rb_sinx_x->isChecked()){
        for(int i = 0; i<steps; i++){
            y[i] = sin(x[i])/(x[i]);
        }
        graphClass->AddDataToGrahp(x, y, FIRST_GRAPH);
    }
    else if(ui->rb_mouse->isChecked()){

        minVal = -7;
        step = 0.01;
        maxVal = 7+step;
        steps = round(((maxVal-minVal)/step));
        x.clear();
        x.resize(steps);
        x[0] = minVal;
        for(int i = 1; i<steps; i++){
            x[i] = x[i-1]+step;
        }

        QVector<double> data;
        data.resize(steps);
        y.clear();
        y.resize(steps);

        for(int i = 0; i<2; i++){
            data = ConstructMouse(i, x);
            graphClass->AddDataToGrahp(x, data, i);
            data.clear();
        }

    }

    graphClass->UpdateGraph(ui->customPlot);

}



/*!
    @brief Метод строит лого Бэтмена
*/
QVector<double> MainWindow::ConstructMouse(int numForm, QVector<double> x)
{

    QVector<double> result;
    result.resize(x.size());

    double tmpX = 0;
    if(numForm == 0){

        for(int i = 0; i<x.size(); i++){
            tmpX = abs(x[i]);

            if(tmpX>7){

                continue;

            }
            else if (tmpX < 0.5){

                result[i] = 2.25;

            }
            else if(0.5 <= tmpX  && tmpX < 0.75 ){

                result[i] = 3 * tmpX + 0.75;

            }
            else if (0.75 <= tmpX && tmpX< 1.0){

                result[i] = 9 - 8 * tmpX;

            }
            else if(1 <= tmpX && tmpX < 3){

                result[i] = (1.5 - 0.5 * tmpX - 3 * sqrt(10) / 7 * (sqrt(3 - tmpX*tmpX + 2 * tmpX) - 2));

            }
            else if(3 <= tmpX && tmpX <= 7){

                result[i] = 3 * sqrt(-((tmpX / 7)*(tmpX / 7)) + 1);

            }

        }
    }
    else if(numForm == 1){

        for(int i = 0; i< x.size(); i++){

            tmpX = abs(x[i]);

            if(tmpX > 7){
                continue;
            }
            else if(0 <= tmpX && tmpX< 4 ){

                result[i] = (abs(tmpX / 2) - (3*sqrt(33) - 7) / 112 * tmpX*tmpX + sqrt(1 - (abs(tmpX - 2) - 1)*(abs(tmpX - 2) - 1)) - 3);
            }
            else if(4 <= tmpX && tmpX <= 7){

                result[i] = -3 * sqrt(-((tmpX / 7)*(tmpX / 7)) + 1);
            }
        }
    }

    return result;
}



