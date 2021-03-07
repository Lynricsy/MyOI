#include <bits/stdc++.h>

using namespace std;

inline long long read()
{
    long long x = 0;
    int f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
void write(const long long &x)
{
    if (!x)
    {
        putchar('0');
        return;
    }
    char f[100];
    long long tmp = x;
    if (tmp < 0)
    {
        tmp = -tmp;
        putchar('-');
    }
    long long s = 0;
    while (tmp > 0)
    {
        f[s++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while (s > 0)
    {
        putchar(f[--s]);
    }
}
inline double dread()
{
    double r;
    double x = 0, t = 0;
    int s = 0, f = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar())
    {
        if (c == '-')
        {
            f = -1;
        }
        if (c == '.')
        {
            goto readt;
        }
    }
    for (; isdigit(c) && c != '.'; c = getchar())
    {
        x = x * 10 + c - '0';
    }
readt:
    for (; c == '.'; c = getchar())
        ;
    for (; isdigit(c); c = getchar())
    {
        t = t * 10 + c - '0';
        ++s;
    }
    r = (x + t / pow(10, s)) * f;
    return r;
}

inline void dwrite(long long x)
{
    if (x == 0)
    {
        putchar(48);
        return;
    }
    int bit[20], p = 0, i;
    for (; x; x /= 10)
        bit[++p] = x % 10;
    for (i = p; i > 0; --i)
        putchar(bit[i] + 48);
}
inline void write(double x, int k)
{
    static int n = pow(10, k);
    if (x == 0)
    {
        putchar('0');
        putchar('.');
        for (int i = 1; i <= k; ++i)
            putchar('0');
        return;
    }
    if (x < 0)
        putchar('-'), x = -x;
    long long y = (long long)(x * n) % n;
    x = (long long)x;
    dwrite(x), putchar('.');
    int bit[10], p = 0, i;
    for (; p < k; y /= 10)
        bit[++p] = y % 10;
    for (i = p; i > 0; i--)
        putchar(bit[i] + 48);
}

long long totT, totN, totM, xx1, xx2, yy1, yy2, kk1, kk2;

long long Senta()
{
    long long xx = xx2 - xx1;
    if (xx < 0)
        xx *= -1;
    long long yy = yy2 - yy1;
    if (yy < 0)
        yy *= -1;
    return xx + yy;
}

int main()
{
    freopen("jump.in", "r", stdin);
    freopen("jump.out", "w", stdout);
    totT = read();
    while (totT--)
    {
        totN = read();
        totM = read();
        xx1 = read();
        xx2 = read();
        yy1 = read();
        yy2 = read();
        kk1 = read();
        kk2 = read();
        if (totN == 1 || totM == 1)
        {
            puts("YES");
            continue;
        }
        else if (kk1 == kk2 && kk1 == 0)
        {
            if (Senta() % 2 == 1)
                puts("NO");
            else
                puts("YES");
            continue;
        }
        else
        {
            if (kk1 >= kk2)
            {
                puts("NO");
            }
            else
            {
                puts("YES");
            }
            continue;
        }
    }
    return 0;
}