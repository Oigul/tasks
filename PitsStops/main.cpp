#include <iostream>

void printArray(double *array, const int n);
void initializationArray(double *array, const int n);
void initializationIntervals(double *array, double *pitstops, const int n);
void sorting(double *array, const int n);
double searchMax(double *pitstops, const int n, int dist);

int main()
{

//    const int n = 4;
//    double pitstops[n] = {4.5, 0.5, 2, 1};
//    int dist = 5;

    int dist=0;
    std::cout << "enter tracker length " << std::endl;
    std::cin >> dist;
    while (dist <= 0)
    {
        std::cout << "tracker length must be greater than 0 " << std::endl;
        std::cin >> dist;
    }

    int n=0;
    std::cout << "enter the number of pit stops " << std::endl;
    std::cin >> n;
    while (n <= 0)
    {
        std::cout << "the number of pit stops must be greater than 0 " << std::endl;
        std::cin >> n;
    }

    double pitstops[n];
    std::cout << "enter coordinates of pit stops  " << std::endl;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> pitstops[i];
        while(pitstops[i] < 0 || pitstops[i] >= dist)
        {
            std::cout << "enter a coordinate greater than 0 and less than " << dist << std::endl;
            std::cin >> pitstops[i];
        }
    }

    sorting(pitstops, n);
    printArray(pitstops, n);

    double maxIntervals = searchMax(pitstops, n, dist);

    std::cout << "maximum possible distance to the nearest pit stop  = "
              << maxIntervals << std::endl;

    return 0;
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

void initializationArray(double *array, const int n)
{
    for (int i = 0; i < n; ++i)
    {
        array[i] = 0;
    }
}

void initializationIntervals(double *intervals, double *pitstops, const int n)
{
    for (int i = 0; i < n-1; ++i)
    {
        intervals[i] = pitstops[i+1] - pitstops[i];
    }
    //std::cout << std::endl;
}

double searchMax(double *pitstops, const int n, int dist)
{
    if (n>1)
    {
        double intervals[n-1];
        initializationIntervals(intervals, pitstops, n);

        double max = intervals[0];
        for (int i = 1; i < n; ++i)
        {
            if(intervals[i] > max)
                max = intervals[i];
        }

        return max/2;
    }
    else
    {
        if (dist - pitstops[0] > pitstops[0])
        {
            return (dist - pitstops[0])/2;
        }
        else
        {
            return pitstops[0]/2;
        }
    }
}

void sorting(double *array, const int n)
{
    //cout << "sorting" << endl;
    for(int j = 1; j<n; ++j)
    {
        double key = array[j];
        int i = j-1;

        while(i>=0 && array[i]>key)
        {
            array[i+1] = array[i];
            --i;
        }
        array[i+1] = key;
    }
}
