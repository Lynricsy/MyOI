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
long long S[100090];
struct Edge
{
    int nxt;
    int to;
} edges[100090];
int cnt_edges;
int head[100090];
long long H[100090];
int pres[100090];
int MMM;
long long maxH;
long long ppp[100090];
void add_edge(int x, int y)
{
    ++cnt_edges;
    edges[cnt_edges].nxt = head[x];
    head[x] = cnt_edges;
    edges[cnt_edges].to = y;
}

int main()
{
    totN = read();
    for (int i = 1; i <= totN; ++i)
    {
        S[i] = read();
    }
    int x, y;
    x = read();
    y = read();
    while (x && y)
    {
        add_edge(y, x);
        x = read();
        y = read();
    }
    for (int i = 1; i <= totN; ++i)
    {
        H[i] = S[i];
    }
    long long maxS = 0;
    for (int i = 1; i <= totN; i++)
    {
        maxS=0;
        for (int j = head[i]; j; j = edges[j].nxt)
        {
            if (S[edges[j].to] > maxS)
            {
                pres[i] = edges[i].to;
                maxS = S[edges[j].to];
            }
        }
        H[i] += maxS;
    }
    for (int i = 1; i <= totN; ++i)
    {
        if (H[i] > maxH)
        {
            MMM = i;
            maxH = H[i];
        }
    }
    int ii = 0;
    while (pres[MMM] != 0)
    {
        ppp[ii] = MMM;
        MMM = pres[MMM];
        ++ii;
    }
    for (int i = ii - 1; i >= 0; i--)
    {
        write(ppp[i]);
        if(i!=0)
        {
            putchar('-');
        }
    }
    write(maxH);
    putchar('\n');
    return 0;
} //LikiBlaze Code