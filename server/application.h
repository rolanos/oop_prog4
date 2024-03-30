#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QCoreApplication>

#include "communicator.h"

class TApplication : public QCoreApplication
{
    Q_OBJECT
    //Класс-коммуникатор
    TCommunicator *communicator;

public:

    TApplication(int, char**);

signals:

public slots:

    void recieve(QByteArray);

};

#endif // APPLICATION_H
