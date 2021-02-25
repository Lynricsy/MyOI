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
int totS;
struct Edge
{
    int nxt;
    int to;
    long long val;
}edges[300090];
long long dis[300090];
int head[300090];
struct Node
{
	long long dist;
	long long dot;
};
bool operator<(Node a,Node b)
{
	return a.dist>b.dist;
}
priority_queue<Node> Q;
int cnt_edges;
void add_edges(int x,int y,int z)
{
    ++cnt_edges;
    edges[cnt_edges].nxt=head[x];
    head[x]=cnt_edges;
    edges[cnt_edges].to=y;
    edges[cnt_edges].val=z;
}
bool Dvis[100090];
void Dijkstra()
{
    memset(Dvis,0,sizeof(Dvis));
    Q.push({0,totS});
    dis[totS]=0;
    while (!Q.empty())
    {
        int x=Q.top().dot;
        Q.pop();
        if(Dvis[x])
        {
        	continue;
		}
        Dvis[x]=1;
        for (int i = head[x]; i ; i=edges[i].nxt)
        {long long y=edges[i].to;
            if(dis[y]>dis[x]+edges[i].val)
            {
                dis[y]=dis[x]+edges[i].val;
                if(!Dvis[y])
                {
                    Q.push({dis[y],y});
                }
            }
        }
    }
}

int main()
{
    totN=read();
    totM=read();
    totS=read();
    for(int i=1;i<=totN;++i)
    {
    	dis[i]=0x7fffffff;
	}
    for (int i = 1,x,y,z; i <= totM; ++i)
    {
        x=read();
        y=read();
        z=read();
        add_edges(x,y,z);
    }
    Dijkstra();
    for (int i = 1; i <= totN; i++)
    {
        write(dis[i]);
        putchar(' ');
    }
    return 0;
}//LikiBlaze Code
