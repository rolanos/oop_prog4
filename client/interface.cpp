#include "interface.h"


TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    int width= 800;
    int height =480;
    setWindowTitle("Клиент ПР_5");
    setFixedSize(width, height);

    matrixSizeTitle = new QLabel("Размер матрицы:", this);
    matrixSizeTitle->setGeometry(width * 0.05, height * 0.07, width * 0.15, width * 0.05);
    matrixSizeField = new QLineEdit(this);
    matrixSizeField->setGeometry(width * 0.2, height * 0.07, width * 0.05, width * 0.05);
    matrixSizeField->setValidator( new QIntValidator(0, 20, this));

    matrixTitle = new QLabel("Matrix elements:", this);
    matrixTitle->setGeometry(width * 0.05, width * 0.15, width * 0.1, width * 0.05);

    matrixTable = new QTableWidget(this);
    matrixTable->setGeometry(width * 0.05, height * 0.2, width * 0.5, height * 0.4);

    transposeButton = new QPushButton("Транспонировать", this);
    transposeButton->setGeometry(width * 0.6, height * 0.2, width * 0.2, height * 0.1);

    determinantButton = new QPushButton("Детерминант", this);
    determinantButton->setGeometry(width * 0.6, height * 0.35, width * 0.2, height * 0.1);

    rankButton = new QPushButton("Ранг", this);
    rankButton->setGeometry(width * 0.6, height * 0.5, width * 0.2, height * 0.1);

    outputTitle = new QLabel("Вывод:", this);
    outputTitle->setGeometry(width * 0.05, height * 0.6, width * 0.1, width * 0.05);

    outputValue = new QLabel("",this);
    outputValue->setGeometry(width * 0.05, height * 0.65, width * 0.1, width * 0.05);
    outputValue->setVisible(false);

    martixOutput = new QTableWidget(this);
    martixOutput->setGeometry(width * 0.05, height * 0.7, width * 0.4, height * 0.2);
    martixOutput->setVisible(false);
    //SIGNALS

    connect(matrixSizeField, SIGNAL(textChanged(const QString &)), this, SLOT(onMatrixSizeChanged(const QString &)));

    connect(transposeButton,SIGNAL(pressed()),
            this,SLOT(formRequest()));
    connect(rankButton,SIGNAL(pressed()),
            this,SLOT(formRequest()));
    connect(determinantButton,SIGNAL(pressed()),
            this,SLOT(formRequest()));
}

TInterface::~TInterface() {
    delete matrixSizeTitle;
    delete matrixTitle;
    delete outputTitle;
    delete outputValue;
    delete matrixSizeField;
    delete matrixTable;
    delete martixOutput;
    delete transposeButton;
    delete determinantButton;
    delete rankButton;
}

//slots
void TInterface::onMatrixSizeChanged(const QString &size) {
    int n = size.toInt();
    //Устанавливаем новое количество строк
    matrixTable->setRowCount(n);
    //Устанавливаем новое количество строк
    matrixTable->setColumnCount(n);
}

void TInterface::formRequest()
{
    QString msg;
    //Добавляем размер матрицы в запрос
    msg << matrixSizeField->text();

    //Добавляем элементы матрицы в запрос
    for (int i = 0; i < matrixSizeField->text().toInt(); i++) {
        for (int j = 0; j < matrixSizeField->text().toInt(); j++) {
            QTableWidgetItem *item = matrixTable->item(i,j);
            if (NULL != item) {
                QString s = item->text();
                QStringList nums = s.split("/");
                if(nums.length() >= 1){
                    msg << s;
                } else {
                    msg<<"0/1";
                }
            }
        }
    }

    QPushButton *btn = (QPushButton*)sender();
    //В зависимости от нажатой кнопки регистрируем нужный нам запрос, добавляя числовое значение запроса
    if (btn == transposeButton)
    {
        msg << QString().setNum(PRINT_TRANSPOSE_REQUEST);
    }
    if (btn == determinantButton)
        msg << QString().setNum(PRINT_DETERMINANT_REQUEST);

    if (btn == rankButton) {
        msg << QString().setNum(PRINT_RANK_REQUEST);
    }
    emit request(msg);
}

void TInterface::answer(QString msg)
{
    QString text;
    QStringList response = msg.split(separator);
    //Удаляем пустые значения
    response.removeAll("");
    //Получаем числовое значение запроса
    int query = response.last().toInt();
    //Удаляем последнее значение - число запроса
    response.removeLast();
    switch (query)
    {
    case PRINT_TRANSPOSE_RESPONSE: {
        outputValue->setVisible(false);
        martixOutput->setVisible(true);

        int size = response.first().toInt();
        response.removeFirst();
        //Инициализируем выходную матрицу данными, которые пришли нам в ответ от server
        martixOutput->setRowCount(size);
        martixOutput->setColumnCount(size);
        for (int row = 0; row < size; row++) {
            for (int column = 0; column < size; column++) {
                 QTableWidgetItem *item = martixOutput->item(row, column);
                if(!item) {
                     item = new QTableWidgetItem();
                     item->setText(response[row*size+column]);
                     martixOutput->setItem(row, column, item);
                }

            }
        }
        return;
    }
    case PRINT_RANK_RESPONSE: {
        text += response.first();
        outputValue->setText(text);
        outputValue->setVisible(true);
        martixOutput->setVisible(false);
        return;
    }
    case PRINT_DETERMINANT_RESPONSE: {
        text += response.first();
        outputValue->setText(text);
        outputValue->setVisible(true);
        martixOutput->setVisible(false);
        return;
    }
    }
}
