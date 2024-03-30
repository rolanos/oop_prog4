#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

struct TCommunicationParams
{
    QHostAddress recieverHost;
    quint16      recieverPort;
    QHostAddress sendHost;
    quint16      sendPort;
};

class TCommunicator : public QUdpSocket
{
    Q_OBJECT

    bool isReady;
    TCommunicationParams  params;

public:
    TCommunicator(TCommunicationParams&, QObject *parent = nullptr);
    bool checkReady();

signals:
    void recieved(QByteArray);

public slots:
    void send(QByteArray);

private slots:
    void recieve();
};

#endif // COMMUNICATOR_H
