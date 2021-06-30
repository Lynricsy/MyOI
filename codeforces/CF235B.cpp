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

const long long maxN = 100090;
long double X1[maxN];
long double X2[maxN];
long double ANS[maxN];
long double P[maxN];
long long totN;

int main()
{
    totN = read();
    for (int i = 1; i <= totN; i++)
    {
        scanf("%Lf", &P[i]);
    }
    for (int i = 1; i <= totN; ++i)
    {
        X1[i] = P[i] * (X1[i - 1] + 1);
        X2[i] = X2[i - 1] + P[i] * (2 * X1[i - 1] + 1);
    }
    printf("%.15LF", X2[totN]);
    return 0;
} //Thomitics Code