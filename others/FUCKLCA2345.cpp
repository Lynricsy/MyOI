#include <bits/stdc++.h>

using namespace std;

inline long long read()
{
    long long x = 0;
    int f = 1;
    char ch = getchar();
    while (ch < '0' || ch>'9')
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
void write(const long long& x)
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
    double x=0,t=0;
    int s=0,f=1;
    char c=getchar();
    for (;!isdigit(c);c=getchar())
    {
        if (c=='-')
        {
            f=-1;
        }
        if (c=='.')
        {
            goto readt;
        }
    }
    for (;isdigit(c)&&c!='.';c=getchar())
    {
        x=x*10+c-'0';
    }
    readt:
    for (;c=='.';c=getchar());
    for (;isdigit(c);c=getchar())
    {
        t=t*10+c-'0';
        ++s;
    }
    r=(x+t/pow(10,s))*f;
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
inline void write(double x,int k)
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
    if (x < 0) putchar('-'), x = -x;
    long long y = (long long) (x * n) % n;
    x = (long long) x;
    dwrite(x), putchar('.');
    int bit[10], p = 0, i;
    for (; p < k; y /= 10) 
        bit[++p] = y % 10;
    for (i = p; i > 0; i--) 
        putchar(bit[i] + 48);
}

long long totN;
long long rot;
long long totQ;
long long fath[1000090][33];
struct Edge
{
    long long nxt;
    long long to;
}edges[1000090];
long long cnt_edges;
long long head[1000090];
long long deepth[1000090];
int lg[1000090];
void add_edge(long long a,long long b)
{
    ++cnt_edges;
    edges[cnt_edges].nxt=head[a];
    head[a]=cnt_edges;
    edges[cnt_edges].to=b;
}
void DFS(long long nowX,long long fa)
{
    fath[nowX][0]=fa;
    deepth[nowX]=deepth[fa]+1;
    for (int i = 1; i <= lg[deepth[nowX]]; i++)
    {
        fath[nowX][i]=fath[fath[nowX][i-1]][i-1];
    }
    for (int i = head[nowX]; i ; i=edges[i].nxt)
    {
        if(edges[i].to==fa)
        {
            continue;
        }
        DFS(edges[i].to,nowX);
    }
}

long long LCA(long long x,long long y)
{
    if(deepth[x]<deepth[y])
    {
        swap(x,y);
    }
    while (deepth[x]>deepth[y])
    {
        x=fath[x][lg[deepth[x]-deepth[y]]-1];
    }
    if (x==y)
    {
        return y;
    }
    for (int i = lg[deepth[x]] - 1; i >= 0; --i)
    {
        if (fath[x][i]!=fath[y][i])
        {
            x=fath[x][i];
            y=fath[y][i];
        }
    }
    return fath[x][0];
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
    for(int i = 1; i <= totN; ++i)
    {
        lg[i] = lg[i-1] + (1 << lg[i-1] == i); 
    }
    DFS(rot,0);
    for (int i = 1; i <= totQ; i++)
    {
        int x,y;
        x=read();
        y=read();
        write(LCA(x,y));
        putchar('\n');
    }
    return 0;
}//LikiBlaze Code
