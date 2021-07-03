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
long long totN;
long long totM;
struct Edge
{
    long long val;
    long long nxt;
    long long to;
    long long flow;
} edges[maxN];
long long cnt_edges;
long long head[maxN];
long long DIS[maxN];
void add_edge(long long x, long long y, long long w, long long flow)
{
    ++cnt_edges;
    edges[cnt_edges].nxt = head[x];
    head[x] = cnt_edges;
    edges[cnt_edges].to = y;
    edges[cnt_edges].val = w;
    edges[cnt_edges].flow = flow;

    ++cnt_edges;
    edges[cnt_edges].nxt = head[y];
    head[y] = cnt_edges;
    edges[cnt_edges].to = x;
    edges[cnt_edges].val = -w;
    edges[cnt_edges].flow = 0;
}

void SPFA()
{
}

int main()
{
    totN = read();
    totM = read();
    for (int i = 1, x, y, z; i <= totM; ++i)
    {
        x = read();
        y = read();
        z = read();
        add_edge(x, y, z, 1);
    }
    for (int i = 1; i <= totN; ++i)
    {
        add_edge(i, i + totN + 1, 0, 1);
    }

    return 0;
} //Thomitics Code