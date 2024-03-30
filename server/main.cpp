#include <QCoreApplication>
#include<QDebug>

#include "application.h"

int main(int argc, char *argv[])
{
    qInfo("Getting started with the server");
    TApplication a(argc, argv);
    return a.exec();
}
