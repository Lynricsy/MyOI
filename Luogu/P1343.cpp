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
long long totM;
long long totX;
struct Edge
{
    int nxt;
    int to;
    int val;
} edges[100090];
int head[100090];
int cnt_edges;
int dis[100090];

void add_edges(int x, int y, int z)
{
    ++cnt_edges;
    edges[cnt_edges].nxt = head[x];
    head[x] = cnt_edges;
    edges[cnt_edges].to = y;
    edges[cnt_edges].val = z;
}
void BFS()
{
    memset(dis,-1,sizeof(dis));
    dis[1]=0;
    queue<int> Q;
    Q.push(1);
    while(!Q.empty())
    {
        int st=Q.front();
        Q.pop();
        for (int i = head[st]; i ; i=edges[i].nxt)
        {
            
        }
        
    }
}
int DFS(int u,int flows)
{
    if (u==totN)
    {
        return flows;
    }
    int delta=flows;
    for (int i = head[u]; i ; i=edges[i].nxt)
    {
        if(dis[edges[i].to]==(dis[u]+1)&&edges[i].val>0)
        {
            DFS(edges[i].to,min(flows,))
        }
    }
    
}

int main()
{
    totN = read();
    totM = read();
    totX = read();
    for (int i = 1; i <= totM; i++)
    {
        int x = read();
        int y = read();
        int z = read();
        add_edges(x, y, z);
        add_edges(y, x, 0);
    }
    
    return 0;
} //Thomitics Code