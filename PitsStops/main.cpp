#include <iostream>

using namespace std;

void printArray(double *array, const int n);
void initializationArray(double *array, const int n);
void initializationIntervals(double *array, double *pitstops, const int n);
void sorting(double *array, const int n);
double searchMax(double *array, const int n);

int main()
{
    //cout << "Hello World!" << endl;

    const int n = 4;
    double pitstops[n] = {4.5, 0.5, 2, 1};
    int dist = 5;

    sorting(pitstops, n);

    double intervals[n-1];
    initializationIntervals(intervals, pitstops, n);

    cout << "maximum possible distance to the nearest pit stop  = "
         << searchMax(intervals, n-1) << endl;

    return 0;
}

void printArray(double *array, const int n)
{
    //cout << "printArray" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

void initializationArray(double *array, const int n)
{
    for (int i = 0; i < n; ++i)
    {
        array[i] = 0;
    }
    cout << endl;
}

void initializationIntervals(double *intervals, double *pitstops, const int n)
{
    for (int i = 0; i < n-1; ++i)
    {
        intervals[i] = pitstops[i+1] - pitstops[i];
    }
    cout << endl;
}

double searchMax(double *array, const int n)
{
    double max = array[0];
    for (int i = 1; i < n; ++i)
    {
        if(array[i] > max)
            max = array[i];
    }
    return max;
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
