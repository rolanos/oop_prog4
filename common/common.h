#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum Message
{
    PRINT_TRANSPOSE_REQUEST = 1,
    PRINT_RANK_REQUEST,
    PRINT_DETERMINANT_REQUEST,

    PRINT_TRANSPOSE_RESPONSE,
    PRINT_RANK_RESPONSE,
    PRINT_DETERMINANT_RESPONSE
};

extern const QChar separator;
QString& operator<< (QString&,const QString&);

#endif // COMMON_H
