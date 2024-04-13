#include "common.h"
#include "application.h"
#include "sqare_matrix.h"

//Инициализация работы серверного приложения
TApplication::TApplication(int argc, char *argv[])
    : QCoreApplication(argc,argv)
{
    TCommunicationParams params = { QHostAddress("127.0.0.1"), 10000,
                        QHostAddress("127.0.0.1"), 10001};
    communicator = new TCommunicator(params, this);

    connect(communicator, SIGNAL(recieved(QByteArray)), this, SLOT(recieve(QByteArray)));
}

void TApplication::recieve(QByteArray msg)
{
    //Буффер ответа
    QString answer;
    QString message = QString(msg);
    QStringList numbers = message.split(separator);

    //Очищаем пустые значения
    numbers.removeAll("");

    int matrixSize = numbers.first().toInt();
    int query = numbers.last().toInt();

    //Очищаем первое значение - размерность
    numbers.removeFirst();
    //Очищаем последнее значение - номер запроса
    numbers.removeLast();

    SqareMatrix* matrix = new SqareMatrix(matrixSize);
    //Инициализируем матрицу, которую получили от клиента
    for (int row = 0; row < matrixSize; row++) {
        for (int column = 0; column < matrixSize; column++) {
            QString currentNumStr = numbers[row * matrixSize + column];
            QStringList parts = currentNumStr.split('/');
            switch (parts.length()) {
            case 1:
                matrix->inputValue(number(parts[0].toInt(), 1), row, column);
                break;
            case 2:
                matrix->inputValue(number(parts[0].toInt(), parts[1].toInt()), row, column);
                break;
            default:
               matrix->inputValue(number(), row, column);
            }
        }
    }
    //Матрица для ответа
    SqareMatrix responseMatrix = SqareMatrix(matrixSize);
    //Сообщаяем в консоли о сообщении
    qInfo("The message has been received");
    switch(query) {
    case PRINT_TRANSPOSE_REQUEST: {
            //Вычисление транспонированной матрицы
            responseMatrix = matrix->calculateTranspose();
            answer << QString().number(responseMatrix.getDimension());
            for (int row = 0; row < responseMatrix.getDimension(); ++row) {
                for (int column = 0; column < responseMatrix.getDimension(); ++column) {
                    QString bufferStr;
                    number elem = responseMatrix(row, column);
                    if(elem.denominator != 1) {
                        bufferStr << QString::number(elem.numerator) + QString('/') + QString::number(elem.denominator);
                    }
                    else {
                        bufferStr << QString::number(elem.numerator);
                    }
                    answer += bufferStr;
                }
            }
            answer << QString().setNum(PRINT_TRANSPOSE_RESPONSE);
            break;
        }
    case PRINT_DETERMINANT_REQUEST: {
            //Вычисление детерминанта
            number determinant = matrix->calculateDetermenant();
            QString bufferStr;
            if(determinant.denominator != 1) {
                bufferStr << QString::number(determinant.numerator) + QString('/') + QString::number(determinant.denominator);
            }
            else {
                bufferStr << QString::number(determinant.numerator);
            }

            answer += bufferStr;
            answer << QString().setNum(PRINT_DETERMINANT_RESPONSE);
            break;
    }
    case PRINT_RANK_REQUEST: {
        //Вычисление ранга матрицы
        int rank = matrix->getRank();
            answer << QString::number(rank);
            answer << QString().setNum(PRINT_RANK_RESPONSE);
            break;
    }
    }
    //Отправляем ответ
    communicator->send(answer.toUtf8());
}
