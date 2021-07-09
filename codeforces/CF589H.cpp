/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm: 
**************************************************************/
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define IINF 0x3f3f3f3f

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

const long long maxN = 90;
long long totN;
long long totM;
long long totK;
long long Ks[maxN];
long long fath[maxN];
bool pip[maxN];
long long couple[maxN];
long long inK[maxN];
long long totANS;
long long depth[maxN];
long long FA[maxN];

struct Edge
{
    long long nxt;
    long long to;
} edges[maxN];
long long cnt_edges;
long long head[maxN];
void add_edge(long long x, long long y)
{
    ++cnt_edges;
    edges[cnt_edges].nxt = head[x];
    head[x] = cnt_edges;
    edges[cnt_edges].to = y;
}

long long getfa(long long x)
{
    if (x == fath[x])
    {
        return x;
    }
    else
    {
        return fath[x] = getfa(fath[x]);
    }
}

void getpath(long long x, long long y)
{
    long long Apath[maxN], Bpath[maxN];
    long long Alen = 0, Blen = 0;
    while (x != y)
    {
        if (depth[x] > depth[y])
        {
            ++Alen;
            Apath[Alen] = x;
            x = FA[x];
        }
        else
        {
            ++Blen;
            Bpath[Blen] = y;
            y = FA[y];
        }
    }
    ++Alen;
    Apath[Alen] = x;
    write(Alen + Blen - 1);
    putchar(' ');
    for (int i = 1; i <= Alen; ++i)
    {
        write(Apath[i]);
        putchar(' ');
    }
    for (int i = Blen; i >= 1; --i)
    {
        write(Bpath[i]);
        putchar(' ');
    }
    putchar('\n');
}

void DFS(long long x, long long fa)
{
    if (pip[x])
    {
        couple[x] = x;
    }
    for (int i = head[x]; i; i = edges[i].nxt)
    {
        long long vir = edges[i].to;
        if (vir == fa)
        {
            continue;
        }
        depth[vir] = depth[x] + 1;
        FA[vir] = x;
        DFS(vir, x);
        if (!couple[vir])
        {
            continue;
        }
        if (!couple[x])
        {
            couple[x] = couple[vir];
        }
        else
        {
            getpath(couple[x], couple[vir]);
            couple[x] =  0;
        }
    }
}

int main()
{
    totN = read();
    totM = read();
    totK = read();
    for (int i = 1; i <= totN; ++i)
    {
        fath[i] = i;
    }
    for (int i = 1, x, y; i <= totM; ++i)
    {
        x = read();
        y = read();
        if (getfa(x) == getfa(y))
        {
            continue;
        }
        add_edge(x, y);
        add_edge(y, x);
        fath[getfa(x)] = getfa(y);
    }
    for (int i = 1, k; i <= totK; ++i)
    {
        k = read();
        ++inK[getfa(k)];
        pip[k] = 1;
    }
    for (int i = 1; i <= totN; ++i)
    {
        if (fath[i] == i)
        {
            totANS += inK[i] / 2;
        }
    }
    write(totANS);
    putchar('\n');
    for (int i = 1; i <= totN; ++i)
    {
        if (fath[i] == i)
        {
            DFS(i, 0);
        }
    }
    return 0;
} //Thomitics Code