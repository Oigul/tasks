#include <QCoreApplication>
#include <QFileInfo>
#include <QTextStream>

#include <iostream>
#include <random>
#include <vector>
#include <time.h>

void printArray(int *array, const int n);
void initArray(int *array, const int size);
void initVector(QFile &file, std::vector<int>& vector);
void writeArrayInFile(int *array, const int size, QFile &file);
void writeVectorInFile(std::vector<int> vector, QFile &file);
void insertionSort(QFile &file);
void mergeSort(QFile &file);
void mergeSort(std::vector<int> &vector, int left, int right);
std::string result(double timeInsertionSort, double timeMergeSort);
int searchMax(int *array, const int n);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    srand(static_cast<unsigned int>(time(0)));

    const int size = 2048;
    int array[size];
    initArray(array, size);

    QString pathToFileArray = "C:\\trash\\compareSortsArray.txt";
    QFile fileArray(pathToFileArray);
    writeArrayInFile(array, size, fileArray);

    double time1 = clock();
    insertionSort(fileArray);
    double time2 = clock();
    double timeInsertionSort = time2 - time1;

    time1 = clock();
    mergeSort(fileArray);
    time2 = clock();
    double timeMergeSort = time2 - time1;

    std::cout << result(timeInsertionSort, timeMergeSort) << std::endl;

    return a.exec();
}

void printArray(int *array, const int n)
{
    //cout << "printArray" << endl;
    for (int i = 0; i < n; ++i)
    {
        std::cout << array[i] << " ";
        if ((i+1) % 25 == 0)
            std::cout << "\n";
    }
    std::cout << std::endl;
}

void initArray(int *array, const int size)
{
    for (int i = 0; i < size; ++i)
    {
        array[i] = rand() % 100;
    }
}

void initVector(QFile &file, std::vector<int>& vector)
{
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString str = "1";
    while(!str.isNull())
    {
        str = in.readLine();
        if(!str.isNull())
            vector.push_back(str.toInt());
    }
    file.close();
}

void writeArrayInFile(int *array, const int size, QFile &file)
{
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    for (int i = 0; i < size; ++i)
    {
        stream << array[i] << "\n";
    }

    file.close();
}

void writeVectorInFile(std::vector<int> vector, QFile &file)
{
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    for (int i = 0; i < vector.size(); ++i)
    {
        stream << vector[i] << "\n";
    }

    file.close();
}

void printVector(std::vector<int> tmp, const int n)
{
    //std:cout << "printArray" << std:endl;
    for (int i = 0; i < n; ++i)
    {
        std::cout << tmp[i] << " ";
    }
    std::cout << std::endl;
}

std::string result(double timeInsertionSort, double timeMergeSort)
{
    if (timeMergeSort == timeInsertionSort)
        return "t insertion = t merge";
    if (timeMergeSort < timeInsertionSort)
    {
        return "Merge sort is faster than insert sort ";
    }
    else
        return "Insert sort is faster than merge sort";
}

int searchMax(int *array, const int n)
{
    double max = array[0];
    for (int i = 1; i < n; ++i)
    {
        if(array[i] > max)
            max = array[i];
    }
    return max;
}

void insertionSort(QFile &file)
{
    std::vector<int> vector;
    initVector(file, vector);

    //std::cout << "insertionSort" << std::endl;
    for (int j = 1; j < vector.size() ; ++j)
    {
        int key = vector[j];
        int i = j-1;

        while(i>=0 && vector[i]>key)
        {
            vector[i+1] = vector[i];
            --i;
        }
        vector[i+1] = key;
    }

    QString pathToFileInsertion = "C:\\trash\\compareSortsArrayInsertion.txt";
    QFile fileInsertion(pathToFileInsertion);
    writeVectorInFile(vector, fileInsertion);
}

void mergeSort(QFile &file)
{
    std::vector<int> vector;
    initVector(file, vector);
    mergeSort(vector, 0, vector.size());
    QString pathToFileMerge = "C:\\trash\\compareSortsArrayMerge.txt";
    QFile fileMerge(pathToFileMerge);
    writeVectorInFile(vector, fileMerge);
}

void mergeSort(std::vector<int>& vector, int left, int right)
{
    //std::cout << "mergeSort" << std::endl;

    if (left<right) //граничное условие
    {
        int middle = (left + right) / 2;
        mergeSort(vector, left, middle);
        mergeSort(vector, middle + 1, right);

        int n1 = middle - left + 1;
        int n2 = right - middle;
        std::vector<int> tmpLeft;
        std::vector<int> tmpRight;
        for(int i = 0; i < n1; ++i)
            tmpLeft.push_back(vector[left+i]);

        for(int i=0; i < n2; ++i)
            if(middle + i + 1 < vector.size())
                tmpRight.push_back(vector[middle+i+1]);

        /*int max = searchMax(array, n);
        tmpLeft.push_back(max+1);
        tmpRight.push_back(max+1);*/
        tmpLeft.push_back(100);
        tmpRight.push_back(100);

        int i = 0, j = 0;
        for(int k = left; k <= right; ++k)
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
