#include <QCoreApplication>
#include <QFileInfo>
#include <vector>
#include <QDebug>

#include <iostream>

//вопросы
//в if всегда -1 (41 строка)

int binarySearch(QFile& file, double requiredNumber, int begin, int finish);

int fun()
{
    std::cout << "\noigul test return 1234" << std::endl;
    return 1234;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString pathToFile = "C:\\trash\\dataset_sorted.csv";
    QFile file(pathToFile);

    double requiredNumber;
    std::cout << "enter the required number " << std::endl;
    std::cin >> requiredNumber;
    int requiredNumberIndex;
    int fileSize = 0;

    //oigul test
    int c;

    std::cout << std::endl << "expectation" << std::endl;
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        QString maxNumber;
        while (!file.atEnd())
        {
            maxNumber = file.readLine();
            ++fileSize;
        }
        //std::cout << "maxNumber =" << maxNumber.toStdString() << std::endl;
        std::cout << "fileSize =" << fileSize << std::endl;

        std::cout << std::endl << "expectation" << std::endl;
        file.close();

        if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
        {
            requiredNumberIndex = binarySearch(file, requiredNumber, 0, fileSize);
            std::cout << "requiredNumberIndex in if = " << requiredNumberIndex << std::endl;

            c = fun();
            std::cout << "oigul test c = " << c << std::endl;
        }

        if(requiredNumberIndex >= 0)
        {
            std::cout << "\nthere is the number in the array\n";
            std::cout << "requiredNumberIndex = " << requiredNumberIndex << " \n";
        }
        else
        {
            std::cout << "there is not the number in the array" << std::endl;
        }
    }

    return a.exec();
}

int binarySearch(QFile &file, double requiredNumber, int begin, int finish)
{
    int middle = (begin+finish)/2;
    static bool left = true;

    std::cout << "middleIndex " << middle;

    //переход на нужную строку
    if (left)
    {
        for(int i = 0; i < middle-1; ++i)
        {
            file.readLine();
        }
    }
    else
    {
        for(int i = begin; i <= middle-1; ++i)
        {
            QString forStr=file.readLine();
        }

    }

    //чтение средней строки и выделение из нее числа
    QString str=file.readLine();
    double middleValue;
    QString::iterator s = str.begin();
    while (*s == '.' || (*s >= '0' && *s <= '9'))
    {
        ++s;
    }
    while(s != str.end())
    {
        *s = ' ';
        ++s;
    }
    middleValue = str.toDouble();
    std::cout << " middleValue " << middleValue << std::endl;

    //сравнение среднего числа с искомым числом
    if (middleValue == requiredNumber)
    {
        std::cout << "return " << middle << " \n";
        return middle;
    }

    if (begin >= finish)
    {
        std::cout << "return -1" << " \n";
        return -1;
    }

    if (requiredNumber < middleValue)
    {
        left = true;
        file.close();
        if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
            binarySearch(file, requiredNumber, begin, middle-1);
    }
        else
    {
        left = false;
        binarySearch(file, requiredNumber, middle+1, finish);
    }
}
