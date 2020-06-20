int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
int main()
{
    int a = 1, b = 2, c = 3, d = 4, m, n;
    int i;
    int x, y, z;
    x = read();
    y = read();
    z = max(x, y);
    write(z);

    m = 1;
    m = a + b;
    n = a + b - m * (c + d) * (c + d) + 2 * 3;
    while (a < b)
    {
        if (a * 2 < b)
            continue;
        for (c = 1; c < 10; c++)
            if (c < 5)
                continue;
            else
                break;
    }

    return 1;
}