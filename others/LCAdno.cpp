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

const long long maxN=20;
long long totN;
long long totQ;
int rot;
int head[maxN];
int cnt_edges;
int lg[maxN];
struct Edge
{
    int nxt;
    int to;
}edges[maxN];
int deepth[maxN];
int fa[maxN][34];
void add_edge(int x,int y)
{
    ++cnt_edges;
    edges[cnt_edges].nxt=head[x];
    head[x]=cnt_edges;
    edges[cnt_edges].to=y;
}
void GetLog()
{
    for (int i = 1; i <= totN; i++)
    {
        lg[i]=lg[i-1]+(1<<lg[i-1]==i);
        //lg[i]=log(i)/log(2)+1;
    }
}
void DFS(int x,int fath)
{
    deepth[x]=deepth[fath]+1;
    fa[x][0]=fath;
    for (int i = 1; i <= 33; i++)
    {
        fa[x][i]=fa[fa[x][i-1]][i-1];
    }
    for (int i = head[x]; i ; i=edges[i].nxt)
    {
        if(edges[i].to==fath)
        {
            continue;
        }
        DFS(edges[i].to,x);
    }
}
int LCA(int x,int y)
{
    if(deepth[x]<deepth[y])
    {
        swap(x,y);
    }
    while (deepth[x]>deepth[y])
    {
        x=fa[x][lg[deepth[x]-deepth[y]]-1];
    }
    if (x==y)
    {
        return x;
    }
    for (int i = lg[deepth[x]] - 1; i >= 0; --i)
    {
        if(fa[x][i]!=fa[y][i])
        {
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

int main()
{
    totN=read();
    totQ=read();
    rot=read();
    for (int i = 1; i <= totN-1; i++)
    {
        int x=read();
        int y=read();
        add_edge(x,y);
        add_edge(y,x);
    }
    GetLog();
    DFS(rot,0);
    for (int i = 1; i <= totQ; i++)
    {
        int x=read();
        int y=read();
        write(LCA(x,y));
        putchar('\n');
    }
    return 0;
} //LikiBlaze Code