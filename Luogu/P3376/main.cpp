#include <bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f

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

const long long maxN=100090;
long long totN;
long long totM;
long long totS;
long long totT;
long long cnt=1;
long long head[maxN*3];
long long DIS[maxN];
long long now[maxN];
long long totFLOW;

struct Edge
{
	long long nxt;
	long long to;
	long long val;
}edges[maxN*3];

void add_edge(long long x,long long y,long long w)
{
	++cnt;
	edges[cnt].nxt=head[x];
	head[x]=cnt;
	edges[cnt].to=y;
	edges[cnt].val=w;

	++cnt;
	edges[cnt].nxt=head[y];
	head[y]=cnt;
	edges[cnt].to=x;
	edges[cnt].val=w;
}

bool BFS()
{
	memset(DIS, 0x3f, sizeof DIS);
	queue<long long> Q;
	Q.push(totS);
	DIS[totS] = 0;
	now[totS] = head[totS];
	while (!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for (int i = head[x]; i; i = edges[i].nxt)
		{
			int vir = edges[i].to;
			if ((DIS[vir] != INF) || (!edges[i].val))
			{
				continue;
			}
			Q.push(vir);
			DIS[vir] = DIS[x] + 1;
			now[vir] = head[vir];
			if (vir == totT)
			{
				return true;
			}
		}
	}
	return false;
}
inline long long DFS(long long x,long long nowFLOW)
{
	if (x==totT)
	{
		return nowFLOW;
	}
	long long dotRES,res=0;
	for (int i = now[x]; i && nowFLOW; i = edges[i].nxt)
	{
		now[x]=i;
		int vir=edges[i].to;
		if ((DIS[vir]==DIS[x]+1)&&(edges[i].val))
		{
			dotRES=DFS(vir,min(edges[i].val,nowFLOW));
			if(!dotRES)
			{
				DIS[x]=INF;
			}
			edges[i].val-=dotRES;
			edges[i^1].val+=dotRES;
			res+=dotRES;
			nowFLOW-=dotRES;
		}
	}
	return res;
}

int main()
{
	totN=read();
	totM=read();
	totS=read();
	totT=read();
	for (int i = 1,x,y,w; i <= totM; ++i)
	{
		x=read();
		y=read();
		w=read();
		add_edge(x,y,w);
	}
	while (BFS())
	{
		totFLOW+=DFS(totS,INF);
	}
	write(totFLOW);
	return 0;
} //Thomitics Code