#include "signalcollect.h"

SignalCollect::SignalCollect(QObject *parent) : QObject{parent}
{

}

SignalCollect::~SignalCollect()
{

    qDebug() << "SignalCollect delete";

}

void SignalCollect::SendSimpleSignal()
{
    //Код метода
    emit sig_SendSimpleSignal( );
    //продолжение
}
