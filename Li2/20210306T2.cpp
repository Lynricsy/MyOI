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
long long totM;
long long totQ;
long long nowPL;
long long nowJ;
long long nowC;
long long maxJIE = 2;
long long JIE[1000090];
const long long MOD = 998244353;

long long Q[100090];
long long M[100090];

long long fact(long long x)
{
    if (x == 0 || x == 1)
    {
        return 1;
    }

    if (x <= maxJIE)
    {
        return JIE[x];
    }
    else
    {
        for (long long i = maxJIE; i <= x; ++i)
        {
            JIE[i] = (JIE[i - 1] * i) % MOD;
        }
        maxJIE = x;
        return x;
    }
}
long long suC(long long n, long long m)
{
    if (m == n)
    {
        return 1;
    }

    return (fact(n) / (fact(n - m) * fact(m)));
}

int main()
{
    freopen("plus.in","r",stdin);
    freopen("plus.out","w",stdout);
    JIE[0] = 1;
    JIE[1] = 1;
    JIE[2] = 2;
    totN = read();
    totQ = read();
    totM = read();
    for (int i = 1; i <= totQ; ++i)
    {
        Q[i] = read();
    }
    for (int i = 1; i <= totN; ++i)
    {
        M[i] = read();
    }
    for (int i = 1; i <= totM; ++i)
    {
        nowPL = read();
        nowJ = read();
        nowC = read();
        long long nowU = fact(Q[nowJ]);
        long long nowL = nowU;
        long long nowCNT = 0;
        for (int j = nowPL; j <= totN; ++j)
        {
            /*
            ++nowCNT;
            M[j] += (nowC * (nowL / nowU)) % MOD;
            M[j] %= MOD;
            nowL /= nowCNT;
            nowL *= (nowJ + nowCNT);
            */
            M[j] += nowC * suC(Q[nowJ] + j - nowPL, Q[nowJ]);
        }
    }
    for (long long i = 1; i <= totN; i++)
    {
        write(M[i]);
        putchar(' ');
    }
    return 0;
} //LikiBlaze Code
  /*
(m+a)!/(m!*a!)
*/