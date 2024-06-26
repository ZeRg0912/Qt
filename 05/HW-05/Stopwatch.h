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
     QTime stopTime;
     int circleTime;
     int count;

public:
    explicit Stopwatch(QObject *parent = nullptr);
    ~Stopwatch();
    void UpdateTime();
    void StartTimer();
    void StopTimer();

    QString strCurrentTime;
    QString strCircleTime;

signals:
    void sig_UpdateTime(QString& time);

public slots:
    void ReceiveCircle();
    void ReceiveClear();
};

#endif // STOPWATCH_H
