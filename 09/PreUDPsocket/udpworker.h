#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>


#define BIND_PORT 12345

class UDPworker : public QObject
{
    Q_OBJECT
public:
    explicit UDPworker(QObject *parent = nullptr);
    void InitSocket( void );
    void ReadDatagram( QNetworkDatagram datagram);
    void SendDatagram(QByteArray data );


private slots:
    void readPendingDatagrams(void);

private:
    QUdpSocket* serviceUdpSocket;

signals:
    void sig_sendTimeToGUI(QDateTime data);

};

#endif // UDPWORKER_H
