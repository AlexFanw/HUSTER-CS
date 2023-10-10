#include <iostream>
#define SIZE 101
 
using namespace std;
 
int a[SIZE][SIZE];
 
int MaxSubArray(int n, int* a)
{
    int max = 0;
    int b = 0;
    for (int i = 0; i < n; i++)
    {
        if (b > 0) b += a[i];
        else b = a[i];
        if (b > max) max = b;
    }
    return max;
}
 
int MaxSubMatrix(int m, int n)
{
    int i, j, k, sum;
    int max = 0;
    int b[SIZE];
    for (i = 0; i < m; i++)
    {
        for (k = 0; k < n; k++)
        {
            b[k] = 0;
        }
       

        for (j = i; j < m; j++)
        {

            for (k = 0; k < n; k++)
            {
                b[k] += a[j][k];
            }
            
            sum = MaxSubArray(k, b);
            if (sum > max)
            {
                max = sum;
            }
        }
    }
    return max;
}
 
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
        }
    }
    cout << MaxSubMatrix(n, n) << endl;

    return 0;
}