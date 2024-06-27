#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QDebug>

class Stopwatch : public QObject
{
    Q_OBJECT

private:
    QTimer *timer;
    QTime time;
    QTime stop_time;
    int circle_count = 1;

public slots:
    void ReceiveClear();
    void ReceiveCircle();

signals:
    void sig_UpdateTime(QString& time);

public:
    Stopwatch(QObject *parent = nullptr);
    ~Stopwatch();
    void UpdateTime();
    void StartTimer();
    void StopTimer();

    QString current_time = "";
    QString circle_time = "";

};

#endif // STOPWATCH_H
