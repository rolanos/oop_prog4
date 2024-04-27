#include "common.h"
#include "application.h"
#include "square_matrix.h"
#include "rational.h"
#include "complex.h"

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
    int mode = numbers[1].toInt();
    int query = numbers.last().toInt();

    //Очищаем первое значение - размерность
    numbers.removeFirst();
    //Удаляем значение режима
    numbers.removeAt(1);
    //Очищаем последнее значение - номер запроса
    numbers.removeLast();

    switch (mode) {
        case DOUBLE_MODE: {
        //Матрица для ответа
        SqareMatrix<double> responseMatrix = SqareMatrix<double>(matrixSize);
        //Сообщаяем в консоли о сообщении
        qInfo("The message has been received");
        SqareMatrix<double>* matrix = new SqareMatrix<double>(matrixSize);
        //Инициализируем матрицу, которую получили от клиента
        for (int row = 0; row < matrixSize; row++) {
            for (int column = 0; column < matrixSize; column++) {
                QString currentNumStr = numbers[row * matrixSize + column];
                QStringList parts = currentNumStr.split('/');
                switch (parts.length()) {
                case 1:
                    matrix->inputValue(parts[0].toInt(), row, column);
                    break;
                default:
                    matrix->inputValue(0, row, column);
                }
            }
        }
        switch(query) {
        case PRINT_TRANSPOSE_REQUEST: {

                //Вычисление транспонированной матрицы
                responseMatrix = matrix->calculateTranspose();
                answer << QString().number(responseMatrix.getDimension());
                for (int row = 0; row < responseMatrix.getDimension(); ++row) {
                    for (int column = 0; column < responseMatrix.getDimension(); ++column) {
                        QString bufferStr;
                        double elem = responseMatrix(row, column);

                        bufferStr << QString::number(elem);

                        answer += bufferStr;
                    }
                }
                answer << QString().setNum(PRINT_TRANSPOSE_RESPONSE);
                break;
            }
            case PRINT_DETERMINANT_REQUEST: {
                //Вычисление детерминанта
                double determinant = matrix->calculateDetermenant();
                QString bufferStr;

                bufferStr << QString::number(determinant);

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
        }
        case COMPLEX_MODE: {
            SqareMatrix<TComplex>* matrix = new SqareMatrix<TComplex>(matrixSize);
            //Инициализируем матрицу, которую получили от клиента
            for (int row = 0; row < matrixSize; row++) {
                for (int column = 0; column < matrixSize; column++) {
                    QString currentNumStr = numbers[row * matrixSize + column];
                    QStringList parts = currentNumStr.split(' ');
                    switch (parts.length()) {
                    case 1:
                        matrix->inputValue(TComplex(parts[0].toDouble(), 1), row, column);
                        break;
                    case 2:
                        matrix->inputValue(TComplex(parts[0].toDouble(), parts[1].toDouble()), row, column);
                        break;
                    default:
                        matrix->inputValue(TComplex(), row, column);
                    }
                }
            }
            //Матрица для ответа
            SqareMatrix<TComplex> responseMatrix = SqareMatrix<TComplex>(matrixSize);
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
                        TComplex elem = responseMatrix(row, column);
                        QString separator;
                        if(elem.getImaginary() >= 0) {
                            separator = QString("+");
                        }
                        else {
                            separator = QString("-");
                        }
                        bufferStr << QString::number(elem.getReal()) + separator + QString::number(elem.getImaginary());
                        answer += bufferStr;
                    }
                }
                answer << QString().setNum(PRINT_TRANSPOSE_RESPONSE);
                break;
            }
            case PRINT_DETERMINANT_REQUEST: {
                //Вычисление детерминанта
                TComplex determinant = matrix->calculateDetermenant();
                QString bufferStr;
                //Если часть мнимая == 0, то без отступа
                QString separator;
                if(determinant.getImaginary() >= 0) {
                    separator = QString("+");
                }
                else {
                    separator = QString("-");
                }

                bufferStr << QString::number(determinant.getReal()) + separator + QString::number(determinant.getImaginary());

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
        }
        case RATIONAL_MODE: {
            SqareMatrix<TRational>* matrix = new SqareMatrix<TRational>(matrixSize);
            //Инициализируем матрицу, которую получили от клиента
            for (int row = 0; row < matrixSize; row++) {
                for (int column = 0; column < matrixSize; column++) {
                    QString currentNumStr = numbers[row * matrixSize + column];
                    QStringList parts = currentNumStr.split('/');
                    switch (parts.length()) {
                    case 1:
                        matrix->inputValue(TRational(parts[0].toInt(), 1), row, column);
                        break;
                    case 2:
                        matrix->inputValue(TRational(parts[0].toInt(), parts[1].toInt()), row, column);
                        break;
                    default:
                        matrix->inputValue(TRational(), row, column);
                    }
                }
            }
            //Матрица для ответа
            SqareMatrix<TRational> responseMatrix = SqareMatrix<TRational>(matrixSize);
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
                        TRational elem = responseMatrix(row, column);
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
                TRational determinant = matrix->calculateDetermenant();
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
    }



    //Отправляем ответ
    communicator->send(answer.toUtf8());
}
