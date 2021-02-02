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

bool vis[10090];
int totN,totM,totS,totT;
long long head[10090];
struct Edge
{
	int to,nxt;
	long long val;
}edges[20090];
long long cnt=1;

void add_edge(int x,int y,long  long w)
{
	++cnt;
	edges[cnt].to=y;
	edges[cnt].val=w;
	edges[cnt].nxt=head[x];
	head[x]=cnt;
}

long long DFS(int nowX,long long flow)
{
	if (nowX == totT)
	{
		return flow;
	}
	vis[nowX] = true;
	for (int i = head[nowX]; i; i = edges[i].nxt)
	{
		int y = edges[i].to;
		if ((!edges[i].val) || vis[y])
		{
			continue;
		}
		int res = 0;
		if ((res = DFS(y, min(flow, edges[i].val))) > 0)
		{
			edges[i].val -= res;
			edges[i ^ 1].val += res;
			return res;
		}
	}
	return 0;
}

int main()
{
	totN=read();
	totM=read();
	totS=read();
	totT=read();
	for (long long i = 1,x,y,w; i <= totM; ++i)
	{
		x=read();
		y=read();
		w=read();
		add_edge(x,y,w);
		add_edge(y,x,0);
	}
	long long res=0;
	long long tot=0;
	while (memset(vis,0, sizeof(vis))&&((res=DFS(totS,1E18))>0))
	{
		tot+=res;
	}
	write(tot);
	return 0;
}//LikiBlaze Code
