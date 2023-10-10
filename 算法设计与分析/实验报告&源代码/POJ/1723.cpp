#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int n, x[10001], y[10001];
    cin >> n;
    for (int i = 0; i < n; i++)
        scanf("%d%d", &x[i], &y[i]);
    sort(x, x + n);
    sort(y, y + n);
    for (int i = 0; i < n; i++)
        x[i] -= i;
    sort(x, x + n);
    int s = 0;
    for (int i = 0; i < n / 2; i++)
        s += x[n - 1 - i] - x[i] + y[n - 1 - i] - y[i];
    cout << s <<endl ;
    return 0;
}