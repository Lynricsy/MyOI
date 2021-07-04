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
long long totM;
long long totN;
long long totK;
long long totQ;
long long totP;
long long totS;
long long totT;
struct Edge
{
    long long nxt;
    long long to;
    long long flow;
} edges[maxN * 4 + 90];
long long head[maxN * 4 + 90];
long long cnt_edges = 1;
long long DIS[maxN * 4 + 90];
long long now[maxN * 4 + 90];
long long totFLOW;
void add_edge(long long x, long long y, long long flow)
{
    ++cnt_edges;
    edges[cnt_edges].nxt = head[x];
    head[x] = cnt_edges;
    edges[cnt_edges].to = y;
    edges[cnt_edges].flow = flow;

    ++cnt_edges;
    edges[cnt_edges].nxt = head[y];
    head[y] = cnt_edges;
    edges[cnt_edges].to = x;
    edges[cnt_edges].flow = 0;
}

bool BFS()
{
    memset(DIS, 0x3f, sizeof DIS);
    queue<long long> Q;
    Q.push(totS);
    DIS[totS] = 0;
    now[totS] = head[totS];
    while (!Q.empty())
    {
        long long nowX = Q.front();
        Q.pop();
        for (int i = head[nowX]; i; i = edges[i].nxt)
        {
            long long vir = edges[i].to;
            if (DIS[vir] != INF || !edges[i].flow)
            {
                continue;
            }
            Q.push(vir);
            DIS[vir] = DIS[nowX] + 1;
            now[vir] = head[vir];
            if (vir == totT)
            {
                return true;
            }
        }
    }
    return false;
}

long long DFS(long long nowX, long long inFLOW)
{
    if (nowX == totT || !inFLOW)
    {
        return inFLOW;
    }
    long long nowOUT = 0;
    long long outFLOW = 0;
    for (int i = now[nowX]; i && inFLOW; i = edges[i].nxt)
    {
        now[nowX] = i;
        long long vir = edges[i].to;
        if ((DIS[vir] == DIS[nowX] + 1) && (edges[i].flow))
        {
            nowOUT = DFS(vir, min(edges[i].flow, inFLOW));
            if (!nowOUT)
                DIS[vir] = 0;
            edges[i].flow -= nowOUT;
            edges[i ^ 1].flow += nowOUT;
            outFLOW += nowOUT;
            inFLOW -= nowOUT;
        }
    }
    return outFLOW;
}

int main()
{
    totN = read();
    totP = read();
    totQ = read();
    totS = 0;
    totT = 4 * maxN + 1;
    for (int i = 1, x; i <= totN; ++i)
    {
        for (int j = 1; j <= totP; ++j)
        {
            x = read();
            if (x)
            {
                add_edge(j, i + maxN, 1);
            }
        }
    }
    for (int i = 1; i <= totP; i++)
    {
        add_edge(totS, i, 1);
    }
    for (int i = 1, x; i <= totN; ++i)
    {
        for (int j = 1; j <= totQ; ++j)
        {
            x = read();
            if (x)
            {
                add_edge(i + 2 * maxN, j + 3 * maxN, 1);
            }
        }
    }
    for (int i = 1; i <= totQ; i++)
    {
        add_edge(i + 3 * maxN, totT, 1);
    }
    for (int i = 1; i <= totN; ++i)
    {
        add_edge(i + maxN, i + maxN * 2, 1);
    }
    while (BFS())
    {
        totFLOW += DFS(totS, INF);
    }
    write(totFLOW);
    return 0;
} //Thomitics Code