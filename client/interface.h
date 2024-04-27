#ifndef TINTERFACE_H
#define TINTERFACE_H

//Интерфейсные классы
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QTableWidget>
#include <QTableWidgetItem>

#include <common.h>

class TInterface : public QWidget
{
    Q_OBJECT

    //QLabels
    QLabel *matrixSizeTitle;
    QLabel *matrixTitle;
    QLabel *outputTitle;
    QLabel *outputValue;

    //QLinesEdit
    QLineEdit *matrixSizeField;

    //Таблица(визуализация матрицы)
    QTableWidget *matrixTable;
    QTableWidget *martixOutput;

    //QPushButtons
    QPushButton* transposeButton;
    QPushButton* determinantButton;
    QPushButton* rankButton;

    //Radio
    QRadioButton* double_mode;
    QRadioButton* complex_mode;
    QRadioButton* rational_mode;

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

public slots:
    void answer(QString);

private slots:
    //отправляем сообщение в зависимости от запроса
    void formRequest();
    //Callback при изменении размера матрицы
    void onMatrixSizeChanged(const QString&);

signals:
    void request(QString);
};
#endif // TINTERFACE_H
