#include <QCoreApplication>

#include <iostream>
#include <vector>

//#define N 3 //ряды
//#define M 4 //столбцы

//проверки на 0
//найти деретминат и убедиться, что не вырожденная матрица

void printMatrix(std::vector<std::vector<double>> matrix, const int N, const int M);
void initMatrix(std::vector<std::vector<double> > &matrix, const int N, const int M);
void enteringEquation(std::vector<std::vector<double> >& matrix, const int N, const int M);
//void printEquation(std::vector<std::vector<double> >& matrix, const int N, const int M);
double forwardStroke(std::vector<std::vector<double> >& matrix, const int N, const int M);
void reverse(std::vector<std::vector<double> >& matrix, const int N, const int M, double* array, int size);
void columnReverse(std::vector<std::vector<double> >& matrix, const int N, const int M, int i1, int i2);
bool check(std::vector<std::vector<double> >& matrix, const int N, const int M, double* solutionEquation, int size);

void initArray(double* array, int size);
void printArray(double* array, int size);
void printSolution(double* array, int size);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int N = 0;
    std::cout << "Enter the number of equations" << std::endl;
    while (N==0)
        std::cin >> N;
    int M = N+1;

    std::vector<std::vector<double>> matrix;
    initMatrix(matrix, N, M);
    enteringEquation(matrix, N, M);
    //printEquation(matrix, N, M);
    printMatrix(matrix, N, M);

    int size = M-1;
    double solutionEquation[size];
    if (forwardStroke(matrix, N, M))
    {
        reverse(matrix, N, M, solutionEquation, size);
        //printArray(solutionEquation, size);
        printSolution(solutionEquation, size);
    }
    else
    {
        std::cout << "Systems of equations with a degenerate matrix of coefficients :c" << std::endl;
    }

    //не работает из-за округления
//    if(check(matrix, solutionEquation, size))
//        std::cout << "true" << std::endl;
//    else
//        std::cout << "false" << std::endl;

    return a.exec();
}

double forwardStroke(std::vector<std::vector<double> > &matrix, const int N, const int M)
{
    double determinant = 1;

    int u = 0;
    for(int k = 0; k < N-1; ++k)
    {
//        std::cout << "k" << k << std::endl;
        //проверка, что строка не состоит вся из 0
        int j2 = u;
        int j3 = u;
        while(j2 < N-1)
        {
            ++j2;
            if(matrix[k][j2] == 0)
            {
                ++j3;
            }
        }

        if (matrix[k][u] == 0 && j2==j3) //матрица вырожденная, строка вся из 0
                return 0;
        else
            if (matrix[k][u] == 0)
            {
                //если не последняя строка
                if(k < N-1)
                {
                    //ищем следующую строку, которая не начинается с 0 в точку u
                    int i2 = k;
                    while(i2 < N)
                    {
                        if(matrix[i2][u] != 0)
                            break;
                        else
                            ++i2;
                    }
                    //если все = 0 - идем дальше
                    if(i2 == N)
                    {
                        continue;
                    }
                    else
                    {   //меняем местами с другой строкой у которой
                        if(matrix[i2][u])
                        {
                            determinant *= -1;
                            columnReverse(matrix, N, M, k, i2);
                            printMatrix(matrix, N, M);
                        }
                    }
                }
                else
                {
                    printMatrix(matrix, N, M);
                    break;
                }
            }

        //если u элемент не 0
        for(int i = 1+k; i < N; ++i)
        {
            double factor = -matrix[i][u]/matrix[k][u];
            //std::cout << factor << std::endl;
            for(int j = 0; j < M; ++j)
            {
                matrix[i][j] = matrix[k][j]*factor+matrix[i][j];
            }
        }
//        printMatrix(matrix);
        ++u;
    }

    for(int i = 0; i < N; ++i)
    {
        determinant *= matrix[i][i];
    }
    std::cout << std::endl << "determinant = " << determinant << std::endl;

    return determinant;
}

void columnReverse(std::vector<std::vector<double> >& matrix, const int N, const int M, int i1, int i2)
{
    std::cout << "columnReverse";
    for(int j = 0; j < M; ++j)
    {
        double value = matrix[i1][j];
        matrix[i1][j] = matrix[i2][j];
        matrix[i2][j] = value;
    }
}

void reverse(std::vector<std::vector<double> >& matrix, const int N, const int M, double *array, int size)
{
    int variable = size-1; //номер элемента массива, в котором хранится текущая искомая переменная
    initArray(array, size);
    array[variable] = 0; //чтобы искомая переменная не считалась в сумму

    for(int i = N-1; i >= 0; --i)
    {
        double rowSum = 0;
        for(int j = 0; j < size; ++j)
        {
            rowSum += matrix[i][j]*array[j];
        }
//        std::cout << std::endl << "variable = "<< variable << std::endl;
//        std::cout << std::endl << "rowSum = "<< rowSum << std::endl;
        array[variable] = (matrix[i][M-1] - rowSum)/matrix[i][variable];
//        std::cout << std::endl << array[variable] << std::endl;
        --variable;
        array[variable] = 0; //следующая искомая переменная
    }
}

void printMatrix(std::vector<std::vector<double> > matrix, const int N, const int M)
{
    std::cout << std::endl;
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < M; ++j)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void initMatrix(std::vector<std::vector<double> > &matrix, const int N, const int M)
{
    std::vector<double> row(M);
    for (int i = 0; i < N; ++i)
    {
        matrix.push_back(row); //3 ряда по 4
    }
}

void enteringEquation(std::vector<std::vector<double> >& matrix, const int N, const int M)
{
    /*int value;

    for(int i = 0; i < N; ++i)
    {
        auto  text
        {
            [](int i)
            {
                return ((i == 0) ? "first" : ((i == 1) ? "second" : "third"));
            }
        };
        std::cout << "input of coefficients of the " << text(i) << " equation" <<std::endl;

        for(int j = 0; j < M-1; ++j)
        {
            auto  textCoefficients
            {
                [](int j)
                {
                    return ((j == 0) ? "x" : ((j == 1) ? "y" : "z"));
                }
            };

            std::cout << "enter coefficient before " << textCoefficients(j) <<std::endl;
            std::cin >> value;
            matrix[i][j] = value;
        }

        std::cout << "enter the result of the equation " <<std::endl;
        std::cin >> value;
        matrix[i][M-1] = value;
    }*/

    int value;

    for(int i = 0; i < N; ++i)
    {

        std::cout << i << " input of coefficients " << std::endl;

        for(int j = 0; j < M-1; ++j)
        {
            std::cout << j << " enter coefficient " << std::endl;
            std::cin >> value;
            matrix[i][j] = value;
        }

        std::cout << "enter the result of the equation " <<std::endl;
        std::cin >> value;
        matrix[i][M-1] = value;
    }
}

void printEquation(std::vector<std::vector<double> > &matrix, const int N, const int M)
{
    std::cout << std::endl;

    auto  textCoefficients
    {
        [](int j)
        {
            return ((j == 0) ? "x" : ((j == 1) ? "y" : "z"));
        }
    };

    auto  textSign
    {
        [](int j)
        {
            return ((j == 2) ? "=" : "+" );
        }
    };

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < M-1; ++j)
        {
            std::cout << matrix[i][j] << textCoefficients(j) << textSign(j);
        }
        std::cout << matrix[i][M-1];
        std::cout << std::endl;
    }
}

void printSolution(double* array, int size)
{
    std::cout << std::endl << "solution of the equation:"<<std::endl;

    /*auto  textCoefficients
    {
        [](int j)
        {
            return ((j == 0) ? "x = " : ((j == 1) ? "y  = " : "z  = "));
        }
    };

    for(int i = 0; i < size; ++i)
    {

        std::cout << textCoefficients(i) << array[i] << std::endl;
    }*/

    for(int i = 0; i < size; ++i)
    {

        std::cout << array[i] << std::endl;
    }
}

void initArray(double* array, int size)
{
    for(int i = 0; i < size; ++i)
    {
        array[i] = 1;
    }
}

void printArray(double* array, int size)
{
    for(int i = 0; i < size; ++i)
    {
        std::cout << std::endl << array[i] << std::endl;
    }
}

bool check(std::vector<std::vector<double> >& matrix, const int N, const int M, double* solutionEquation, int size)
{
    double sum[size];

    for(int i = 0; i < N; ++i)
    {
        sum[i] = 0;
        for(int j = 0; j < M-1; ++j)
        {
            sum[i] += matrix[i][j]*solutionEquation[j];
        }
    }

    for(int i = 0; i < N; ++i)
    {
        if(sum[i] != matrix[i][M-1])
            return false;
    }
    return true;
}
