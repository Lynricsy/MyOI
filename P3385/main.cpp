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

int totT;
int totN;
int totM;
struct Edge
{
    int to;
    int nxt;
    int value;
}edges[100090];
int head[100090];
int cnt_edges;
queue<int> Q;
long long dis[100090];
int updated[100090];
bool vis[100090];

void add_edge(int x,int y,int w)
{
    if (w<0)
    {
        cnt_edges++;
        edges[cnt_edges].nxt=head[x];
        head[x]=cnt_edges;
        edges[cnt_edges].to=y;
        edges[cnt_edges].value=w;
    } else
    {
        cnt_edges++;
        edges[cnt_edges].nxt=head[x];
        head[x]=cnt_edges;
        edges[cnt_edges].to=y;
        edges[cnt_edges].value=w;
        cnt_edges++;
        edges[cnt_edges].nxt=head[y];
        head[y]=cnt_edges;
        edges[cnt_edges].to=x;
        edges[cnt_edges].value=w;
    }
}

void clear(queue<int> & q)
{
    queue<int> empty;
    swap(empty, q);
}

void SPFA()
{
    //clear(Q);
    while (!Q.empty())
    {
        Q.pop();
    }
    memset(updated,0,sizeof(updated));
    memset(vis,0,sizeof(vis));
    Q.push(1);
    dis[1]=0;
    vis[1]=true;
    while (!Q.empty())
    {
        int x=Q.front();
        vis[x]=false;
        Q.pop();
        for (int i = head[x]; i ; i=edges[i].nxt)
        {
            if (dis[edges[i].to]>dis[x]+edges[i].value)
            {
                dis[edges[i].to]=dis[x]+edges[i].value;
                if (!vis[edges[i].to])
                {
                    Q.push(edges[i].to);
                    vis[edges[i].to]=true;
                    updated[edges[i].to]++;
                    if (updated[edges[i].to]>=totN)
                    {
                        putchar('Y');
                        putchar('E');
                        putchar('S');
                        putchar('\n');
                        return;
                    }
                }
            }
        }
    }
    putchar('N');
    putchar('O');
    putchar('\n');
}

int main()
{
    totT=read();
    while (totT--)
    {
        memset(head,0,sizeof(head));
        memset(edges,0,sizeof(edges));
        totN=read();
        totM=read();
        for (int i = 1; i <= totN; ++i)
        {
            dis[i]=0x3f3f3f3f;
        }
        for (int i = 1; i <= totM; ++i)
        {
            int tempx=read();
            int tempy=read();
            int tempw=read();
            add_edge(tempx,tempy,tempw);
        }
        SPFA();
    }

    return 0;
}//LikiBlaze Code