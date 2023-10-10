#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
 
const int N = 10000;
 
struct point
{
    int x, y;
};
 
int n;
point p[N];
int x[N], y[N];
int x1, x2, y1, y2;
set<int> table;
 
inline int f(int x, int y)
{
    return (x + 10000) * 100000 + (y + 10000);
}
 
inline bool find(int x, int y)
{
    return table.find(f(x, y)) != table.end();
}
 
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d", x + i, y + i);
        p[i].x = x[i];
        p[i].y = y[i];
        table.insert(f(x[i], y[i]));
    }
    sort(x, x + n);
    sort(y, y + n);
 
    int sum = 0, cnt = 0;
    if (n & 1)
    {
        x1 = x[n / 2];
        y1 = y[n / 2];
        if (find(x1, y1))
        {
            for (int i = 0; i < n; ++i)
            {
                sum += abs(x1 - x[i]);
                sum += abs(y1 - y[i]);
            }
            ++sum;
 
            x1 = x[n / 2 - 1];
            x2 = x[n / 2 + 1];
            for (int i = x1; i <= x2; ++i)
                if (!find(i, y1))
                    ++cnt;
 
            y1 = y[n / 2 - 1];
            y2 = y[n / 2 + 1];
            for (int i = y1; i <= y2; ++i)
                if (!find(x1, i))
                    ++cnt;
        }
        else
        {
            for (int i = 0; i < n; ++i)
            {
                sum += abs(x1 - x[i]);
                sum += abs(y1 - y[i]);
            }
            cnt = 1;
        }
    }
    else
    {
        x1 = x[n / 2 - 1];
        x2 = x[n / 2];
        y1 = y[n / 2 - 1];
        y2 = y[n / 2];
        cnt = (x2 - x1 + 1) * (y2 - y1 + 1);
        for (int i = 0; i < n; ++i)
        {
            sum += abs(x1 - x[i]);
            sum += abs(y1 - y[i]);
        }
        for (int i = 0; i < n; ++i)
        {
            if (p[i].x >= x1 && p[i].x <= x2 && p[i].y >= y1 && p[i].y <= y2)
                --cnt;
        }
    }
    printf("%d %d\n", sum, cnt);
    return 0;
}