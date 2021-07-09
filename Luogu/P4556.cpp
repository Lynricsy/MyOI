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

const long long maxN = 100090;
long long totN;
long long totM;
long long siz[maxN];
long long depth[maxN];
long long ID[maxN];
long long top[maxN];
long long Sson[maxN];
long long fath[maxN];

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

void DFS1(long long x, long long fa, long long dep)
{
    depth[x] = dep;
    fath[x] = fa;
    siz[x] = 1;
    long long max = -1;
    for (int i = head[x]; i; i = edges[i].nxt)
    {
        long long vir = edges[i].to;
        if (vir == fa)
        {
            continue;
        }
        DFS1(vir, x, dep + 1);
        siz[x] += siz[vir];
        if (siz[vir] > max)
        {
            max = siz[vir];
            Sson[x] = vir;
        }
    }
}
void DFS2(long long x,long long nowTOP)
{
    top[x]=nowTOP;
    
}

int main()
{
    totN = read();
    totM = read();
    for (int i = 1, x, y; i < totN; ++i)
    {
        x = read();
        y = read();
        add_edge(x, y);
        add_edge(y, x);
    }

    return 0;
} //Thomitics Code