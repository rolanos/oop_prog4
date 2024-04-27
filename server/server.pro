QT += core network

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        application.cpp \
        complex.cpp \
        main.cpp \
        rational.cpp \
        ../common/communicator.cpp \
        ../common/common.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    application.h \
    complex.h \
    matrix.h \
    rational.h \
    ../common/communicator.h \
    ../common/common.h \
    square_matrix.h

INCLUDEPATH += ../common
