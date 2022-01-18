#include <QCoreApplication>
#include <QFileInfo>
#include <vector>
#include <QDebug>

#include <iostream>

//вопросы
//всегда 1 передается в main (строка 39), даже если binarySearch передает другое число

int binarySearch(QTextStream &in, double requiredNumber, int begin, int finish);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString pathToFile = "C:\\trash\\dataset_sorted.csv";
    QFile file(pathToFile);

    int requiredNumberIndex;
    double requiredNumber;
    std::cout << "enter the required number " << std::endl;
    std::cin >> requiredNumber;

    int line_count = 0;
    QString maxLinesNumber;
    file.open(QIODevice::ReadOnly);

    QTextStream in(&file);
    maxLinesNumber = in.readLine();
    while(!maxLinesNumber.isNull())
    {
        line_count++;
        maxLinesNumber = in.readLine();
    }
    std::cout << "line_count = " << line_count << std::endl;

    in.seek(0);
    requiredNumberIndex = binarySearch(in, requiredNumber, 0, line_count-1);
    std::cout << "oigul!!! requiredNumberIndex = " << requiredNumberIndex << std::endl;
    file.close();

    if(requiredNumberIndex >= 0)
    {
        std::cout << "\nthere is the number in the array\n";
    }
    else
    {
        std::cout << "\nthere is not the number in the array" << std::endl;
    }

    return a.exec();
}

int binarySearch(QTextStream &in, double requiredNumber, int begin, int finish)
{
    static bool left = true;

    if (begin > finish)
    {
        std::cout << "oigul!!! return -1" << " \n";
        return -1;
    }

    int middle = (begin+finish)/2;
    std::cout <<"begin " << begin << " finish " << finish << " middleIndex " << middle;

    //переход на нужную строку
    if(left)
    {
        for(int i = 0; i < middle; ++i)
        {
            in.readLine();
        }
    }
    else
    {
        for(int i = begin; i < middle; ++i)
        {
            in.readLine();
        }
    }

    /*QString value = "";
    QString str = in.read(0);
    while(!str.isNull() && (str == '.' || (str >= '0' && str <= '9')))
    {
        value += str;
        str = in.read(0);
    }
    double middleValue = str.toDouble();
    std::cout << " middleValue " << middleValue << std::endl;*/

    //чтение средней строки и выделение из нее числа
    QString str = in.readLine();
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
    double middleValue;
    middleValue = str.toDouble();
    std::cout << " middleValue " << middleValue << std::endl;

    //сравнение среднего числа с искомым числом
    if (middleValue == requiredNumber)
    {
        std::cout << "oigul!!! return " << middle << " \n";
        return middle;
    }

    if (begin == finish)
    {
        std::cout << "oigul!!! return -1" << " \n";
        return -1;
    }

    if (requiredNumber < middleValue)
    {
        left = true;
        in.seek(0);
        binarySearch(in, requiredNumber, begin, middle-1);
    }
    else
    {
        left = false;
        binarySearch(in, requiredNumber, middle+1, finish);
    }
}
