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
    int i_value;
    int prev;
    int to;
    int nxt;
}edges[100090],finaledges[100090];
int head[100090];
int cnt_edges;
bool nodetype[100090];
int fa[100090];
int cnt_finaledges;
int final_head[100090];
bool dfsed[100090];
int child_0[100090];
int child_1[100090];
const long long MOD=1e9+7;
long long totresult;
int ones;
int zeros;

bool operator<(Edge a,Edge b)
{
    return a.i_value<b.i_value;
}
long long ultra_quick_pow(long long num,long long mi)
{
    long long base=num;
    long long result=1;
    while (mi)
    {
        if (mi&1)
        {
            result=result*base%MOD;
        }
        mi>>=1;
        base=base*base%MOD;
    }
    return result;
}
void add_edge(int x,int y,int i)
{
    cnt_edges++;
    edges[cnt_edges].i_value=i;
    edges[cnt_edges].nxt=head[x];
    head[x]=cnt_edges;
    edges[cnt_edges].to=y;
    edges[cnt_edges].prev=x;
}
void add_final_edge(int x,int y,int i)
{
    cnt_finaledges++;
    finaledges[cnt_finaledges].i_value=i;
    finaledges[cnt_finaledges].nxt=final_head[x];
    final_head[x]=cnt_finaledges;
    finaledges[cnt_finaledges].to=y;
    finaledges[cnt_finaledges].prev=x;
    cnt_finaledges++;
    finaledges[cnt_finaledges].i_value=i;
    finaledges[cnt_finaledges].nxt=final_head[y];
    final_head[y]=cnt_finaledges;
    finaledges[cnt_finaledges].to=x;
    finaledges[cnt_finaledges].prev=y;
}
bool getbool()
{
    if (getchar()=='0')
    {
        getchar();
        return false;
    } else
    {
        getchar();
        return true;
    }
}
void Krulprework()
{
    for (int i = 1; i <= totN; ++i)
    {
        fa[i]=i;
    }
    sort(edges+1,edges+totM+1);
}
int getfa(int getting)
{
    if (getting=fa[getting])
    {
        return getting;
    } else
    {
        return fa[getting]=getfa(getting);
    }
}
void Krulskal()
{
    for (int i = 1; i <= totM; ++i)
    {
        if (getfa(edges[i].prev)==getfa(edges[i].to))
        {
            continue;
        } else
        {
            fa[fa[edges[i].prev]]=fa[edges[i].to];
            add_final_edge(edges[i].prev,edges[i].to,edges[i].i_value);
        }
    }
}
void DFS(int scanning)
{
    dfsed[scanning]=true;
    for (int i = final_head[scanning]; i ; i=finaledges[i].nxt)
    {
        if (!dfsed[finaledges[i].to])
        {
            DFS(finaledges[i].to);
            child_0[scanning]+=child_0[finaledges[i].to];
            child_1[scanning]+=child_1[finaledges[i].to];
        }
    }
}
void calc()
{
    for (int i = 1; i <= cnt_finaledges; ++i)
    {
        int u=finaledges[i].to;
        int v=finaledges[i].prev;
        long long powwed=ultra_quick_pow(2,finaledges[i].i_value);
        totresult+=(child_0[v]*(ones-child_1[v])%MOD)*powwed%MOD;
        totresult+=(child_1[v]*(zeros-child_0[v])%MOD)*powwed%MOD;
        totresult%=MOD;
    }
}

int main()
{
    totN=read();
    totM=read();
    for (int i = 1; i <= totN; ++i)
    {
        nodetype[i]=getbool();
        if (nodetype[i])
        {
            child_1[i]++;
            ones++;
        } else
        {
            child_0[i]++;
            zeros++;
        }
    }
    for (int i = 1; i <= totM; ++i)
    {
        int x=read();
        int y=read();
        add_edge(x,y,i);
    }
    Krulprework();
    Krulskal();
    DFS(1);
    calc();
    write(totresult);
    return 0;
}//LikiBlaze Code