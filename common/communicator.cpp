#include "communicator.h"

TCommunicator::TCommunicator(TCommunicationParams& pars, QObject *parent) : QUdpSocket(parent)
{
    params = pars;
    isReady = bind(params.recieverHost, params.recieverPort,
                 QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
    if (isReady) connect(this,SIGNAL(readyRead()),this,SLOT(recieve()));
}

bool TCommunicator::checkReady()
{
    return isReady;
}

void TCommunicator::send(QByteArray message)
{
    if (isReady)
        writeDatagram(message, params.sendHost, params.sendPort);

}

void TCommunicator::recieve()
{
    if (hasPendingDatagrams())
    {
        quint64 size = pendingDatagramSize();
        QByteArray message(size,'\0');
        readDatagram(message.data(), size);
        emit recieved(message);
    }
}
