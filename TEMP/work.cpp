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
long long totT;
long long totM;

struct Edge
{
    int nxt;
    int to;
    bool w;
}edges[100090],SCC_edges[100090];
int head[100090];
queue<int> Q;
bool inQ[100090];
int cnt_edges;
int cnt_SCC_edges;
int SCC_head[100090];
int dfs_cnt;
int dfn[100090];
int low[100090];
int inSCC[100090];
int cntSCC;
void add_edge(int x,int y,int z)
{
    ++cnt_edges;
    edges[cnt_edges].nxt=head[x];
    head[x]=cnt_edges;
    edges[cnt_edges].to=y;
    edges[cnt_edges].w=z;
}
void add_SCC_edge(int x,int y,int z)
{
    ++cnt_SCC_edges;
    SCC_edges[cnt_SCC_edges].nxt=SCC_head[x];
    SCC_head[x]=cnt_SCC_edges;
    SCC_edges[cnt_SCC_edges].to=y;
    SCC_edges[cnt_SCC_edges].w=z;
}
void Tarjan(int nowX)
{
    ++dfs_cnt;
    dfn[nowX]=low[nowX]=dfs_cnt;
    inQ[nowX]=1;
    Q.push(nowX);
    for(int i=head[nowX]; i ; i=edges[i].nxt)
    {
        if(!dfn[edges[i].to])
        {
            Tarjan(edges[i].to);
            low[nowX]=min(low[nowX],(int)low[edges[i].to]);
        }
        else if(inQ[edges[i].to])
        {
            low[nowX]=min(low[nowX],(int)dfn[edges[i].to]);
        }
    }
    if(dfn[nowX]==low[nowX])
    {
        ++cntSCC;
        int y=-1;
        while(y!=nowX)
        {
            y=Q.front();
            Q.pop();
            inSCC[nowX]=cntSCC;
        }
    }
}

int main()
{
    totT = read();
    for (int i = 1,x,y,z; i <= totM; ++i)
    {
        x=read();
        y=read();
        z=read();
        if(!z)
        {
            add_edge(x,y,z);
        }
        if (z)
        {
            add_edge(x,y,z);
            add_edge(y,x,z);
        }
    }
    for (int i = 1; i <= totN; i++)
    {
        if(!dfn[i])
        {
            Tarjan(i);
        }
    }
    
    return 0;
} //Thomitics Code