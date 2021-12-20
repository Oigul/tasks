#include <QCoreApplication>
#include <QFileInfo>
#include <vector>
#include <QDebug>

#include <iostream>

//открыть большой файл

void mergeSort(std::vector<double> &vector, const int n, int left, int right);
int binarySearch(std::vector<double> &vector, const int n, double requiredNumber, int begin, int finish);

void printArray(double *array, const int n);
void mergeSort(double *array, const int n, int left, int right);
int binarySearch(double *array, const int n, double requiredNumber, int begin, int finish);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file("C:\\trash\\dataset_sorted.csv");
    //QFile file("C:\\trash\\list.csv");

    const int n = 9;
    //double values[n];
    std::vector<double> values;

    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        int j = 0;
        QString str=file.readLine();
        //for(int k = 0; k < n; ++k)
        while (!file.atEnd())
        {
            str=file.readLine();
            QString value="";
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
            //values[j] = str.toDouble();
            //std::cout << values[j] << std::endl;
            ++j;

            values.push_back(str.toDouble());
            std::cout << values[j] << std::endl;
            ///values.push_back(str.toDouble());
        }

        file.close();
    }

    std::cout << std::endl;
    //printArray(values, n);
    mergeSort(values, n, 0, n);
    std::cout << std::endl;
    //printArray(values, n);

    double requiredNumber;
    std::cout << std::endl << "enter the required number " << std::endl;
    std::cin >> requiredNumber;
    int requiredNumberIndex = binarySearch(values, n-1, requiredNumber, 0, n-1);

    if(requiredNumberIndex >= 0)
    {
        std::cout << "there is the number in the array" << " \n";
    }
    else
    {
        std::cout << "there is not the number in the array" << std::endl;
    }

    return a.exec();
}

void printArray(double *array, const int n)
{
    //cout << "printArray" << endl;
    for (int i = 0; i < n; ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void mergeSort(std::vector<double> &vector, const int n, int left, int right)
{
    //std::cout << "mergeSort" << std::endl;

    if (left<right) //граничное условие
    {
        int middle = (left+right)/2;
        mergeSort(vector, n, left, middle);
        mergeSort(vector, n, middle+1, right);

        int n1 = middle-left+1;
        int n2 = right-middle;
        std::vector<double> tmpLeft;
        std::vector<double> tmpRight;
        for(int i=0; i<n1; ++i)
            tmpLeft.push_back(vector[left+i]);

        for(int i=0; i<n2; ++i)
        {
            if(middle+i+1 < n)
                tmpRight.push_back(vector[middle+i+1]);
        }

        /*int max = searchMax(array, n);
        tmpLeft.push_back(max+1);
        tmpRight.push_back(max+1);*/
        tmpLeft.push_back(100);
        tmpRight.push_back(100);

        int i=0, j=0;
        for(int k = left; k<=right; ++k)
        {
            if(tmpLeft[i] <= tmpRight[j])
            {
                vector[k] = tmpLeft[i];
                ++i;
            } else
            {
                vector[k] = tmpRight[j];
                ++j;
            }
        }
    }
}

int binarySearch(std::vector<double> &vector, const int n, double requiredNumber, int begin, int finish)
{
    int middle = (begin+finish)/2;

    if (vector[middle] == requiredNumber)
    {
        return middle;
    }

    if (begin == finish)
    {
        return -1;
    }

    if (vector[middle] > requiredNumber)
        binarySearch(vector, n, requiredNumber, begin, middle-1);
    else
        binarySearch(vector, n, requiredNumber, middle+1, finish);
}
