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
void clearStack(stack<int> &s)
{
    stack<int>().swap(s);
}
void clearVector(vector<int> &s)
{
    vector<int>().swap(s);
}

int totN;
int totM;

struct Edge
{
	long long val;
	int nxt;
	int to;
}edges[100090];
int head[100090];
int cnt_edges;
int dfn[100090];
bool ins[100090];
vector<int> SCC;
stack<int> Sta;
int dfscnt;
int cntSCC;
int low[100090];

void add_edge(int x,int y,int z)
{
	cnt_edges++;
	edges[cnt_edges].nxt=head[x];
	head[x]=cnt_edges;
	edges[cnt_edges].to=y;
	edges[cnt_edges].val=z;
}

bool Tarjian(int nowX,int numm)
{
	dfn[nowX]=low[nowX]=++dfscnt;
	Sta.push(nowX);
	ins[nowX]=true;
	for(int i=head[nowX];i;i=edges[i].nxt)
	{
		if(edges[i].val>numm)
		{
			continue;
		}
		if(ins[edges[i].to])
		{
			low[nowX]=min(low[nowX],dfn[edges[i].to]);
		}
		else if(!dfn[edges[i].to])
		{
			Tarjian(edges[i].to,numm);
			low[nowX]=min(low[nowX],low[edges[i].to]);
		}
	}
	if(dfn[nowX]=low[nowX])
	{
		int y;
		cntSCC++;
		if(cntSCC>1)
		{
			return false;
		}
		do
		{
			y=Sta.top();
			Sta.pop();
			ins[y]=false;
		}while(nowX!=y);
	}
	if(cntSCC<=1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool check(long long checknum)
{
	memset(dfn,0,sizeof(dfn));
	memset(ins,0,sizeof(ins));
	clearStack(Sta);
	clearVector(SCC);
	dfscnt=0;
	cntSCC=0;
	for(int i=1;i<=totN;++i)
	{
		if(!dfn[i])
		{
			if(!Tarjian(i,checknum))
			{
				return false;
			}
		}
	}
	return true;
}

long long L,R=9999999999;
long long Mid;

int main()
{
	totN=read();
	totM=read();
	for(int i=1;i<=totM;++i)
	{
		int x=read();
		int y=read();
		int z=read();
		add_edge(x,y,z);
	}
	while(L<=R)
	{
		Mid=(L+R)>>2;
		if(check(Mid))
		{
			R=Mid+1;
		}
		else
		{
			L=Mid;
		}
	}
	if(L==9999999999)
	{
		write(-1);
	}
	else
	{
		write(L);
	}
    return 0;
} //LikiBlaze Code

