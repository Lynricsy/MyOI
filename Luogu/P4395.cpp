/**************************************************************
 * Problem: Luogu P4395
 * Author: 芊枫
 * Date: 2021 July 04
 * Algorithm: 树上DP
**************************************************************/
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f

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
long long totN;

struct Edge
{
    long long to;
    long long nxt;
} edges[maxN];
long long cnt_edges;
long long head[maxN];
long long DP[maxN][20];
void add_edge(long long x, long long y)
{
    ++cnt_edges;
    edges[cnt_edges].nxt = head[x];
    head[x] = cnt_edges;
    edges[cnt_edges].to = y;
}

void DFS(long long nowX, long long fath)
{
    for (int i = head[nowX]; i; i = edges[i].nxt)
    {
        long long vir = edges[i].to;
        if (vir == fath)
        {
            continue;
        }
        DFS(vir, fath);
        for (int j = 1; j <= 15; ++j)
        {
            for (int k = 1; k <= 15; ++k)
            {
                if (j != k)
                {
                    DP[nowX][j] += DP[vir][k];
                }
            }

        }
    }
}

int main()
{
    totN = read();
    for (int i = 1, x, y; i <= totN; ++i)
    {
        x = read();
        y = read();
        add_edge(x, y);
        add_edge(y, x);
    }
    for (int i = 1; i <= totN; ++i)
    {
        for (int j = 1; j <= 15; ++j)
        {
            DP[i][j] = j;
        }
    }
    DFS(1, 0);
    return 0;
} //Thomitics Code