#include <QObject>
#include <QApplication>

#include "interface.h"
#include "communicator.h"

class TApplication : public QApplication
{
    Q_OBJECT

    TCommunicator *communicator;
    TInterface    *interface;

public:
    TApplication(int, char**);

public slots:
    void fromCommunicator(QByteArray);
    void toCommunicator(QString);

};
