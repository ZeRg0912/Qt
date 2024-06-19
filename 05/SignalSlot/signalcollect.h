#ifndef SIGNALCOLLECT_H
#define SIGNALCOLLECT_H
#include <QObject>
#include <QDebug>

class SignalCollect : public QObject
{
  Q_OBJECT

public:
    explicit SignalCollect(QObject *parent = nullptr);
    ~SignalCollect( void );
    void SendSimpleSignal(void);

signals:
    void sig_SendSimpleSignal(void);
    void sig_SendSignal(QString);
    void sig_SendSignal(int num);

};

#endif // SIGNALCOLLECT_H
