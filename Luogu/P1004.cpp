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

long long totN;
long long mapp[19][19];
long long DP[19][19][19][19];

int main()
{
    totN = read();
    int x, y, z;
    x = read();
    y = read();
    z = read();
    while (x && y && z)
    {
        mapp[x][y] = z;
        x = read();
        y = read();
        z = read();
    }
    int i, j, k, l;
    for (i = 1; i <= totN; i++)
    {
        for (j = 1; j <= totN; j++)
        {
            for (k = 1; k <= totN; k++)
            {
                l = i + j - k;
                if (l <= 0)
                    break;
                DP[i][j][k][l] = max(DP[i - 1][j][k - 1][l], max(DP[i - 1][j][k][l - 1], max(DP[i][j - 1][k - 1][l], DP[i][j - 1][k][l - 1])));
                if (i == k && j == l)
                    DP[i][j][k][l] += mapp[i][j];
                else
                    DP[i][j][k][l] += mapp[i][j] + mapp[k][l];
            }
        }
    }
    return 0;
} //Thomitics Code