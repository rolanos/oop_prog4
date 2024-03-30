#include "application.h"

int main(int argc, char *argv[])
{
    TApplication application = TApplication(argc, argv);
    return application.exec();
}
