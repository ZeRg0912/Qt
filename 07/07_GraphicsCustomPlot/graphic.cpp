#include "graphic.h"

Graphic::Graphic(QCustomPlot* cPlot, uint32_t numGraps)
{
   /*
    Выделяем память под объекты графиков. В конструкторе необходимо
    передать оси, по которым будет строиться график.
   */
   ptrGraph.resize(numGraps);

   for(int i = 0; i<ptrGraph.size(); i++){
       ptrGraph[i] = new QCPGraph(cPlot->xAxis, cPlot->yAxis);
   }
   //В отличии от QtCharts QCustomPlot поддерживает встроенные функции масштабирования.
   cPlot->setInteraction(QCP::iRangeZoom, true);
   cPlot->setInteraction(QCP::iRangeDrag, true);
}

/*!
    @brief Метод добавляет данные на график
*/
void Graphic::AddDataToGrahp(QVector<double> x, QVector<double> y, uint32_t numGraph)
{
    //Добавляем данные на серию
    ptrGraph[numGraph]->addData(x,y);
}

/*!
    @brief Метод очищает данные хранящиеся в памяти графиков
*/
void Graphic::ClearGraph(QCustomPlot* cPlot)
{
    //Очищаем данные
    for(int i = 0; i<ptrGraph.size(); i++){
       ptrGraph[i]->data().clear();
    }

    for(int i = 0; i< cPlot->graphCount(); i++){
        cPlot->graph(i)->data()->clear();
    }
    //Обновляем отображение графика
    cPlot->replot();

}

/*!
    @brief Слот обновляет отрисовку графика
*/
void Graphic::UpdateGraph(QCustomPlot *cPlot){
    //Масштабируем оси
    cPlot->rescaleAxes();
    //Отрисовываем график
    cPlot->replot();
}





