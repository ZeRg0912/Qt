#include "tcpclient.h"

TCPclient::TCPclient(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, [&](){
        emit sig_connectStatus(STATUS_SUCCESS);
    });

    connect(socket, &QTcpSocket::errorOccurred, this, [&](){
        emit sig_connectStatus(ERR_CONNECT_TO_HOST);});

    connect(socket, &QTcpSocket::readyRead, this, &TCPclient::ReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &TCPclient::sig_Disconnected);
}

/* Операторы << и >> для сериализации ServiceHeader */
QDataStream &operator <<(QDataStream &out, const ServiceHeader &header){
    out << header.id
        << header.idData
        << header.status
        << header.len;
    return out;
}

QDataStream &operator >>(QDataStream &in, ServiceHeader &header){
    in >> header.id
       >> header.idData
       >> header.status
       >> header.len;
    return in;
}

/* Операторы << и >> для сериализации StatServer */
QDataStream &operator >>(QDataStream &out, StatServer &stat){

    out >> stat.incBytes
        >> stat.sendBytes
        >> stat.revPck
        >> stat.sendPck
        >> stat.workTime
        >> stat.clients;
    return out;
};

QDataStream &operator <<(QDataStream &in, StatServer &stat){

    in << stat.incBytes
       << stat.sendBytes
       << stat.revPck
       << stat.sendPck
       << stat.workTime
       << stat.clients;
    return in;
};

void TCPclient::SendRequest(ServiceHeader head) {
    QByteArray send;
    QDataStream out(&send, QIODevice::WriteOnly);
    out << head;
    socket->write(send);
}

void TCPclient::SendData(ServiceHeader head, QString data) {
    QByteArray send;
    QDataStream out(&send, QIODevice::WriteOnly);
    out << head;
    out << data;
    socket->write(send);
}

void TCPclient::ConnectToHost(QHostAddress host, uint16_t port) {
    socket->connectToHost(host, port);
}

void TCPclient::DisconnectFromHost() {
    socket->disconnectFromHost();
}

void TCPclient::ReadyRead() {

    QDataStream incStream(socket);

    if(incStream.status() != QDataStream::Ok){
        QMessageBox msg;
        msg.setIcon(QMessageBox::Warning);
        msg.setText("Ошибка открытия входящего потока для чтения данных!");
        msg.exec();
    }


    //Читаем до конца потока
    while(incStream.atEnd() == false){
        //Если мы обработали предыдущий пакет, мы скинули значение idData в 0
        if(servHeader.idData == 0){

            //Проверяем количество полученных байт. Если доступных байт меньше чем
            //заголовок, то выходим из обработчика и ждем новую посылку. Каждая новая
            //посылка дописывает данные в конец буфера
            if(socket->bytesAvailable() < sizeof(ServiceHeader)){
                return;
            }
            else{
                //Читаем заголовок
                incStream >> servHeader;
                //Проверяем на корректность данных. Принимаем решение по заранее известному ID
                //пакета. Если он "битый" отбрасываем все данные в поисках нового ID.
                if(servHeader.id != ID){
                    uint16_t hdr = 0;
                    while(incStream.atEnd()){
                        incStream >> hdr;
                        if(hdr == ID){
                            incStream >> servHeader.idData;
                            incStream >> servHeader.status;
                            incStream >> servHeader.len;
                            break;
                        }
                    }
                }
            }
        }
        //Если получены не все данные, то выходим из обработчика. Ждем новую посылку
        if(socket->bytesAvailable() < servHeader.len){
            return;
        }
        else{
            //Обработка данных
            ProcessingData(servHeader, incStream);
            servHeader.idData = 0;
            servHeader.status = 0;
            servHeader.len = 0;
        }
    }
}

/*
 * Остался метод обработки полученных данных. Согласно протоколу
 * мы должны прочитать данные из сообщения и вывести их в ПИ.
 * Поскольку все типы сообщений нам известны реализуем выбор через
 * switch. Реализуем получение времени.
*/

void TCPclient::ProcessingData(ServiceHeader header, QDataStream &stream) {

    switch (header.idData){

    case GET_TIME: {
        QDateTime time;
        stream >> time;
        emit sig_sendTime(time);
        break;
    }

    case GET_SIZE: {
        uint32_t len;
        stream >> len;
        emit sig_sendFreeSize(len);
        break;
    }
    case GET_STAT: {
        StatServer status;
        stream >> status;
        emit sig_sendStat(status);
        break;
    }

    case SET_DATA: {
        QString message;
        stream >> message;
        if (header.status == ERR_NO_FREE_SPACE)
        {
            message = "ERR_NO_FREE_SPACE";
        }
        emit sig_SendReplyForSetData(message);
        break;
    }
    case CLEAR_DATA: {
        QString message = "данные на сервере очищены";
        emit sig_SendReplyForSetData(message);
        break;
    }
    default:
        return;

    }

}
