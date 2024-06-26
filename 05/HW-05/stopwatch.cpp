#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent) : QObject{parent}
{
    time.setHMS(0, 0, 0, 0);
    stopTime.setHMS(0, 0, 0, 0);
    circleTime = 0;
    count = 1;

    timer = new QTimer(this);
    timer->setInterval(100);
    connect(timer, &QTimer::timeout, this, &Stopwatch::UpdateTime);
}

Stopwatch::~Stopwatch()
{
    delete timer;
}

void Stopwatch::UpdateTime()
{
    time = time.addMSecs(100);
    strCurrentTime = time.toString("mm:ss.z");
    emit sig_UpdateTime(strCurrentTime);
}

void Stopwatch::StartTimer()
{
    timer->start();
    UpdateTime();
}

void Stopwatch::StopTimer()
{
    timer->stop();
}

void Stopwatch::ReceiveCircle()
{
    circleTime = stopTime.secsTo(time);
    strCircleTime = "Круг " + QString::number(count) + " , время: " + QString::number(circleTime) + " сек";
    stopTime = time;
    count++;
}

void Stopwatch::ReceiveClear()
{
    count = 1;
    time.setHMS(0, 0, 0, 0);
    stopTime.setHMS(0, 0, 0, 0);
}

