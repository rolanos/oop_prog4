#include "application.h"

TApplication::TApplication(int argc, char *argv[])
    : QApplication(argc,argv)
{
    //Инициализация клиентского приложения
    TCommunicationParams pars = { QHostAddress("127.0.0.1"), 10001,
                        QHostAddress("127.0.0.1"), 10000};
    communicator = new TCommunicator(pars, this);

    interface = new TInterface();
    interface->show();

    //SIGNAL получения сообщения
    connect(communicator,SIGNAL(recieved(QByteArray)),this,
            SLOT(fromCommunicator(QByteArray)));
    //SIGNAL отправки сообщения
    connect(interface,SIGNAL(request(QString)),
            this,SLOT(toCommunicator(QString)));

}

//Получение сообщения(ответа)
void TApplication::fromCommunicator(QByteArray msg)
{
    interface->answer(QString(msg));
}

//Отправка сообщения(запрос)
void TApplication::toCommunicator(QString msg)
{
    communicator->send(QByteArray().append(msg.toUtf8()));
}
