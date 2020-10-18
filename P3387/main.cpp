#ifdef ONLINE_JUDGE
#pragma GCC optimize(2)
#pragma GCC diagnostic error "-std=c++11"
#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(3)
#endif // ONLINE_JUDGE

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

int totN;
int totM;
struct Edge
{
    int pre;
    int to;
    int nxt;
}edges[100090],DCC_edges[100090];
int dcc_head[100090];
int head[100090];
int value[100090];
int cnt_edges;
int cnt_DCC_edges;
int dfn[100090];
int low[100090];
int dfscnt;
bool instack[100090];
stack<int> stacking;
int cnt_DCC;
stack<int> DCCs[100090];
int in_stacking[100090];
queue<int> topo_Q;
int inDegree[100090];
int toposo[100090];

void add_edge(int x,int y)
{
    cnt_edges++;
    edges[cnt_edges].nxt=head[x];
    head[x]=cnt_edges;
    edges[cnt_edges].to=y;
    edges[cnt_edges].pre=x;
}
void add_dcc_edges(int x,int y)
{
    cnt_DCC_edges++;
    DCC_edges[cnt_DCC_edges].nxt=dcc_head[x];
    dcc_head[x]=cnt_DCC_edges;
    DCC_edges[cnt_DCC_edges].to=y;
}

void tarjian(int x)
{
    dfn[x]=low[x]=++dfscnt;
    stacking.push(x);
    instack[x]= true;
    for (int i = head[x]; i ; i=edges[i].nxt)
    {
        if (!dfn[edges[i].to])
        {
            tarjian(edges[i].to);
            low[x]=min(low[x],low[edges[i].to]);
        } else if (instack[edges[i].to])
        {
            low[x]=min(dfn[edges[i].to],low[x]);
        }
    }
    if (dfn[x]==low[x])
    {
        cnt_DCC++;
        int y;
        do
        {
            y=stacking.top();
            instack[y]= false;
            in_stacking[y]=cnt_DCC;
            DCCs[cnt_DCC].push(y);
        }while (y!=x);
    }
}
void topo_sort()
{
    for (int i = 1; i <= cnt_DCC; ++i)
    {
        if (!inDegree[i])
        {
            topo_Q.push(i);
        }
    }
    while (!topo_Q.empty())
    {
        int nownode=topo_Q.front();
        for (int i = head[nownode]; i ; i=edges[i].nxt)
        {
            if (!inDegree[edges[i].to])
            {
                topo_Q.push()
            }
        }
    }
}

int main()
{
    totN=read();
    totM=read();
    for (int i = 1; i <= totN; ++i)
    {
        value[i]=read();
    }
    for (int i = 1; i <= totM; ++i)
    {
        int x=read();
        int y=read();
        add_edge(x,y);
    }
    for (int i = 1; i <= totN; ++i)
    {
        if (!dfn[i])
        {
            tarjian(i);
        }
    }
    for (int i = 1; i <= totM; ++i)
    {
        if (in_stacking[edges[i].pre]!=in_stacking[edges[i].to])
        {
            add_dcc_edges(in_stacking[edges[i].pre],in_stacking[edges[i].to]);
        }
    }
    for (int i = 1; i <= cnt_DCC_edges; ++i)
    {
        inDegree[DCC_edges[i].to]++;
    }
    return 0;
}//LikiBlaze Code