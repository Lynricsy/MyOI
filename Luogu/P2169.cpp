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

struct Edge
{
    long long to;
    long long nxt;
    long long val;
} edges[maxN * 2], SCCedges[maxN * 2];
struct Node
{
    long long ID;
    long long dis;
};

bool operator<(Node a, Node b)
{
    return a.dis > b.dis;
}

long long totN;
long long totM;
long long dfn[maxN];
long long low[maxN];
long long in_SCC[maxN];
long long DFScnt;
bool inSTACK[maxN];
stack<long long> S;
long long cnt_SCC;
long long DIS[maxN];
bool vis[maxN];
priority_queue<Node> Q;
long long totS;
long long totT;

long long head[maxN];
long long cnt_edges;
void add_edge(long long x, long long y, long long w)
{
    ++cnt_edges;
    edges[cnt_edges].nxt = head[x];
    head[x] = cnt_edges;
    edges[cnt_edges].to = y;
    edges[cnt_edges].val = w;
}

long long SCChead[maxN];
long long cnt_SCCedges;
void add_SCCedge(long long x, long long y, long long w)
{
    ++cnt_SCCedges;
    SCCedges[cnt_SCCedges].nxt = SCChead[x];
    SCChead[x] = cnt_SCCedges;
    SCCedges[cnt_SCCedges].to = y;
    SCCedges[cnt_SCCedges].val = w;
}

void tarjan(long long nowX)
{
    ++DFScnt;
    low[nowX] = dfn[nowX] = DFScnt;
    S.push(nowX);
    inSTACK[nowX] = true;
    for (long long i = head[nowX]; i; i = edges[i].nxt)
    {
        long long vir = edges[i].to;
        if (!dfn[vir])
        {
            tarjan(vir);
            low[nowX] = min(low[nowX], low[vir]);
        }
        else if (inSTACK[vir])
        {
            low[nowX] = min(low[nowX], dfn[vir]);
        }
    }
    if (dfn[nowX] == low[nowX])
    {
        ++cnt_SCC;
        in_SCC[nowX] = cnt_SCC;
        S.pop();
        inSTACK[nowX] = false;
        long long y = S.top();
        while (y != nowX)
        {
            S.pop();
            in_SCC[y] = cnt_SCC;
            inSTACK[y] = false;
            y = S.top();
        }
    }
}
void Dijstra()
{
    memset(DIS, 0x3f, sizeof DIS);
    DIS[1] = 0;
    vis[1] = true;
    Q.push({1, 0});
    while (!Q.empty())
    {
        long long nowX = Q.top().ID;
        for (int i = SCChead[nowX]; i; i = SCCedges[i].nxt)
        {
            long long w = SCCedges[i].val;
            long long vir = SCCedges[i].to;
            if (DIS[vir] >= DIS[nowX] + w)
            {
                DIS[vir] = DIS[nowX] + w;
                if (!vis[vir])
                {
                    Q.push({vir, DIS[vir]});
                }
            }
        }
    }
}

int main()
{
    totN = read();
    totM = read();
    for (long long i = 1, x, y, w; i <= totM; ++i)
    {
        x = read();
        y = read();
        w = read();
        add_edge(x, y, w);
    }
    for (int i = 1; i <= totN; ++i)
    {
        if (!dfn[i])
        {
            tarjan(i);
        }
    }
    for (long long i = 1; i <= totN; ++i)
    {
        for (long long j = head[i]; j; j = edges[i].nxt)
        {
            long long vir = edges[i].to;
            if (in_SCC[i] != in_SCC[vir])
            {
                add_SCCedge(in_SCC[i], in_SCC[vir], edges[i].val);
            }
        }
    }
    totS = in_SCC[1];
    totT = in_SCC[totN];
    Dijstra();
    write(DIS[totT]);
    return 0;
} //Thomitics Code