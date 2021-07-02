#include <bits/stdc++.h>
#define INF 999999999

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

long long totN;
long long totM;
long long totA;
long long totB;
long long DP[190][190];

int main()
{
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
    totN = read();
    totM = read();
    totA = read() + 1;
    totB = read() + 1;
    DP[1][0] = 1;
    for (int i = 1; i <= totN + 1; ++i)
    {
        for (int j = 1; j <= totM + 1; ++j)
        {
            if ((i == totA && j == totB) || (i == totA - 1 && j == totB + 2) || (i == totA - 1 && j == totB - 2) || (i == totA - 2 && j == totB - 1) || (i == totA - 2 && j == totB + 1) || (i == totA + 1 && j == totB + 2) || (i == totA + 1 && j == totB - 2) || (i == totA + 2 && j == totB + 1) || (i == totA + 2 && j == totB - 1))
            {
                DP[i][j] = 0;
            }
            else
            {
                DP[i][j] = DP[i - 1][j] + DP[i][j - 1];
            }
        }
    }
    write(DP[totN + 1][totM + 1]);
    return 0;
} //Thomitics Code
