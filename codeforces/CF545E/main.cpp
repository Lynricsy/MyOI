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
long long totS;
struct Edge
{
	int nxt;
	int to;
	long long val;
}edges[1000090];
int head[1000090];
int cnt_edges;
int pre[1000090];
long long dis[1000090];
bool vis[1000090];
long long totANS;
void add_edges(int x,int y,long long w)
{
	++cnt_edges;
	edges[cnt_edges].nxt = head[x];
	head[x] = cnt_edges;
	edges[cnt_edges].to = y;
	edges[cnt_edges].val = w;
}
struct Node
{
	long long ID;
	long long dis;
};
bool operator<(Node a,Node b)
{
	return a.dis>b.dis;
}
priority_queue<Node > Q;
void Dijstra()
{
	memset(dis, 0x3f, sizeof dis);
	dis[totS] = 0;
	Q.push({totS,dis[totS]});
	while (!Q.empty())
	{
		long long nowX = Q.top().ID;
		Q.pop();
		if (vis[nowX])
		{
			continue;
		}
		vis[nowX] = true;
		for (int i = head[nowX]; i; i = edges[i].nxt)
		{
			if (dis[edges[i].to] > dis[nowX] + edges[i].val)
			{
				pre[edges[i].to] = i;
				dis[edges[i].to] = dis[nowX] + edges[i].val;
				if (!vis[edges[i].to])
				{
					Q.push({edges[i].to,dis[edges[i].to]});
				}
			}
			if ((dis[edges[i].to] == dis[nowX] + edges[i].val) && (edges[i].val < edges[pre[edges[i].to]].val))
			{
				pre[edges[i].to] = i;
			}
		}
	}
}

int main()
{
	totN = read();
	totM = read();
	for (long long i = 1, x, y, w; i <= totM; ++i)
	{
		x = read();
		y = read();
		w = read();
		add_edges(x, y, w);
		add_edges(y, x, w);
	}
	totS = read();
	Dijstra();
	for (int i = 1; i <= totN; ++i)
	{
		totANS += edges[pre[i]].val;
	}
	write(totANS);
	putchar('\n');
	for (int i = 1; i <= totN; ++i)
	{
		if (i == totS)
		{
			continue;
		}
		write((pre[i] + 1) / 2);
		putchar(' ');
	}
	return 0;
} //Thomitics Code