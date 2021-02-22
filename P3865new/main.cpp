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
long long totQ;
int lg[100090];
int nums[100090];
int LLC;
int RES[100090][49];

void getLOG()
{
    for (int i = 1; i <= 100090; i++)
    {
        lg[i]=lg[i-1]+(1<<lg[i-1]==i);
    }
    for (int i = 1; i <= 100090; i++)
    {
        --lg[i];
    }

}
void PRE()
{
    for (int i = 1; i <= 21; i++)
    {
        for (int j = 1; i <= totN-(1<<i)+1; i++)
        {
            RES[j][i]=max(RES[j][i-1],RES[j+(1<<(i-1))][i-1]);
        }
    }
}
int query(int x,int y)
{
    int tmp=lg[y-x+1];
    return max(RES[x][tmp],RES[y-(1<<tmp)+1][tmp]);
}

int main()
{
    totN=read();
    totQ=read();
    for (int i = 1; i <= totN; i++)
    {
        RES[i][0]=read();
    }
    getLOG();
    PRE();
    for (int i = 1; i <= totQ; i++)
    {
        int x,y;
        x=read();
        y=read();
        write(query(x,y));
        putchar('\n');
    }
    return 0;
} //LikiBlaze Code