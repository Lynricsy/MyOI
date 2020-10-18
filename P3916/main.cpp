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
int head[100090];
struct Edge
{
    int nxt;
    int to;
}edges[100090];
int cnt_edges;
bool dfsed[100090];
int max_to[100090];

void add_edges(int x,int y)
{
    cnt_edges++;
    edges[cnt_edges].nxt=head[x];
    head[x]=cnt_edges;
    edges[cnt_edges].to=y;
}

void DFS(int nowx)
{
    dfsed[nowx]=true;
    for (int i = head[nowx]; i ; i=edges[i].nxt)
    {
        if (!dfsed[edges[i].to])
        {
            DFS(edges[i].to);
        }
        max_to[nowx]=max(max_to[nowx],max_to[edges[i].to]);
    }
}
/*
int main()
{
    totN = read();
    totM = read();
    for (int i = 1; i <= totM; ++i)
    {
        int x=read();
        int y=read();
        add_edges(x,y);
    }
    for (int i = 1; i <= totN; ++i)
    {
        max_to[i]=i;
    }
    for (int i = 1; i <= totN; ++i)
    {
        if (!dfsed[i])
        {
            DFS(i);
        }
    }
    for (int i = 1; i <= totN; ++i)
    {
        write(max_to[i]);
        putchar(' ');
    }
    return 0;
}//LikiBlaze Code
*/
const int N = 100010, M = 1000010;
int ver[M], Next[M], Head[N], dfn[N], low[N];
int stacking[N], ins[N], c[N];
vector<int> scc[N];
int n, m, tot, num, top, cnt;
int now_node_max;

void add(int x, int y)
{
    ver[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}

void tarjan(int x)
{
    dfn[x] = low[x] = ++num;
    stacking[++top] = x, ins[x] = 1;
    for (int i = Head[x]; i; i = Next[i])
        if (!dfn[ver[i]])
        {
            tarjan(ver[i]);
            low[x] = min(low[x], low[ver[i]]);
        }
        else if (ins[ver[i]])
            low[x] = min(low[x], dfn[ver[i]]);
    if (dfn[x] == low[x])
    {
        cnt++;
        int y;
        now_node_max=-1;
        do
        {
            y = stacking[top--], ins[y] = 0;
            now_node_max=max(now_node_max,y);
            c[y] = cnt, scc[cnt].push_back(y);
        } while (x != y);
        max_to[cnt]=now_node_max;
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    for (int x = 1; x <= n; x++)
    {
        for (int i = Head[x]; i; i = Next[i])
        {
            int y = ver[i];
            if (c[x] == c[y])
                continue;
            add_edges(c[x], c[y]);
        }
    }
    for (int i = 1; i <= cnt; ++i)
    {
        if (!dfsed[i])
        {
            DFS(i);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        write(max_to[c[i]]);
        putchar(' ');
    }
    return 0;
}