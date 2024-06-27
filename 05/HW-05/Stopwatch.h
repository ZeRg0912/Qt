#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QDebug>

static const int INTERVAL = 100;

class Stopwatch : public QObject
{
    Q_OBJECT

private:
    QTimer *timer;
    QTime time;
    QTime stop_time;
    int circle_count = 1;    
    QString current_time = "";
    QString circle_time = "";
    void UpdateTime();

public slots:
    void ReceiveClear();
    void ReceiveCircle();

signals:
    void sig_UpdateTime(QString& time);

public:
    Stopwatch(QObject *parent = nullptr);
    ~Stopwatch();
    void StartTimer();
    void StopTimer();
    QString GetCurrentTime();
    QString GetCircleTime();

};

#endif // STOPWATCH_H
