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
char obj[109];
long long DP[109][12][12][12];

int main()
{
    totN = read();
    for (int i = 1; i <= totN; ++i)
    {
        obj[i] = getchar();
        getchar();
    }
    memset(DP, 0x3f, sizeof(DP));
    DP[0][0][0][0] = 0;
    for (int i = 1; i <= totN; ++i)
    {
        for (int j = 0; j <= 10; ++j)
        {
            for (int k = 0; k <= 10; ++k)
            {
                for (int l = 0; l <= 10; ++l)
                {
                    if (j + k + l > 10)
                    {
                        continue;
                    }
                    if (obj[i] == 'A' && j)
                    {
                        DP[i][j][k][l] = DP[i - 1][j - 1][k][l];
                    }
                    else if (obj[i] == 'B' && k)
                    {
                        DP[i][j][k][l] = DP[i - 1][j][k - 1][l];
                    }
                    else if (obj[i] == 'C' && l)
                    {
                        DP[i][j][k][l] = DP[i - 1][j][k][l - 1];
                    }
                    DP[i][0][k][l] = min(DP[i][0][k][l], DP[i][j][k][l] + 1);
                    DP[i][j][0][l] = min(DP[i][j][0][l], DP[i][j][k][l] + 1);
                    DP[i][j][k][0] = min(DP[i][j][k][0], DP[i][j][k][l] + 1);
                }
            }
        }
    }
    write(DP[totN][0][0][0]);
    return 0;
} //Thomitics Code